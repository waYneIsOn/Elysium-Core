/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZEREMPHASIS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZEREMPHASIS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SynthesizerEmphasis : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class SynthesizerEmphasis
#else
#error "undefined os"
#endif
	{
		Stressed = 1,

		Emphasized = 2
	};
}
#endif
