/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#define ELYSIUM_CORE_IO_DIRECTORY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API Directory final
	{
	public:
		Directory() = delete;

		Directory(const Directory& Source) = delete;

		Directory(Directory&& Right) noexcept = delete;

		~Directory() = delete;
	public:
		Directory& operator=(const Directory& Source) = delete;

		Directory& operator=(Directory&& Right) noexcept = delete;
	public:
		/*
		static void Delete(const char8_t* Path);

		static constexpr const bool Exists(const char8_t* Path) noexcept;
		*/
	};
}
#endif
