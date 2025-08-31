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

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../Elysium.Core.Template/MemCpy.hpp"
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
	_CompletionPortHandle(CreateThreadpoolIo(_DirectoryHandle, IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment))
{ }

Elysium::Core::IO::FileSystemWatcher::~FileSystemWatcher()
{
	_IsDestructing = true;

#if defined ELYSIUM_CORE_OS_WINDOWS
	EndInit();

	if (_CompletionPortHandle != nullptr)
	{
		// cancel new callbacks from coming in
		CancelThreadpoolIo(_CompletionPortHandle);

		// Ensure no callbacks are still active
		// https://learn.microsoft.com/en-us/windows/win32/api/threadpoolapiset/nf-threadpoolapiset-closethreadpoolio
		// "You should close the associated file handle and wait for all outstanding overlapped I/O operations to complete before calling this function."
		WaitForThreadpoolIoCallbacks(_CompletionPortHandle, TRUE);

		CloseThreadpoolIo(_CompletionPortHandle);
		_CompletionPortHandle = nullptr;
	}

	if (_DirectoryHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_DirectoryHandle);
		_DirectoryHandle = INVALID_HANDLE_VALUE;
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
	if (nullptr != _AddressOfLatestAsyncResult.Load())
	{	// already initialized (check is necessary since this method is public)
		return;
	}

	if (INVALID_HANDLE_VALUE == _DirectoryHandle)
	{
		return;
	}

	FileSystemWatcherAsyncResult* RawAsyncFileWatcherResult = new FileSystemWatcherAsyncResult(*this,
		Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference::Bind<FileSystemWatcher, &FileSystemWatcher::EndInit>(*this),
		nullptr, 0x0, _CompletionPortHandle);

	RawAsyncFileWatcherResult->_WrappedOverlap._AsyncResult = &_AddressOfLatestAsyncResult;
	_AddressOfLatestAsyncResult.Exchange(RawAsyncFileWatcherResult);

	DWORD BytesReturned = 0;

	StartThreadpoolIo(_CompletionPortHandle);
	if (FALSE == ReadDirectoryChangesExW(_DirectoryHandle, &RawAsyncFileWatcherResult->_InformationBuffer[0],
		RawAsyncFileWatcherResult->_InformationBufferSize, _IncludeSubdirectories, static_cast<DWORD>(_NotifyFilters), &BytesReturned,
		(LPOVERLAPPED)&RawAsyncFileWatcherResult->_WrappedOverlap, nullptr,
		READ_DIRECTORY_NOTIFY_INFORMATION_CLASS::ReadDirectoryNotifyExtendedInformation))
	{
		DWORD ErrorCode = GetLastError();
		if (ERROR_IO_PENDING != ErrorCode)
		{
			_AddressOfLatestAsyncResult.Exchange(nullptr);

			// https://learn.microsoft.com/en-us/windows/win32/api/threadpoolapiset/nf-threadpoolapiset-cancelthreadpoolio
			// - To prevent memory leaks, you must call the CancelThreadpoolIo function for either of the following scenarios:
			// An overlapped (asynchronous) I/O operation fails (that is, the asynchronous I/O function call returns failure with
			// an error code other than ERROR_IO_PENDING).
			// - "...notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS..." isn't the case here as I do not call
			// SetFileCompletionNotificationModes(...) with FILE_SKIP_COMPLETION_PORT_ON_SUCCESS anywhere in this class.
			// @ToDo:
			// doing it like this might cause the handle to get canceled twice (destructor!) - need to check!
			CancelThreadpoolIo(_CompletionPortHandle);

			delete RawAsyncFileWatcherResult;

			throw IOException(ErrorCode);
		}
	}
}

void Elysium::Core::IO::FileSystemWatcher::EndInit()
{
	FileSystemWatcherAsyncResult* RawAsyncFileWatcherResult = _AddressOfLatestAsyncResult.Exchange(nullptr);
	if (RawAsyncFileWatcherResult == nullptr)
	{	// already uninitialized (this check is necessary since this method is public)
		return;
	}
	
	// stop current io (causes another callback with IoResult being ERROR_OPERATION_ABORTED)
	if (FALSE == CancelIoEx(_DirectoryHandle, &RawAsyncFileWatcherResult->_WrappedOverlap._Overlapped))
	{
		DWORD ErrorCode = GetLastError();
		bool bla = false;
	}
	
	// wait for current io to complete
	DWORD BytesTransferred = 0;
	if (FALSE == GetOverlappedResultEx(_DirectoryHandle, &RawAsyncFileWatcherResult->_WrappedOverlap._Overlapped, &BytesTransferred,
		INFINITE, TRUE))
	{
		DWORD ErrorCode = GetLastError();
		switch (ErrorCode)
		{
		case ERROR_OPERATION_ABORTED:
			// expected
			break;
		case ERROR_IO_PENDING:
			// @ToDo: wait longer? (instead of throwing an exception!)
			throw IOException(ErrorCode);
		default:
			throw IOException(ErrorCode);
		}
	}

	RawAsyncFileWatcherResult->_WrappedOverlap._AsyncResult = nullptr;
	delete RawAsyncFileWatcherResult;
}

