/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESTREAMASYNCRESULT
#define ELYSIUM_CORE_IO_FILESTREAMASYNCRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "../Elysium.Core/AsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif
#endif

namespace Elysium::Core::IO
{
	class FileStream;

	class ELYSIUM_CORE_API FileStreamAsyncResult final : public Elysium::Core::Internal::AsyncResult
	{
		friend class FileStream;
	private:
		FileStreamAsyncResult(FileStream& Stream, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, 
			const void* AsyncState, const Elysium::Core::size Position);
	public:
		FileStreamAsyncResult(const FileStreamAsyncResult& Source) = delete;

		FileStreamAsyncResult(FileStreamAsyncResult&& Right) noexcept = delete;

		virtual ~FileStreamAsyncResult();
	public:
		FileStreamAsyncResult& operator=(const FileStreamAsyncResult& Source) = delete;

		FileStreamAsyncResult& operator=(FileStreamAsyncResult&& Right) noexcept = delete;
	public:
		Elysium::Core::IO::FileStream& GetFileStream() const;

		const Elysium::Core::size GetBytesTransferred() const;
	private:
		FileStream& _Stream;
		Elysium::Core::size _BytesTransferred;
	};
}
#endif
