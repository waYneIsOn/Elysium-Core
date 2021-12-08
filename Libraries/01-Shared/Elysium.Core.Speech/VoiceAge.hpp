/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEAGE
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEAGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class VoiceAge : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class VoiceAge
#else
#error "undefined os"
#endif
	{
		NotSet = 0,

		Child = 10,

		Teen = 15,

		Adult = 30,

		Senior = 65
	};
}
#endif
