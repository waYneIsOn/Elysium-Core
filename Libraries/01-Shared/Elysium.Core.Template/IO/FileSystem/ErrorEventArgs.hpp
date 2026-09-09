/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_ERROREVENTEVENTARGS
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_ERROREVENTEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_INTERNALBUFFEROVERFLOWEXCEPTION
#include "../../Exceptions/IO/InternalBufferOverflowException.hpp"
#endif

namespace Elysium::Core::Template::IO::FileSystem
{
	class FileSystemWatcher;

	class ErrorEventArgs
	{
		friend class FileSystemWatcher;
	public:
		constexpr ErrorEventArgs() = delete;
	protected:
		inline constexpr ErrorEventArgs(Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException&& Exception)
			: _Exception(Elysium::Core::Template::Functional::Move(Exception))
		{ }
	public:
		constexpr ErrorEventArgs(const ErrorEventArgs& Source) = delete;

		constexpr ErrorEventArgs(ErrorEventArgs&& Right) noexcept = delete;

		constexpr ~ErrorEventArgs() noexcept = default;
	public:
		constexpr ErrorEventArgs& operator=(const ErrorEventArgs& Source) = delete;

		constexpr ErrorEventArgs& operator=(ErrorEventArgs&& Right) noexcept = delete;
	public:
		inline const Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException& GetException() const
		{
			return _Exception;
		}
	private:
		const Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException _Exception;
	};
}
#endif
