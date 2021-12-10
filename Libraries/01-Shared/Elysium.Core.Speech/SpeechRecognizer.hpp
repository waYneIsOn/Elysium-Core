/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNIZER
#define ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNIZER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API SpeechRecognizer final
	{
	public:
		SpeechRecognizer();

		SpeechRecognizer(const SpeechRecognizer& Source) = delete;

		SpeechRecognizer(SpeechRecognizer&& Right) noexcept = delete;

		~SpeechRecognizer();
	public:
		SpeechRecognizer& operator=(const SpeechRecognizer& Source) = delete;

		SpeechRecognizer& operator=(SpeechRecognizer&& Right) noexcept = delete;
	};
}
#endif