const bool Elysium::Core::IO::FileSystemWatcher::IsInterested(const char8_t* RelativePath)
{
	const char8_t* Expression = &_Filter[0];

	// @ToDo: check whether the os will ever give use an empty relative path as this check could be removed!
	if (Expression == nullptr || RelativePath == nullptr)
	{
		return false;
	}

	if (Expression[0] == u8'*')
	{
		const Elysium::Core::Template::System::size ExpressionLength = _Filter.GetLength();
		if (ExpressionLength == 1)
		{	// special case "*"
			return true;
		}

		// @ToDo: implement this fully and correctly!
		// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-fsa/0b034646-4e23-4874-8488-2adac231ff23
		const char8_t* Asterisk = Elysium::Core::Template::Text::CharacterTraits<char8_t>::Find(&Expression[1], ExpressionLength - 1, u8'*');
		if (Asterisk != nullptr)
		{
			const Elysium::Core::Template::System::size RelativePathLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(RelativePath);
			if (RelativePathLength < ExpressionLength - 1)
			{
				return false;
			}

			// ...

			return true;
		}
	}

	// @ToDo: ...

	return false;
}

void Elysium::Core::IO::FileSystemWatcher::EndInit(Elysium::Core::Template::Threading::Atomic<Elysium::Core::IAsyncResult*>& AsyncResult)
{
	IAsyncResult* RawAsyncResult = AsyncResult.Exchange(nullptr);
	FileSystemWatcherAsyncResult* RawAsyncFileWatcherResult = static_cast<FileSystemWatcherAsyncResult*>(RawAsyncResult);
	if (RawAsyncFileWatcherResult == nullptr)
	{	// This should probably only happen if EndInit() has been called.
		return;
	}

	if (RawAsyncFileWatcherResult->GetErrorCode() != NO_ERROR)
	{
		const Elysium::Core::uint16_t ErrorCode = RawAsyncFileWatcherResult->GetErrorCode();

		// cleanup
		RawAsyncFileWatcherResult->_CompletionPortHandle = nullptr;
		RawAsyncFileWatcherResult->_WrappedOverlap._AsyncResult = nullptr;
		delete RawAsyncFileWatcherResult;

		throw IOException(ErrorCode);
	}


	// ...
	bool PotentialBufferOverflow = false;
	if (RawAsyncFileWatcherResult->_BytesTransferred == FileSystemWatcherAsyncResult::_InformationBufferSize)
	{	// might be a buffer overflow
		PotentialBufferOverflow = true;
	}

	// ...
	Elysium::Core::size Offset = 0;
	wchar_t* OldName = nullptr;
	do
	{
		const FILE_NOTIFY_EXTENDED_INFORMATION& Info = (FILE_NOTIFY_EXTENDED_INFORMATION&)RawAsyncFileWatcherResult->_InformationBuffer[Offset];
		
		// pre-validate
		if (Info.Action == 0 || Info.FileNameLength == 0)
		{
			PotentialBufferOverflow = true;
			//break;
		}
		
		if (Info.NextEntryOffset == 0)
		{	// yes, this can occurre resulting in an endless loop
			// @ToDo: is my parsing incorrect/misaligned?
			bool bla = false;
			//break;
		}

		// ...		
		Utf8String FileName = Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(Info.FileName, 
			Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Info.FileName));

		// @ToDo: populate FullPath (don't just concatenate strings!)
		Utf8String FullPath = Utf8String(_Path.GetLength() + FileName.GetLength() + sizeof(char8_t));
		Elysium::Core::Template::Memory::MemCpy(&FullPath[0], &_Path[0], _Path.GetLength());
		FullPath[_Path.GetLength()] = u8'\\';
		Elysium::Core::Template::Memory::MemCpy(&FullPath[_Path.GetLength() + sizeof(char8_t)], &FileName[0], FileName.GetLength());

		switch (Info.Action)
		{
		case 0:
		{
			// this is undocumented but can appear!
			// there's some suggestion that it can appear sporadically and should be ignored.
			// it seems to occurre when to many changes happen (with the buffer not necessarily overflowing!!!)
			/*
			DWORD ErrorCode = GetLastError();

			OnError(*this, ErrorEventArgs(Elysium::Core::Template::Functional::Move(
				Elysium::Core::Template::Exceptions::SystemException(21))));
			*/
		}
			break;
		case FILE_ACTION_ADDED:
			if (IsInterested(&FileName[0]))
			{
				OnCreated(*this, FileSystemEventArgs(WatcherChangeTypes::Created, Elysium::Core::Template::Functional::Move(FullPath),
					Elysium::Core::Template::Functional::Move(FileName)));
			}
			break;
		case FILE_ACTION_REMOVED:
			if (IsInterested(&FileName[0]))
			{
				OnDeleted(*this, FileSystemEventArgs(WatcherChangeTypes::Deleted, Elysium::Core::Template::Functional::Move(FullPath),
					Elysium::Core::Template::Functional::Move(FileName)));
			}
			break;
		case FILE_ACTION_MODIFIED:
			if (IsInterested(&FileName[0]))
			{
				OnChanged(*this, FileSystemEventArgs(WatcherChangeTypes::Changed, Elysium::Core::Template::Functional::Move(FullPath),
					Elysium::Core::Template::Functional::Move(FileName)));
			}
			break;
		case FILE_ACTION_RENAMED_OLD_NAME:
			OldName = const_cast<wchar_t*>(Info.FileName);
			break;
		case FILE_ACTION_RENAMED_NEW_NAME:
		{
			if (IsInterested(&FileName[0]))
			{
				Utf8String OldFileName = Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(OldName,
					Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(OldName));
				OnRenamed(*this, RenamedEventArgs(WatcherChangeTypes::Renamed, Elysium::Core::Template::Functional::Move(FullPath),
					Elysium::Core::Template::Functional::Move(FileName), Elysium::Core::Template::Functional::Move(OldFileName)));
			}
		}
			break;
		default:
			// @ToDo: some sort of notification about the unhandled event-type
			// simply call OnError(...)?
			break;
		}

		Offset += Info.NextEntryOffset;
		//Offset = Info.NextEntryOffset;

		// post-validate
		if (Offset >= RawAsyncFileWatcherResult->_BytesTransferred || Info.NextEntryOffset == 0)
		{
			PotentialBufferOverflow = true;
			break;
		}
	} while (Offset > 0);

	// ...
	if (PotentialBufferOverflow)
	{
		// afaik there's no default windows error code for this -> .NET uses error code 0x80131671
		// @ToDo: actually check this
		OnError(*this, ErrorEventArgs(Elysium::Core::Template::Functional::Move(
			Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException(0x80131671, 
				u8"Too many changes at once in directory: ..."))));	// @ToDo: use _Path
	}

	// ...
	Elysium::Core::Threading::ManualResetEvent& AsyncWaitHandle =
		(Elysium::Core::Threading::ManualResetEvent&)RawAsyncFileWatcherResult->GetAsyncWaitHandle();
	bool GetAsyncWaitHandleSetResult = AsyncWaitHandle.Set();

	// A successful io-operation musn't be canceled!
	// Make sure to not cause CancelThreadpoolIo(_CompletionPortHandle) when RawAsyncFileWatcherResult get's destructed!
	RawAsyncFileWatcherResult->_CompletionPortHandle = nullptr;

	// make sure to not cause a memory leak
	RawAsyncFileWatcherResult->_WrappedOverlap._AsyncResult = nullptr;
	delete RawAsyncFileWatcherResult;

	// run again
	if (!_IsDestructing)
	{
		BeginInit();
	}
}

