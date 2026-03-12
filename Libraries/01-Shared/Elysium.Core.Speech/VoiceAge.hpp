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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class VoiceAge 
		: Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
