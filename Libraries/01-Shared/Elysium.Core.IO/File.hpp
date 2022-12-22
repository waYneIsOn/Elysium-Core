/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILE
#define ELYSIUM_CORE_IO_FILE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API File final
	{
	public:
		File() = delete;

		File(const File& Source) = delete;

		File(File&& Right) noexcept = delete;

		~File() = delete;
	public:
		File& operator=(const File& Source) = delete;

		File& operator=(File&& Right) noexcept = delete;
	public:
		static void Delete(const char8_t* Path);

		static void Move(const char8_t* SourceFileName, const char8_t* DestinationFileName, const bool Overwrite = false);
	};
}
#endif
