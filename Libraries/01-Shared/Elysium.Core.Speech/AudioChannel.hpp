/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_AUDIOCHANNEL
#define ELYSIUM_CORE_SPEECH_AUDIOFORMAT_AUDIOCHANNEL

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
	enum class AudioChannel : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class AudioChannel
#else
#error "undefined os"
#endif
	{
		Mono = 1,

		Stereo = 2
	};
}
#endif
