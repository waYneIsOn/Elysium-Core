/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKSTARTEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKSTARTEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS
#include "PromptEventArgs.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API SpeakStartedEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		SpeakStartedEventArgs(Elysium::Core::Utf8String&& Prompt);
	public:
		SpeakStartedEventArgs(const SpeakStartedEventArgs& Source) = delete;

		SpeakStartedEventArgs(SpeakStartedEventArgs&& Right) noexcept = delete;

		virtual ~SpeakStartedEventArgs();
	public:
		SpeakStartedEventArgs& operator=(const SpeakStartedEventArgs& Source) = delete;

		SpeakStartedEventArgs& operator=(SpeakStartedEventArgs&& Right) noexcept = delete;
	};
}
#endif
