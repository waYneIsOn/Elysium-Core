/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMWATCHER_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMWATCHER_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "../../Container/FixedSizeBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_EVENT
#include "../../Dispatch/Event.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_IOEXCEPTION
#include "../../Exceptions/IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_ERROREVENTEVENTARGS
#include "ErrorEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMEVENTARGS
#include "FileSystemEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_RENAMEDEVENTARGS
#include "RenamedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_NOTIFYFILTERS
#include "NotifyFilters.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../Text/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "../../Threading/Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#include "../../Threading/ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "../../Threading/Mutex.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#include "../../Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../../Text/Unicode/Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _APISETFILE_
#include <fileapi.h>
#endif

#ifndef _THREADPOOLAPISET_H_
#include <threadpoolapiset.h>
#endif

namespace Elysium::Core::Template::IO::FileSystem
{
	template <class = void>
	class FileSystemWatcher
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		inline static constexpr const Elysium::Core::Template::IO::FileSystem::NotifyFilters DefaultNotifyFilters = Elysium::Core::Template::IO::FileSystem::NotifyFilters::LastWrite |
			Elysium::Core::Template::IO::FileSystem::NotifyFilters::FileName | Elysium::Core::Template::IO::FileSystem::NotifyFilters::DirectoryName;

		/// <summary>
		/// 4kb is the default memory page size on windows (x86 and x64).
		/// This should be used with a low event volume where the use of minimal memory suffices.
		/// </summary>
		inline static constexpr const Elysium::Core::Template::System::size MinimumInformationBufferSize = 4096;

		/// <summary>
		/// 64kb appears to be the safe upper bound for compatibility across all filesystems on windows.
		/// This appears to be the sweet spot in regards to safety, compatibility and efficiency.
		/// (Chromium, VS Code etc. appear to be using this value - with overflow detection/resilience logic.)
		/// </summary>
		inline static constexpr const Elysium::Core::Template::System::size SafeInformationBufferSize = 65536;

		/// <summary>
		/// 128-256kb works but might be risky in some filesystems.
		/// This can be used for high frequency event volume.
		/// </summary>
		inline static constexpr const Elysium::Core::Template::System::size MaximumInformationBufferSize = 262144;
	private:
		class IoContext
		{
		public:
			inline constexpr IoContext() = delete;

			inline constexpr IoContext(const Elysium::Core::Template::System::size BufferSize)
				: _InformationBuffer(BufferSize)
			{ }
		public:
			inline void Reset()
			{
				const Elysium::Core::Template::System::size Position = 0;
				_Overlapped.Offset = static_cast<unsigned long>(Position);
				_Overlapped.OffsetHigh = static_cast<unsigned long>(Position >> 32);
			}
		public:
			OVERLAPPED _Overlapped{};
			Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _InformationBuffer;
		};
	public:
		constexpr FileSystemWatcher() = delete;

		inline constexpr FileSystemWatcher(const Elysium::Core::Template::Text::StringView<char8_t> Path, const Elysium::Core::Template::Text::StringView<char8_t> Filter = u8"*.*",
			const Elysium::Core::Template::IO::FileSystem::NotifyFilters NotifyFilters = DefaultNotifyFilters, const bool IncludeSubdirectories = false,
			const Elysium::Core::Template::System::size InternalBufferSize = SafeInformationBufferSize)
			: _Path(Path), _Filter(Filter), _NotifyFilters(NotifyFilters), _IncludeSubdirectories(IncludeSubdirectories), _InternalBufferSize(InternalBufferSize),
			_CurrentIoContext(InternalBufferSize), _DirectoryHandle(CreateNativeDirectoryHandle(Path)),
			_CompletionPortHandle(CreateThreadpoolIo(_DirectoryHandle, IOCompletionPortCallback, this, &Elysium::Core::Template::Threading::ThreadPool::GetIOPool()._Environment))
		{ }

		constexpr FileSystemWatcher(const FileSystemWatcher& Source) = delete;

		constexpr FileSystemWatcher(FileSystemWatcher&& Right) noexcept = delete;

		inline constexpr ~FileSystemWatcher()
		{
			_IocpIsRunningOrDestructingMutex.Lock();
			_IsDestructing = true;
			_IocpIsRunningOrDestructingMutex.Unlock();

			EndInit();

			if (nullptr != _CompletionPortHandle)
			{
				CloseThreadpoolIo(_CompletionPortHandle);
				_CompletionPortHandle = nullptr;
			}

			if (FALSE == CloseHandle(_DirectoryHandle))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			_DirectoryHandle = INVALID_HANDLE_VALUE;
		}
	public:
		constexpr FileSystemWatcher& operator=(const FileSystemWatcher& Source) = delete;

