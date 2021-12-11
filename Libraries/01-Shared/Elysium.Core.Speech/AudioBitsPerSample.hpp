/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_AUDIOBITSPERSAMPLE
#define ELYSIUM_CORE_SPEECH_AUDIOFORMAT_AUDIOBITSPERSAMPLE

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
	enum class AudioBitsPerSample : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class AudioBitsPerSample
#else
#error "undefined os"
#endif
	{
		Eight = 8,

		Sixteen = 16
	};
}
#endif
