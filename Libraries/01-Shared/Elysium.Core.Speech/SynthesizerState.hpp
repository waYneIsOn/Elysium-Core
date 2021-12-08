/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZERSTATE
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZERSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SynthesizerState : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class SynthesizerState
#else
#error "undefined os"
#endif
	{
		Ready = 0,

		Speaking = 1,

		Paused = 2
	};
}
#endif
