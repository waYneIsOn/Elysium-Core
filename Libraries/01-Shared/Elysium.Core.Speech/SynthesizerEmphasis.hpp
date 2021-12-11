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

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class SynthesizerEmphasis : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