		constexpr FileSystemWatcher& operator=(FileSystemWatcher&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::IO::FileSystem::NotifyFilters GetNotifyFilters() const
		{
			return _NotifyFilters;
		}

		inline constexpr const bool GetIncludeSubdirectories() const
		{
			return _IncludeSubdirectories;
		}

		inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetPath() const
		{
			return _Path;
		}

		inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetFilter() const
		{
			return _Filter;
		}
	public:
		inline void BeginInit()
		{
			_IocpIsRunningOrDestructingMutex.Lock();
			if (_IsRunning || _IsDestructing)
			{
				_IocpIsRunningOrDestructingMutex.Unlock();
				return;
			}
			
			BeginInitInLockedState();

			_IocpIsRunningOrDestructingMutex.Unlock();
		}

		inline void EndInit()
		{
			_IocpIsRunningOrDestructingMutex.Lock();
			if (!_IsRunning)
			{
				_IocpIsRunningOrDestructingMutex.Unlock();
				return;
			}

			_IsRunning = false;

			// request cancellation of all outstanding IOCP operations and wait for them to finish
			BOOL CancelationResult = CancelIoEx(_DirectoryHandle, nullptr);

			const DWORD ErrorCode = GetLastError();
			_IocpIsRunningOrDestructingMutex.Unlock();
			if (FALSE == CancelationResult && ERROR_NOT_FOUND != ErrorCode)
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException(ErrorCode);
			}

			bool WaitResult = _AllIoOperationsCompleted.WaitOne();
			if (!WaitResult)
			{
				bool sdf = false;
			}

			if (_InFlightIos != 0 && nullptr != _CompletionPortHandle)
			{
				// wait for CALLBACKS that are queued/running
				WaitForThreadpoolIoCallbacks(_CompletionPortHandle, FALSE);
				bool sdfsdf = false;
			}

			_IocpIsRunningOrDestructingMutex.Unlock();
		}
	private:
		inline void ProcessInformationBuffer(const IoContext& IoContext, ULONG IoResult = NO_ERROR, ULONG_PTR NumberOfBytesTransferred = 0) const noexcept
		{
			if (NO_ERROR != IoResult)
			{
				// ...
				OnError(*this, ErrorEventArgs(Elysium::Core::Template::Functional::Move(Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException(0x80131671,
					u8"Generic error has occurred: ErrorCode XYZ"))));
				return;
			}

			if (0 == NumberOfBytesTransferred)
			{	// this seems to be the case when buffer size is smaller than a single message (case: buffer overflow)
				OnError(*this, ErrorEventArgs(Elysium::Core::Template::Functional::Move( Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException(0x80131671,
					u8"InternalBufferSize is too small."))));
				return;
			}

			// ...
			bool PotentialBufferOverflow = false;
			if (IoContext._InformationBuffer.GetCapacity() == NumberOfBytesTransferred)
			{	// might be a buffer overflow
				PotentialBufferOverflow = true;
			}

			// ...
			constexpr const Elysium::Core::Template::System::size InfoBlockSize = sizeof(FILE_NOTIFY_EXTENDED_INFORMATION);
			Elysium::Core::Template::System::size Offset = 0;
			wchar_t* OldName = nullptr;
			do
			{
				const FILE_NOTIFY_EXTENDED_INFORMATION* Info = reinterpret_cast<const FILE_NOTIFY_EXTENDED_INFORMATION*>(&IoContext._InformationBuffer[Offset]);
				if (nullptr == Info)
				{	// can only happen if FileSystemWatcher got destructed with the callback still running!!!
					throw 1;
				}
				
				// validate premature end of buffer (incomplete entry)
				if (Offset + InfoBlockSize > NumberOfBytesTransferred)
				{
					PotentialBufferOverflow = true;
					//TempErrorMessage += u8"InfoBlockSize exceeds buffer.\r\n";
					break;
				}






				// incomplete entry due to buffer size?
				// @ToDo: check these cases to check whether we do have an incomplete entry. depending on the result these checks can all be removed
				{
					if (Info->FileNameLength == 0)
					{
						if (PotentialBufferOverflow)
						{
							throw 1;
						}
						else
						{
							throw 1;
						}
					}
					if (Offset >= NumberOfBytesTransferred)
					{
						if (PotentialBufferOverflow)
						{
							throw 1;
						}
						else
						{
							throw 1;
						}
					}

					const Elysium::Core::Template::System::size CurrentInfoSize = InfoBlockSize - sizeof(wchar_t) + (Info->FileNameLength / sizeof(wchar_t));
					if (CurrentInfoSize + Offset > NumberOfBytesTransferred)
					{
						if (PotentialBufferOverflow)
						{
							throw 1;
						}
						else
						{
							throw 1;
						}
					}
				}







				// Do NOT count the length of Info.FileName but use Info.FileNameLength!!!
				// I've seen cases of Info.FileName being "file.txth" with Info.FileNameLength being 16 (ie. wchar_t[8]) while
				// counting the number of characters would obviously result in wchar_t[9] giving incorrect results!
				// @ToDo: make sure this is "normal" and I am not causing some buffer corruption!!!
				Elysium::Core::Template::Text::String<char8_t> FileName = 
					Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(Info->FileName, Info->FileNameLength / sizeof(wchar_t));

				// @ToDo: populate FullPath (don't just concatenate strings!)
				Elysium::Core::Template::Text::String<char8_t> FullPath(_Path.GetLength() + FileName.GetLength() + sizeof(char8_t));
				Elysium::Core::Template::Memory::MemCpy(&FullPath[0], &_Path[0], _Path.GetLength());
				FullPath[_Path.GetLength()] = u8'\\';
				Elysium::Core::Template::Memory::MemCpy(&FullPath[_Path.GetLength() + sizeof(char8_t)], &FileName[0], FileName.GetLength());

				switch (Info->Action)
				{
				case 0:
				{
					// this is undocumented but can appear!
					// there's some suggestion that it can appear sporadically and should be ignored.
					// it seems to occurre when too many changes happen (with the buffer not necessarily overflowing!!!)
					// @ToDo: what to do? really just ignore it???
					/*
					DWORD ErrorCode = GetLastError();

					OnError(*this, ErrorEventArgs(Elysium::Core::Template::Functional::Move(
						Elysium::Core::Template::Exceptions::SystemException(21))));
					*/
				}
					break;
				case FILE_ACTION_ADDED:
					if (IsInterested(&FileName[0], true))
					{
						OnCreated(*this, FileSystemEventArgs(Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes::Created, Elysium::Core::Template::Functional::Move(FullPath),
							Elysium::Core::Template::Functional::Move(FileName)));
					}
					break;
				case FILE_ACTION_REMOVED:
					if (IsInterested(&FileName[0], true))
					{
						OnDeleted(*this, FileSystemEventArgs(Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes::Deleted, Elysium::Core::Template::Functional::Move(FullPath),
							Elysium::Core::Template::Functional::Move(FileName)));
					}
					break;
				case FILE_ACTION_MODIFIED:
					if (IsInterested(&FileName[0], true))
					{
						OnChanged(*this, FileSystemEventArgs(Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes::Changed, Elysium::Core::Template::Functional::Move(FullPath),
							Elysium::Core::Template::Functional::Move(FileName)));
					}
					break;
				case FILE_ACTION_RENAMED_OLD_NAME:
					OldName = const_cast<wchar_t*>(Info->FileName);
					break;
				case FILE_ACTION_RENAMED_NEW_NAME:
				{
					if (IsInterested(&FileName[0], true))
					{
						Utf8String OldFileName = Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(OldName,
							Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(OldName));
						OnRenamed(*this, RenamedEventArgs(Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes::Renamed, Elysium::Core::Template::Functional::Move(FullPath),
							Elysium::Core::Template::Functional::Move(FileName), Elysium::Core::Template::Functional::Move(OldFileName)));
					}
				}
					break;
				default:
					// @ToDo: some sort of notification about the unhandled event-type. simply call OnError(...)?
					break;
				}

				// post-validate
				if (0 == Info->NextEntryOffset)
				{
					break;
				}

				Offset += Info->NextEntryOffset;
				if (Offset >= NumberOfBytesTransferred)
				{
					PotentialBufferOverflow = true;
					//TempErrorMessage += u8"Offset >= RawAsyncFileWatcherResult->_BytesTransferred\r\n";
					break;
				}
			} while (Offset > 0);

			// ...
			if (PotentialBufferOverflow)
			{
				// afaik there's no default windows error code for this -> .NET uses error code 0x80131671
				// @ToDo: actually check this
				OnError(*this, ErrorEventArgs(Elysium::Core::Template::Functional::Move(Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException(0x80131671,
					u8"Too many changes at once resulting in incomplete entries in directory: ..."))));	// @ToDo: use _Path
			}
		}

