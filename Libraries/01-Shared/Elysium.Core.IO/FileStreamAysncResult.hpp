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

#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "../Elysium.Core/AsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

namespace Elysium::Core::IO
{
	class FileStream;

	class ELYSIUM_CORE_API FileStreamAsyncResult final : public Elysium::Core::Internal::AsyncResult
	{
		friend class FileStream;
	private:
		FileStreamAsyncResult(FileStream& Stream, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback,
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
