/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DRAWING_IMAGE
#define ELYSIUM_CORE_DRAWING_IMAGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DRAWING_API
#include "API.hpp"
#endif

namespace Elysium::Core::Drawing
{
	class ELYSIUM_CORE_DRAWING_API Image
	{
	protected:
		Image();
	public:
		Image(const Image& Source) = delete;

		Image(Image&& Right) noexcept = delete;

		virtual ~Image();
	public:
		Image& operator=(const Image& Source) = delete;

		Image& operator=(Image&& Right) noexcept = delete;
	};
}
#endif