		inline const bool IsInterested(const char8_t* RelativePath, const bool CaseInsensitive) const noexcept
		{
			// 2.1.4.4 Algorithm for Determining if a FileName Is in an Expression
			// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-fsa/0b034646-4e23-4874-8488-2adac231ff23
			// - "Filename cannot contain any wildcard characters". The OS is not going to provide any wildcard chars so no check is required
			// - 

			// @ToDo: case insensitivity. use ToUpper like windows does in most cases (at least to my knowledge)
			const char8_t* Expression = CaseInsensitive ? &_Filter[0] : &_Filter[0];
			const char8_t* FileName = CaseInsensitive ? RelativePath : RelativePath;

			// special cases
			{
				if (nullptr == Expression)
				{
					return nullptr == FileName;
				}

				// .NET sees "*.*" as "any directory" (further filtering works through NotifyFilters)
				// @ToDo: do I want my filtering to behave in that way?
				if (nullptr == FileName)
				{
					return u8"*" == Expression || u8"*.*" == Expression;
				}

				if (u8"*" == Expression || u8"*.*" == Expression)
				{
					return true;
				}

				const Elysium::Core::Template::System::size ExpressionLength = _Filter.GetLength();
				bool ContainsFurtherWildcards = Elysium::Core::Template::Text::CharacterTraits<char8_t>::ContainsAny(&Expression[1], ExpressionLength - sizeof(char8_t), u8"\"<>*?", 4);
				if (u8'*' == Expression[0] && !ContainsFurtherWildcards)
				{

					const Elysium::Core::Template::System::size RelativePathLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(FileName);
					if (RelativePathLength < (ExpressionLength - sizeof(char8_t)))
					{
						return false;
					}

					return Elysium::Core::Template::Text::CharacterTraits<char8_t>::EndsWith(FileName, RelativePathLength, &Expression[1], ExpressionLength - sizeof(char8_t));
				}
			}

			// @ToDo: actual matching logic
			{

			}





			return true;
		}
	private:
		inline HANDLE CreateNativeDirectoryHandle(const Elysium::Core::Template::Text::StringView<char8_t> Path)
		{
			// @ToDo: don't assume correct input (Utf16::SafeToWideString)
			Elysium::Core::Template::Text::String<wchar_t> WindowsPath = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&Path[0], Path.GetLength());

