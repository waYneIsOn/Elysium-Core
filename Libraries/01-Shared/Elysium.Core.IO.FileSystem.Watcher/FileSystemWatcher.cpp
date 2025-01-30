#include "FileSystemWatcher.hpp"

#ifndef ELYSIUM_CORE_CONTAINER_DELEGATEOFVOIDCONSTIASYNCRESULTPOINTER
#include "../Elysium.Core/DelegateOfVoidConstIASyncResultPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEACCESS
#include "../Elysium.Core.IO/FileAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEMODE
#include "../Elysium.Core.IO/FileMode.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEOPTIONS
#include "../Elysium.Core.IO/FileOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESHARE
#include "../Elysium.Core.IO/FileShare.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "../Elysium.Core.IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Elysium.Core.Template/Utf16.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../Elysium.Core.Threading/ThreadPool.hpp"
#endif

Elysium::Core::IO::FileSystemWatcher::FileSystemWatcher()
	: _Path(), _Filter(), _NotifyFilters(), _IncludeSubdirectories(), _AddressOfLatestAsyncResult(),
	_DirectoryHandle(), _CompletionPortHandle()
{ }

Elysium::Core::IO::FileSystemWatcher::FileSystemWatcher(const char8_t* Path, const char8_t* Filter, const NotifyFilters NotifyFilters, const bool IncludeSubdirectories)
	: _Path(Path), _Filter(Filter), _NotifyFilters(NotifyFilters), _IncludeSubdirectories(IncludeSubdirectories), _AddressOfLatestAsyncResult(nullptr),
	_DirectoryHandle(CreateNativeDirectoryHandle(&_Path[0], _Path.GetLength())),
	_CompletionPortHandle(CreateThreadpoolIo(_DirectoryHandle, &IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment))
{ }

Elysium::Core::IO::FileSystemWatcher::~FileSystemWatcher()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	EndInit();

	if (_DirectoryHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_DirectoryHandle);
		_DirectoryHandle = INVALID_HANDLE_VALUE;
	}

	if (_CompletionPortHandle != nullptr)
	{
		// https://learn.microsoft.com/en-us/windows/win32/api/threadpoolapiset/nf-threadpoolapiset-closethreadpoolio
		// "You should close the associated file handle and wait for all outstanding overlapped I/O operations to complete before calling this function."
		WaitForThreadpoolIoCallbacks(_CompletionPortHandle, FALSE);
		CloseThreadpoolIo(_CompletionPortHandle);
		_CompletionPortHandle = nullptr;
	}
#else
#error "undefined os"
#endif
}

const Elysium::Core::IO::NotifyFilters Elysium::Core::IO::FileSystemWatcher::GetNotifyFilters() const
{
	return _NotifyFilters;
}

const bool Elysium::Core::IO::FileSystemWatcher::GetIncludeSubdirectories() const
{
	return _IncludeSubdirectories;
}

const Elysium::Core::Utf8String& Elysium::Core::IO::FileSystemWatcher::GetPath() const
{
	return _Path;
}

const Elysium::Core::Utf8String& Elysium::Core::IO::FileSystemWatcher::GetFilter() const
{
	return _Filter;
}

void Elysium::Core::IO::FileSystemWatcher::BeginInit()
{
	if (_AddressOfLatestAsyncResult.Load() != nullptr)
	{	// already initialized (check is necessary since this method is public)
		return;
	}

	FileSystemWatcherAsyncResult* AsyncResult = new FileSystemWatcherAsyncResult(*this, 
		Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer::Bind<FileSystemWatcher, &FileSystemWatcher::EndInit>(*this),
		nullptr, 0x0, _CompletionPortHandle);
	DWORD BytesReturned = 0;
	
	StartThreadpoolIo(_CompletionPortHandle);
	if (ReadDirectoryChangesExW(_DirectoryHandle, &AsyncResult->_InformationBuffer[0], AsyncResult->_InformationBufferSize, _IncludeSubdirectories,
		static_cast<DWORD>(_NotifyFilters), &BytesReturned, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap, nullptr,
		READ_DIRECTORY_NOTIFY_INFORMATION_CLASS::ReadDirectoryNotifyExtendedInformation) == FALSE)
	{
		Elysium::Core::uint32_t ErrorCode = GetLastError();
		if (ErrorCode != ERROR_IO_PENDING)
		{
			delete AsyncResult;
			throw IOException();
		}
	}

	_AddressOfLatestAsyncResult.Exchange(AsyncResult);
}

void Elysium::Core::IO::FileSystemWatcher::EndInit()
{
	if (_AddressOfLatestAsyncResult.Load() == nullptr)
	{	// already uninitialized (this check is necessary since this method is public)
		return;
	}

	//WaitForThreadpoolIoCallbacks(_CompletionPortHandle, TRUE);
	FileSystemWatcherAsyncResult* AsyncResult = _AddressOfLatestAsyncResult.Exchange(nullptr);
	AsyncResult->_WrappedOverlap._AsyncResult = nullptr;
	delete AsyncResult;
}

