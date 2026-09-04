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

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _APISETFILE_
#include <fileapi.h>
#endif

#ifndef _THREADPOOLAPISET_H_
#include <threadpoolapiset.h>
#endif

namespace Elysium::Core::Template::IO::FileSystem
{
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
	public:
		constexpr FileSystemWatcher() = delete;

		inline constexpr FileSystemWatcher(const Elysium::Core::Template::Text::StringView<char8_t> Path, const Elysium::Core::Template::Text::StringView<char8_t> Filter = u8"*.*",
			const Elysium::Core::Template::IO::FileSystem::NotifyFilters NotifyFilters = DefaultNotifyFilters, const bool IncludeSubdirectories = false,
			const Elysium::Core::Template::System::size InternalBufferSize = SafeInformationBufferSize)
			: _DirectoryHandle(CreateNativeDirectoryHandle(Path)), 
			_CompletionPort(CreateThreadpoolIo(_DirectoryHandle, IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::GetIOPool()._Environment)),
			_Path(Path), _Filter(Filter), _NotifyFilters(NotifyFilters), _IncludeSubdirectories(IncludeSubdirectories), _InternalBufferSize(InternalBufferSize)
		{ }

		constexpr FileSystemWatcher(const FileSystemWatcher& Source) = delete;

		constexpr FileSystemWatcher(FileSystemWatcher&& Right) noexcept = delete;

		inline constexpr ~FileSystemWatcher()
		{

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

		}

		inline void EndInit()
		{

		}
	private:
		/*
		inline const bool IsInterested(const char8_t* RelativePath, const bool CaseInsensitive)
		{

		}

		inline void Process(Elysium::Core::Template::Memory::ObserverPointer<Elysium::Core::IAsyncResult> AsyncResult)
		{

		}
		*/
	private:
		inline HANDLE CreateNativeDirectoryHandle(const Elysium::Core::Template::Text::StringView<char8_t> Path)
		{
			// @ToDo: don't assume correct input (Utf16::SafeToWideString)
			Elysium::Core::WideString WindowsPath = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Path, Path.GetLength());

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
	private:
		inline static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult,
			ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
		{
			bool sdf = false;
		}
	public:
		/*
		Event<void, const FileSystemWatcher&, const FileSystemEventArgs&> OnChanged;

		Event<void, const FileSystemWatcher&, const FileSystemEventArgs&> OnCreated;

		Event<void, const FileSystemWatcher&, const FileSystemEventArgs&> OnDeleted;

		Event<void, const FileSystemWatcher&, const ErrorEventArgs&> OnError;

		Event<void, const FileSystemWatcher&, const RenamedEventArgs&> OnRenamed;
		*/
	private:
		HANDLE _DirectoryHandle;
		PTP_IO _CompletionPort;

		Elysium::Core::Template::Text::String<char8_t> _Path;
		Elysium::Core::Template::Text::String<char8_t> _Filter;
		Elysium::Core::Template::IO::FileSystem::NotifyFilters _NotifyFilters;
		bool _IncludeSubdirectories;
		Elysium::Core::Template::System::size _InternalBufferSize;

		Elysium::Core::Template::Threading::Mutex _IocpIsClosingMutex{};	// prevents submitting while already closing
		Elysium::Core::Template::Threading::Atomic<bool> _IsClosing{};	// 
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::size> _InFlightIos{};
		Elysium::Core::Template::Threading::ManualResetEvent _AllIoOperationsCompleted(true);	// lets Close() wait until _InFlightIos is 0
	};
}
#endif
#endif
