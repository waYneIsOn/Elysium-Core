/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../../Container/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_DELEGATEAWAITER
#include "../../Coroutines/Awaiter/DelegateAwaiter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_GETCURRENTPROMISEAWAITER
#include "../../Coroutines/Awaiter/GetCurrentPromiseAwaiter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_IOEXCEPTION
#include "../../Exceptions/IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEACCESS
#include "../FileAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEMODE
#include "../FileMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEOPTIONS
#include "../FileOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESHARE
#include "../FileShare.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_SEEKORIGIN
#include "../SeekOrigin.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_OBSERVERPOINTER
#include "../../Memory/ObserverPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "../../Memory/UniquePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASK
#include "../../Threading/Tasks/Task.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../../Text/Unicode/Utf16.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#ifndef _APISETHANDLE_
#include <handleapi.h>
#endif
/*
#ifndef _APISETFILE_
#include <fileapi.h>
#endif
*/
#elif defined ELYSIUM_CORE_OS_ANDROID

#else
#error "undefined os"
#endif

namespace Elysium::Core::Template::IO::Device
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	class FileDevice
	{
	public:
		constexpr FileDevice() noexcept = delete;

		inline constexpr FileDevice(const char8_t* Path, const FileMode Mode, const FileAccess Access = FileAccess::Read | FileAccess::Write, const FileShare Share = FileShare::None,
			const Elysium::Core::Template::System::uint32_t BufferSize = 4096, const FileOptions Options = FileOptions::None)
			: _FQFN(GetFQFN(Path)), _Position(0)
			, _FileHandle(CreateNativeFileHandle(_FQFN, Mode, Access, Share, Options | FileOptions::Asynchronous)),
			_CompletionPortHandle(CreateThreadpoolIo(_FileHandle, &IOCompletionPortCallback, this, &Elysium::Core::Template::Threading::ThreadPool::GetIOPool()._Environment)),
			_IocpIsClosingMutex{}, _IsClosing {}, _InFlightIos{}, _AllIoOperationsCompleted(true)
		{ }

		constexpr FileDevice(const FileDevice& Source) = delete;

		constexpr FileDevice(FileDevice&& Right) noexcept = delete;

		inline constexpr ~FileDevice()
		{
			Close();
		}
	public:
		constexpr FileDevice& operator=(const FileDevice& Source) = delete;

		constexpr FileDevice& operator=(FileDevice&& Right) noexcept = delete;
	public:
		inline constexpr const bool operator==(const FileDevice& Other) const noexcept
		{
			// @ToDo: invariant comparison!
			return _FQFN == Other._FQFN;
		}

		inline constexpr const bool operator!=(const FileDevice& Other) const noexcept
		{
			// @ToDo: invariant comparison!
			return _FQFN != Other._FQFN;
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			LARGE_INTEGER Size;
			if (FALSE == GetFileSizeEx(_FileHandle, &Size))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			return Size.QuadPart;
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _Position;
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			Seek(Position, SeekOrigin::Begin);
		}
	public:
		inline void Close()
		{
			_IocpIsClosingMutex.Lock();

			if (INVALID_HANDLE_VALUE == _FileHandle)
			{
				_IocpIsClosingMutex.Unlock();
				return;
			}

			_IsClosing = true;
			_IocpIsClosingMutex.Unlock();

			// request cancellation of all outstanding IOCP operations and wait for them to finish
			CancelIoEx(_FileHandle, nullptr);
			_AllIoOperationsCompleted.WaitOne();

			if (_CompletionPortHandle != nullptr)
			{
				// wait for CALLBACKS that are queued/running
				WaitForThreadpoolIoCallbacks(_CompletionPortHandle, TRUE);
				
				CloseThreadpoolIo(_CompletionPortHandle);
				_CompletionPortHandle = nullptr;
			}

			if (FALSE == CloseHandle(_FileHandle))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			_FileHandle = INVALID_HANDLE_VALUE;
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size Seek(const Elysium::Core::Template::System::int64_t Offset, const SeekOrigin Origin)
		{
			LARGE_INTEGER InternalPosition = LARGE_INTEGER();
			InternalPosition.QuadPart = Offset;

			LARGE_INTEGER NewPosition;

			if (FALSE == SetFilePointerEx(_FileHandle, InternalPosition, &NewPosition, static_cast<unsigned long>(Origin)))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			_Position = NewPosition.QuadPart;

			return _Position;
		}
	public:
		inline const Elysium::Core::Template::System::size Read(Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				//return 0;
				throw 1;
				//throw ArgumentNullException(u8"Buffer");
			}

			Elysium::Core::Template::System::uint32_t BytesRead = 0;
			if (FALSE == ReadFile(_FileHandle, Buffer, static_cast<DWORD>(Count), reinterpret_cast<unsigned long*>(&BytesRead), nullptr))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}
			_Position += BytesRead;

			return BytesRead;
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				return;
			}
			
			Elysium::Core::Template::System::uint32_t TotalBytesWritten = 0;
			Elysium::Core::Template::System::uint32_t BytesWritten = 0;
			do
			{
				if (FALSE == WriteFile(_FileHandle, &Buffer[TotalBytesWritten], static_cast<unsigned long>(Count - TotalBytesWritten), reinterpret_cast<unsigned long*>(&BytesWritten), nullptr))
				{
					throw Elysium::Core::Template::Exceptions::IO::IOException();
				}
				TotalBytesWritten += BytesWritten;
				_Position += BytesWritten;
			} while (TotalBytesWritten != Count);
		}

		inline void Flush(const bool FlushToDisk = true)
		{
			if (!FlushToDisk)
			{
				return;
			}

			// @ToDo: early exit if no write permission was requested
			if (INVALID_HANDLE_VALUE == _FileHandle)
			{
				return;
			}

			if (FALSE == FlushFileBuffers(_FileHandle))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}
		}
	public:
		inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> WriteAsync(const Elysium::Core::Template::System::byte* Buffer, 
			const Elysium::Core::Template::System::size Length)
		{
			_IocpIsClosingMutex.Lock();
			if (_IsClosing)
			{	
				_IocpIsClosingMutex.Unlock();

				// @ToDo: throw specific exception
				throw 1;
			}

			Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType& Promise =
				co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType>{};
			Promise._Overlapped.Offset = static_cast<DWORD>(_Position);
			Promise._Overlapped.OffsetHigh = static_cast<DWORD>(_Position >> 32);

			++_InFlightIos;
			_AllIoOperationsCompleted.Reset();
			StartThreadpoolIo(_CompletionPortHandle);
			DWORD SynchronousByteCount = 0;
			const BOOL Result = WriteFile(_FileHandle, (void*)&Buffer[0], static_cast<DWORD>(Length), &SynchronousByteCount, &Promise._Overlapped);
			//const BOOL Result = WriteFileEx(_FileHandle, (void*)&Buffer[0], static_cast<DWORD>(Length), &AsyncResult->_Overlapped, (LPOVERLAPPED_COMPLETION_ROUTINE)nullptr);

			const DWORD ErrorCode = GetLastError();
			_IocpIsClosingMutex.Unlock();
			if (FALSE == Result)
			{
				if (ERROR_IO_PENDING != ErrorCode)
				{	// https://learn.microsoft.com/en-us/windows/win32/api/threadpoolapiset/nf-threadpoolapiset-cancelthreadpoolio
					// To prevent memory leaks, you must call the CancelThreadpoolIo function for either of the following scenarios:
					// - An overlapped (asynchronous) I/O operation fails (that is, the asynchronous I/O function call returns failure with an error code other than ERROR_IO_PENDING).
					// - "...notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS..." isn't the case here as I do not call
					// SetFileCompletionNotificationModes(...) with FILE_SKIP_COMPLETION_PORT_ON_SUCCESS anywhere in this class.
					CancelThreadpoolIo(_CompletionPortHandle);

					if (0 == --_InFlightIos)
					{
						_AllIoOperationsCompleted.Set();
					}
					throw Elysium::Core::Template::Exceptions::IO::IOException(ErrorCode);
				}

				// current coroutine needs to suspend and wait for IOCP
				co_await Elysium::Core::Template::Coroutines::Awaiter::SuspendAlways{};

				co_return Promise._Result;
			}
			else
			{
				Promise._HasCompletedSynchronously = true;
				if (0 == --_InFlightIos)
				{
					_AllIoOperationsCompleted.Set();
				}
				co_return SynchronousByteCount;
			}
		}

		inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> ReadAsync(const Elysium::Core::Template::System::byte* Buffer, 
			const Elysium::Core::Template::System::size Length)
		{
			_IocpIsClosingMutex.Lock();
			if (_IsClosing)
			{
				_IocpIsClosingMutex.Unlock();
				
				// @ToDo: throw specific exception
				throw 1;
			}

			Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType& Promise =
				co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType>{};
			Promise._Overlapped.Offset = static_cast<DWORD>(_Position);
			Promise._Overlapped.OffsetHigh = static_cast<DWORD>(_Position >> 32);
			
			++_InFlightIos;
			_AllIoOperationsCompleted.Reset();
			StartThreadpoolIo(_CompletionPortHandle);
			DWORD SynchronousByteCount = 0;
			const BOOL Result = ReadFile(_FileHandle, (void*)&Buffer[0], static_cast<DWORD>(Length), &SynchronousByteCount, &Promise._Overlapped);
			//const BOOL Result = ReadFileEx(_FileHandle, (void*)&Buffer[0], static_cast<DWORD>(Length), &AsyncResult->_Overlapped, (LPOVERLAPPED_COMPLETION_ROUTINE)nullptr);

			const DWORD ErrorCode = GetLastError();
			_IocpIsClosingMutex.Unlock();
			if (FALSE == Result)
			{
				if (ERROR_IO_PENDING != ErrorCode)
				{	// https://learn.microsoft.com/en-us/windows/win32/api/threadpoolapiset/nf-threadpoolapiset-cancelthreadpoolio
					// To prevent memory leaks, you must call the CancelThreadpoolIo function for either of the following scenarios:
					// - An overlapped (asynchronous) I/O operation fails (that is, the asynchronous I/O function call returns failure with an error code other than ERROR_IO_PENDING).
					// - "...notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS..." isn't the case here as I do not call
					// SetFileCompletionNotificationModes(...) with FILE_SKIP_COMPLETION_PORT_ON_SUCCESS anywhere in this class.
					CancelThreadpoolIo(_CompletionPortHandle);

					if (0 == --_InFlightIos)
					{
						_AllIoOperationsCompleted.Set();
					}
					throw Elysium::Core::Template::Exceptions::IO::IOException(ErrorCode);
				}

				// current coroutine needs to suspend and wait for IOCP
				co_await Elysium::Core::Template::Coroutines::Awaiter::SuspendAlways{};

				co_return Promise._Result;
			}
			else
			{
				Promise._HasCompletedSynchronously = true;
				if (0 == --_InFlightIos)
				{
					_AllIoOperationsCompleted.Set();
				}
				co_return SynchronousByteCount;
			}
		}
	private:
		inline Elysium::Core::Template::Text::String<char8_t> GetFQFN(const char8_t* Path)
		{
			Elysium::Core::Template::Text::String<char8_t> Result{};

			// @ToDo
			return Path;
		}

		inline HANDLE CreateNativeFileHandle(const Elysium::Core::Template::Text::String<char8_t>& FQFN, const FileMode Mode, const FileAccess Access, const FileShare Share,
			const FileOptions Options)
		{
			Elysium::Core::Template::Text::String<wchar_t> WindowsFQPN = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&FQFN[0], FQFN.GetLength());

			HANDLE NativeFileHandle = CreateFile(&WindowsFQPN[0], static_cast<Elysium::Core::Template::System::uint32_t>(Access),
				static_cast<Elysium::Core::Template::System::uint32_t>(Share),
				nullptr, // default security
				static_cast<Elysium::Core::Template::System::uint32_t>(Mode), static_cast<Elysium::Core::Template::System::int32_t>(Options), nullptr);
			//CreateFile2()

			if (INVALID_HANDLE_VALUE == NativeFileHandle)
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			return NativeFileHandle;
		}
	private:
		inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> WriteAsyncInternally(OVERLAPPED Overlapped,
			const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Length)
		{
			throw 1;
		}

		inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> ReadAsyncInternally(OVERLAPPED Overlapped, 
			const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Length)
		{
			throw 1;
		}
	private:
		inline static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
		{
			// ...
			Elysium::Core::Template::IO::Device::FileDevice* Device = static_cast<Elysium::Core::Template::IO::Device::FileDevice*>(Context);
			
			Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType* Promise =
				static_cast<Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType*>(Overlapped);
			
			Device->_Position += NumberOfBytesTransferred;
			Promise->_ErrorCode = IoResult;
			Promise->_Result = NumberOfBytesTransferred;

			Promise->_Handle.resume();

			if (0 == --Device->_InFlightIos)
			{
				Device->_AllIoOperationsCompleted.Set();
			}

			/*
			// ...
			switch (IoResult)
			{
			case NO_ERROR:	// 0
				// "default" result - nothing to do here
				break;
			case ERROR_OPERATION_ABORTED:	// 995
			{	// @ToDo
				throw 1;
			}
				return;
			default:
				break;
			}
			*/
		}
	private:
		Elysium::Core::Template::Text::String<char8_t> _FQFN;
		Elysium::Core::Template::System::size _Position;

		HANDLE _FileHandle;
		PTP_IO _CompletionPortHandle;

		Elysium::Core::Template::Threading::Mutex _IocpIsClosingMutex;	// prevents submitting while already closing
		Elysium::Core::Template::Threading::Atomic<bool> _IsClosing;	// 
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::size> _InFlightIos;
		Elysium::Core::Template::Threading::ManualResetEvent _AllIoOperationsCompleted;	// lets Close() wait until _InFlightIos is 0
	};
#endif
}
#endif