void Elysium::Core::IO::FileSystemWatcher::EndInit(const Elysium::Core::IAsyncResult* AsyncResult)
{
	FileSystemWatcherAsyncResult* AsyncFileWatcherResult = const_cast<FileSystemWatcherAsyncResult*>(static_cast<const FileSystemWatcherAsyncResult*>(AsyncResult));
	if (AsyncFileWatcherResult == nullptr)
	{	// ToDo: throw specific exception - This should actually never happen!
		throw 1;
	}

	if (AsyncFileWatcherResult->GetErrorCode() != NO_ERROR)
	{
		throw IOException(AsyncFileWatcherResult->GetErrorCode());
	}

	// ...
	Elysium::Core::size Offset = 0;
	wchar_t* OldName;
	do
	{
		const FILE_NOTIFY_EXTENDED_INFORMATION& Info = (FILE_NOTIFY_EXTENDED_INFORMATION&)AsyncFileWatcherResult->_InformationBuffer[Offset];
		if (Info.Action == 0)
		{	// an error can occurre if:
			// - the buffer is too small to capture all events (FileSystemWatcherAsyncResult::_InformationBufferSize).
			// - a remote directory is being monitored and the connection is lost
			// - etc.
			DWORD LastError = GetLastError();
			if (LastError == 0)
			{
				//Error(*this, ErrorEventArgs(...));
			}
			else
			{
				//Error(*this, ErrorEventArgs(...));
			}
		}

		// ToDo: strings
		switch (Info.Action)
		{
		case FILE_ACTION_ADDED:
			OnCreated(*this, FileSystemEventArgs(WatcherChangeTypes::Created, nullptr, nullptr));
			break;
		case FILE_ACTION_REMOVED:
			OnDeleted(*this, FileSystemEventArgs(WatcherChangeTypes::Deleted, nullptr, nullptr));
			break;
		case FILE_ACTION_MODIFIED:
			OnChanged(*this, FileSystemEventArgs(WatcherChangeTypes::Changed, nullptr, nullptr));
			break;
		case FILE_ACTION_RENAMED_OLD_NAME:
			break;
		case FILE_ACTION_RENAMED_NEW_NAME:
			OnRenamed(*this, RenamedEventArgs(WatcherChangeTypes::Renamed, nullptr, nullptr, nullptr));
			break;
		default:
			break;
		}
		
		Offset = Info.NextEntryOffset;
	} while (Offset > 0);

	Elysium::Core::Threading::ManualResetEvent& AsyncWaitHandle =
		(Elysium::Core::Threading::ManualResetEvent&)AsyncFileWatcherResult->GetAsyncWaitHandle();
	bool GetAsyncWaitHandleSetResult = AsyncWaitHandle.Set();

	// A successful io-operation musn't be canceled!
	// Make sure to not cause CancelThreadpoolIo(_CompletionPortHandle) when AsyncFileWatcherResult get's destructed!
	AsyncFileWatcherResult->_CompletionPortHandle = nullptr;

	// make sure to not cause a memory leak
	FileSystemWatcherAsyncResult* PreviousAsyncResult = _AddressOfLatestAsyncResult.Exchange(nullptr);
	PreviousAsyncResult->_WrappedOverlap._AsyncResult = nullptr;
	delete PreviousAsyncResult;

	// run again
	BeginInit();
}

#if defined ELYSIUM_CORE_OS_WINDOWS
HANDLE Elysium::Core::IO::FileSystemWatcher::CreateNativeDirectoryHandle(const char8_t* Path, const size_t PathLength)
{
	// ToDo: don't assume correct input (Utf16::SafeToWideString)
	Elysium::Core::WideString WindowsPath = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Path, PathLength);

	// ...
	HANDLE DirectoryHandle = CreateFile((wchar_t*)&WindowsPath[0], static_cast<Elysium::Core::uint32_t>(FileAccess::Read),
		static_cast<Elysium::Core::uint32_t>(FileShare::ReadWrite),
		nullptr, // default security
		static_cast<Elysium::Core::uint32_t>(FileMode::Open), static_cast<Elysium::Core::uint32_t>(FileOptions::Asynchronous | FileOptions::BackupSemantics), nullptr);
	if (DirectoryHandle == INVALID_HANDLE_VALUE)
	{
		throw IOException();
	}

	return DirectoryHandle;
}

void Elysium::Core::IO::FileSystemWatcher::IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	Elysium::Core::Internal::WrappedOverlap* WrappedOverlap = static_cast<Elysium::Core::Internal::WrappedOverlap*>(Overlapped);
	Elysium::Core::IO::FileSystemWatcherAsyncResult* AsyncFileWatcherResult = dynamic_cast<Elysium::Core::IO::FileSystemWatcherAsyncResult*>(WrappedOverlap->_AsyncResult);
	if (AsyncFileWatcherResult != nullptr)
	{
		AsyncFileWatcherResult->_BytesTransferred = NumberOfBytesTransferred;
		AsyncFileWatcherResult->_ErrorCode = static_cast<Elysium::Core::uint16_t>(IoResult);

		const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback = AsyncFileWatcherResult->GetCallback();
		Callback(AsyncFileWatcherResult);
	}
}
#endif
