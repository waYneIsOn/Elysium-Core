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

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "../Elysium.Core/AsyncResult.hpp"
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
		FileSystemWatcherAsyncResult(const Elysium::Core::Template::System::size BufferSize,
			const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback,
			const void* AsyncState, const Elysium::Core::size Position, PTP_IO CompletionPortHandle);
	public:
		FileSystemWatcherAsyncResult(const FileSystemWatcherAsyncResult& Source) = delete;

		FileSystemWatcherAsyncResult(FileSystemWatcherAsyncResult&& Right) noexcept = delete;

		virtual ~FileSystemWatcherAsyncResult() override = default;
	public:
		FileSystemWatcherAsyncResult& operator=(const FileSystemWatcherAsyncResult& Source) = delete;

		FileSystemWatcherAsyncResult& operator=(FileSystemWatcherAsyncResult&& Right) noexcept = delete;
	private:
		Elysium::Core::Container::VectorOfByte _InformationBuffer;
		Elysium::Core::size _BytesTransferred;
	};
}
#endif
