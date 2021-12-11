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

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class SynthesizerState : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