#if defined ELYSIUM_CORE_OS_WINDOWS
HANDLE Elysium::Core::IO::FileSystemWatcher::CreateNativeDirectoryHandle(const char8_t* Path, const size_t PathLength)
{
	// @ToDo: don't assume correct input (Utf16::SafeToWideString)
	Elysium::Core::WideString WindowsPath = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Path, PathLength);

	// ...
	HANDLE DirectoryHandle = CreateFile((wchar_t*)&WindowsPath[0], FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr, // default security
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		nullptr);
	if (DirectoryHandle == INVALID_HANDLE_VALUE)
	{
		throw IOException();
	}

	return DirectoryHandle;
}

void Elysium::Core::IO::FileSystemWatcher::IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	if (Context == nullptr || Overlapped == nullptr)
	{
		return;
	}

	switch (IoResult)
	{
	case NO_ERROR:	// 0
		// "default" result - nothing to do here
		break;
	case ERROR_OPERATION_ABORTED:	// 995
		// ...
		return;
	default:
		break;
	}

	FileSystemWatcher* Watcher = reinterpret_cast<FileSystemWatcher*>(Context);

	Elysium::Core::Internal::WrappedOverlap* WrappedOverlap = reinterpret_cast<Elysium::Core::Internal::WrappedOverlap*>(Overlapped);
	Elysium::Core::Template::Threading::Atomic<IAsyncResult*>* AsyncResult = 
		reinterpret_cast<Elysium::Core::Template::Threading::Atomic<IAsyncResult*>*>(WrappedOverlap->_AsyncResult);
	if (AsyncResult != nullptr)
	{
		IAsyncResult* RawAsyncResult = AsyncResult->Load();
		FileSystemWatcherAsyncResult* RawAsyncFileWatcherResult = reinterpret_cast<FileSystemWatcherAsyncResult*>(RawAsyncResult);
		const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback = RawAsyncFileWatcherResult->GetCallback();
		RawAsyncFileWatcherResult->_BytesTransferred = NumberOfBytesTransferred;
		RawAsyncFileWatcherResult->_ErrorCode = static_cast<Elysium::Core::uint16_t>(IoResult);

		Callback(*AsyncResult);
	}
}
#endif
