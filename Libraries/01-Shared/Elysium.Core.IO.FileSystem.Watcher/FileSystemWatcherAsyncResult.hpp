/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESYSTEMWATCHERASYNCRESULT
#define ELYSIUM_CORE_IO_FILESYSTEMWATCHERASYNCRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "../Elysium.Core/AsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::IO
{
	class FileSystemWatcher;

	class FileSystemWatcherAsyncResult final
		: public Elysium::Core::Internal::AsyncResult
	{
		friend class FileSystemWatcher;
	private:
		FileSystemWatcherAsyncResult(FileSystemWatcher& Watcher, const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback,
			const void* AsyncState, const Elysium::Core::size Position, PTP_IO CompletionPortHandle);
	public:
		FileSystemWatcherAsyncResult(const FileSystemWatcherAsyncResult& Source) = delete;

		FileSystemWatcherAsyncResult(FileSystemWatcherAsyncResult&& Right) noexcept = delete;

		virtual ~FileSystemWatcherAsyncResult() override = default;
	public:
		FileSystemWatcherAsyncResult& operator=(const FileSystemWatcherAsyncResult& Source) = delete;

		FileSystemWatcherAsyncResult& operator=(FileSystemWatcherAsyncResult&& Right) noexcept = delete;
	public:
		constexpr const FileSystemWatcher& GetWatcher() const;
	private:
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

		/// <summary>
		/// 
		/// </summary>
		//inline static constexpr const Elysium::Core::size _InformationBufferSize = _SafeInformationBufferSize;

		inline static constexpr const Elysium::Core::size _InformationBufferSize = sizeof(FILE_NOTIFY_EXTENDED_INFORMATION) +
			256 * sizeof(wchar_t);
	private:
		FileSystemWatcher& _Watcher;
		Elysium::Core::size _BytesTransferred;

		Elysium::Core::byte _InformationBuffer[_InformationBufferSize];
	};
}
#endif
