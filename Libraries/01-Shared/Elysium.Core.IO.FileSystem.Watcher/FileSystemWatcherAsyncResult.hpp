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

		virtual ~FileSystemWatcherAsyncResult();
	public:
		FileSystemWatcherAsyncResult& operator=(const FileSystemWatcherAsyncResult& Source) = delete;

		FileSystemWatcherAsyncResult& operator=(FileSystemWatcherAsyncResult&& Right) noexcept = delete;
	public:
		constexpr const FileSystemWatcher& GetWatcher() const;
	private:
		inline static constexpr const Elysium::Core::size _InformationBufferSize = sizeof(FILE_NOTIFY_EXTENDED_INFORMATION) + 256 * sizeof(wchar_t);
		//inline static constexpr const Elysium::Core::size _InformationBufferSize = sizeof(FILE_NOTIFY_EXTENDED_INFORMATION);
	private:
		FileSystemWatcher& _Watcher;
		Elysium::Core::size _BytesTransferred;

		Elysium::Core::byte _InformationBuffer[_InformationBufferSize];
	};
}
#endif
