/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEGENDER
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEGENDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class VoiceGender : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class VoiceGender
#else
#error "undefined os"
#endif
	{
		NotSet = 0,

		Male = 1,

		Female = 2,

		Neutral = 3,
	};
}
#endif
