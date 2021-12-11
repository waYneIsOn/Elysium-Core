/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_ENCODINGFORMAT
#define ELYSIUM_CORE_SPEECH_AUDIOFORMAT_ENCODINGFORMAT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Speech::AudioFormat
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class EncodingFormat : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class EncodingFormat
#else
#error "undefined os"
#endif
	{
		Pcm = 1,

		ALaw = 6,

		ULaw = 7
	};
}
#endif