			// ...
			HANDLE DirectoryHandle = CreateFile((wchar_t*)&WindowsPath[0], FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, // default security
				OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);
			if (INVALID_HANDLE_VALUE == DirectoryHandle)
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			return DirectoryHandle;
		}

		inline void BeginInitInLockedState()
		{
			_IsRunning = true;
			++_InFlightIos;
			_AllIoOperationsCompleted.Reset();
			_CurrentIoContext.Reset();
			StartThreadpoolIo(_CompletionPortHandle);
			DWORD SynchronousByteCount = 0;
			const BOOL Result = ReadDirectoryChangesExW(_DirectoryHandle, &_CurrentIoContext._InformationBuffer[0],
				static_cast<DWORD>(_CurrentIoContext._InformationBuffer.GetCapacity()), _IncludeSubdirectories,
				static_cast<DWORD>(_NotifyFilters), &SynchronousByteCount, (LPOVERLAPPED)&_CurrentIoContext._Overlapped, nullptr,
				READ_DIRECTORY_NOTIFY_INFORMATION_CLASS::ReadDirectoryNotifyExtendedInformation);

			const DWORD ErrorCode = GetLastError();
			if (FALSE == Result)
			{
				if (ERROR_IO_PENDING != ErrorCode)
				{	// https://learn.microsoft.com/en-us/windows/win32/api/threadpoolapiset/nf-threadpoolapiset-cancelthreadpoolio
					// To prevent memory leaks, you must call the CancelThreadpoolIo function for either of the following scenarios:
					// - An overlapped (asynchronous) I/O operation fails (that is, the asynchronous I/O function call returns failure with an error code other than ERROR_IO_PENDING).
					// - "...notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS..." isn't the case here as I do not call
					// SetFileCompletionNotificationModes(...) with FILE_SKIP_COMPLETION_PORT_ON_SUCCESS anywhere in this class.
					CancelThreadpoolIo(_CompletionPortHandle);

					_IsRunning = false;
					if (0 == --_InFlightIos)
					{
						_AllIoOperationsCompleted.Set();
					}
					_IocpIsRunningOrDestructingMutex.Unlock();
					throw Elysium::Core::Template::Exceptions::IO::IOException(ErrorCode);
				}
			}
			else
			{
				bool sdfsdf = false;
			}
		}
	private:
		inline static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
		{
			FileSystemWatcher* Watcher = reinterpret_cast<FileSystemWatcher*>(Context);
			IoContext* CurrentIoContext = reinterpret_cast<IoContext*>(Overlapped);

			if (NO_ERROR == IoResult)
			{
				Watcher->ProcessInformationBuffer(*CurrentIoContext, IoResult, NumberOfBytesTransferred);
			}


			Watcher->_IocpIsRunningOrDestructingMutex.Lock();

			if (Watcher->_IsRunning && !Watcher->_IsDestructing)
			{
				Watcher->BeginInitInLockedState();
			}

			Watcher->_IocpIsRunningOrDestructingMutex.Unlock();

			if (0 == --Watcher->_InFlightIos)
			{
				Watcher->_AllIoOperationsCompleted.Set();
			}
			/*
			switch (IoResult)
			{
			case NO_ERROR:	// 0
				// "default" result - nothing to do here
				break;
			case ERROR_OPERATION_ABORTED:	// 995
			{	// EndInit(...) has been called (either through public method or destructor)
				if (0 == --Watcher->_InFlightIos)
				{
					Watcher->_AllIoOperationsCompleted.Set();
				}

				Watcher->_IocpIsRunningOrDestructingMutex.Lock();
				Watcher->_IsRunning = false;
				Watcher->_IocpIsRunningOrDestructingMutex.Unlock();
			}
				return;
			default:
				break;
			}

			Watcher->ProcessInformationBuffer(*CurrentIoContext, IoResult, NumberOfBytesTransferred);
			if (0 == --Watcher->_InFlightIos)
			{
				Watcher->_AllIoOperationsCompleted.Set();
			}

			Watcher->_IocpIsRunningOrDestructingMutex.Lock();
			Watcher->_IsRunning = false;
			Watcher->_IocpIsRunningOrDestructingMutex.Unlock();

			Watcher->BeginInit();
			*/
		}
	public:
		Elysium::Core::Template::Dispatch::Event<false, true, true, void, const FileSystemWatcher&, const FileSystemEventArgs<>&> OnChanged{};

		Elysium::Core::Template::Dispatch::Event<false, true, true, void, const FileSystemWatcher&, const FileSystemEventArgs<>&> OnCreated{};

		Elysium::Core::Template::Dispatch::Event<false, true, true, void, const FileSystemWatcher&, const FileSystemEventArgs<>&> OnDeleted{};
		
		Elysium::Core::Template::Dispatch::Event<false, true, true, void, const FileSystemWatcher&, const ErrorEventArgs<>&> OnError{};

		Elysium::Core::Template::Dispatch::Event<false, true, true, void, const FileSystemWatcher&, const RenamedEventArgs<>&> OnRenamed{};
	private:
		Elysium::Core::Template::Text::String<char8_t> _Path;
		Elysium::Core::Template::Text::String<char8_t> _Filter;
		Elysium::Core::Template::IO::FileSystem::NotifyFilters _NotifyFilters;
		bool _IncludeSubdirectories;
		Elysium::Core::Template::System::size _InternalBufferSize;

		IoContext _CurrentIoContext;

		HANDLE _DirectoryHandle;
		PTP_IO _CompletionPortHandle;

		Elysium::Core::Template::Threading::Atomic<bool> _IsRunning{};		// temporarily "closed"
		Elysium::Core::Template::Threading::Atomic<bool> _IsDestructing{};	// permanently "closed"
		Elysium::Core::Template::Threading::Mutex _IocpIsRunningOrDestructingMutex{};	// prevents submitting while already running or destructing

		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::size> _InFlightIos{};	// counts in flight ios (in this case only 0 or 1) so I don't wait if there's nothing in flight
		Elysium::Core::Template::Threading::ManualResetEvent _AllIoOperationsCompleted = Elysium::Core::Template::Threading::ManualResetEvent(true);	// lets EndInit() wait until _InFlightIos is 0
	};
}
#endif
#endif
