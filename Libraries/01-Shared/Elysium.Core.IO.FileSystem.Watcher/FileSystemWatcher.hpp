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

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "../Elysium.Core.Template/Atomic.hpp"
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
	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER FileSystemWatcher
	{
	private:
		FileSystemWatcher();
	public:
		FileSystemWatcher(const char8_t* Path, const char8_t* Filter = u8"*.*", const NotifyFilters NotifyFilters = DefaultNotifyFilters, 
			const bool IncludeSubdirectories = false);

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
		void EndInit(Elysium::Core::Template::Threading::Atomic<Elysium::Core::IAsyncResult*>& AsyncResult);
	private:
		inline static const NotifyFilters DefaultNotifyFilters = NotifyFilters::LastWrite | NotifyFilters::FileName | NotifyFilters::DirectoryName;
	private:
		NotifyFilters _NotifyFilters;
		bool _IncludeSubdirectories;
		Utf8String _Path;
		Utf8String _Filter;

		Elysium::Core::Template::Threading::Atomic<FileSystemWatcherAsyncResult*> _AddressOfLatestAsyncResult;
		
#if defined ELYSIUM_CORE_OS_WINDOWS
		HANDLE _DirectoryHandle;
		PTP_IO _CompletionPortHandle;
	private:
		static HANDLE CreateNativeDirectoryHandle(const char8_t* Path, const size_t PathLength);

		static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult,
			ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);
#else
#error "undefined os"
#endif
	};
}
#endif
