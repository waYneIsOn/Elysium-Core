/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKCOMPLETEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKCOMPLETEDEVENTARGS

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
	class ELYSIUM_CORE_SPEECH_API SpeakCompletedEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		SpeakCompletedEventArgs(Elysium::Core::Utf8String&& Prompt);
	public:
		SpeakCompletedEventArgs(const SpeakCompletedEventArgs& Source) = delete;

		SpeakCompletedEventArgs(SpeakCompletedEventArgs&& Right) noexcept = delete;

		virtual ~SpeakCompletedEventArgs();
	public:
		SpeakCompletedEventArgs& operator=(const SpeakCompletedEventArgs& Source) = delete;

		SpeakCompletedEventArgs& operator=(SpeakCompletedEventArgs&& Right) noexcept = delete;
	};
}
#endif
