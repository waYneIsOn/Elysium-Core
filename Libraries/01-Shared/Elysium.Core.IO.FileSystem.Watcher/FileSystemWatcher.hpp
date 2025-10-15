/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESYSTEMWATCHER
#define ELYSIUM_CORE_IO_FILESYSTEMWATCHER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENT
#include "../Elysium.Core/Event.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_ERROREVENTARGS
#include "ErrorEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEMEVENTARGS
#include "FileSystemEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEMWATCHERASYNCRESULT
#include "FileSystemWatcherAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_NOTIFYFILTERS
#include "NotifyFilters.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_RENAMEDEVENTARGS
#include "RenamedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "../Elysium.Core.Template/UniquePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_ATOMIC
#include "../Elysium.Core.Threading/Atomic.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif
#else
#error "undefined os"
#endif

namespace Elysium::Core::IO
{
	class FileSystemWatcher;
	/*
	template class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>;
	template class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>;
	template class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>;
	*-/
	template class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER Event<void, const FileSystemWatcher&, const FileSystemEventArgs&>;
	template class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER Event<void, const FileSystemWatcher&, const ErrorEventArgs&>;
	template class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER Event<void, const FileSystemWatcher&, const RenamedEventArgs&>;
	*/
	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER FileSystemWatcher
	{
	private:
		FileSystemWatcher();
	public:
		FileSystemWatcher(const char8_t* Path, const char8_t* Filter = u8"*.*", const NotifyFilters NotifyFilters = DefaultNotifyFilters, 
			const bool IncludeSubdirectories = false, const Elysium::Core::Template::System::size InternalBufferSize = _SafeInformationBufferSize);

		FileSystemWatcher(const FileSystemWatcher& Source) = delete;

		FileSystemWatcher(FileSystemWatcher&& Right) noexcept = delete;

		~FileSystemWatcher();
	public:
		FileSystemWatcher& operator=(const FileSystemWatcher& Source) = delete;

		FileSystemWatcher& operator=(FileSystemWatcher&& Right) noexcept = delete;
	public:
		const NotifyFilters GetNotifyFilters() const;

		const bool GetIncludeSubdirectories() const;

		const Utf8String& GetPath() const;

		const Utf8String& GetFilter() const;
	public:
		void BeginInit();

		void EndInit();
	public:
		Event<void, const FileSystemWatcher&, const FileSystemEventArgs&> OnChanged;

		Event<void, const FileSystemWatcher&, const FileSystemEventArgs&> OnCreated;

		Event<void, const FileSystemWatcher&, const FileSystemEventArgs&> OnDeleted;

		Event<void, const FileSystemWatcher&, const ErrorEventArgs&> OnError;

		Event<void, const FileSystemWatcher&, const RenamedEventArgs&> OnRenamed;
	private:
		const bool IsInterested(const char8_t* RelativePath);

		void Process(Elysium::Core::Template::Memory::ObserverPointer<Elysium::Core::IAsyncResult> AsyncResult);

		static void CleanUp(FileSystemWatcherAsyncResult* RawAsyncFileWatcherResult, const bool WasSuccessful);
	public:
		/// <summary>
		/// 
		/// </summary>
		inline static constexpr const NotifyFilters DefaultNotifyFilters = NotifyFilters::LastWrite | NotifyFilters::FileName | NotifyFilters::DirectoryName;
		
		/// <summary>
		/// 4kb is the default memory page size on windows (x86 and x64).
		/// This should be used with a low event volume where the use of minimal memory suffices.
		/// </summary>
		inline static constexpr const Elysium::Core::size _MinimumInformationBufferSize = 4096;

		/// <summary>
		/// 64kb appears to be the safe upper bound for compatibility across all filesystems on windows.
		/// This appears to be the sweet spot in regards to safety, compatibility and efficiency.
		/// (Chromium, VS Code etc. appear to be using this value - with overflow detection/resilience logic.)
		/// </summary>
		inline static constexpr const Elysium::Core::size _SafeInformationBufferSize = 65536;

		/// <summary>
		/// 128-256kb works but might be risky in some filesystems.
		/// This can be used for high frequency event volume.
		/// </summary>
		inline static constexpr const Elysium::Core::size _MaximumInformationBufferSize = 262144;
	private:
		NotifyFilters _NotifyFilters;
		bool _IncludeSubdirectories;
		Utf8String _Path;
		Utf8String _Filter;
		Elysium::Core::Template::System::size _InternalBufferSize;

		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint8_t> _InFlightIos = 0;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint8_t> _RunningCallbacks = 0;
		Elysium::Core::Template::Threading::Atomic<bool> _IsEnding = false;

		Elysium::Core::Template::Threading::Atomic<FileSystemWatcherAsyncResult*> _AddressOfLatestAsyncResult;

#if defined ELYSIUM_CORE_OS_WINDOWS
		HANDLE _DirectoryHandle;
		PTP_IO _CompletionPort;
	private:
		HANDLE CreateNativeDirectoryHandle(const char8_t* Path, const size_t PathLength);

		static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult,
			ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);
#else
#error "undefined os"
#endif
	};
}
#endif
