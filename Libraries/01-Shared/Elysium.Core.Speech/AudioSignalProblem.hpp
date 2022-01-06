/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSIGNALPROBLEM
#define ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSIGNALPROBLEM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class AudioSignalProblem : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class AudioSignalProblem
#else
#error "undefined os"
#endif
	{
        None = 0,

        TooNoisy = 1,

        NoSignal = 2,

        TooLoud = 3,

        TooSoft = 4,

        TooFast = 5,

        TooSlow = 6
	};
}
#endif
