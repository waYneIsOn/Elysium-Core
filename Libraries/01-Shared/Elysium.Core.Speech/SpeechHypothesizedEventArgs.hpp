/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHHYPOTHESIZEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHHYPOTHESIZEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONRESULT
#include "RecognitionResult.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONEVENTARGS
#include "RecognitionEventArgs.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API SpeechHypothesizedEventArgs final : public RecognitionEventArgs
	{
		friend class SpeechRecognitionEngine;
	protected:
		SpeechHypothesizedEventArgs(RecognitionResult&& Result);
	public:
		SpeechHypothesizedEventArgs(const SpeechHypothesizedEventArgs& Source) = delete;

		SpeechHypothesizedEventArgs(SpeechHypothesizedEventArgs&& Right) noexcept = delete;

		virtual ~SpeechHypothesizedEventArgs();
	public:
		SpeechHypothesizedEventArgs& operator=(const SpeechHypothesizedEventArgs& Source) = delete;

		SpeechHypothesizedEventArgs& operator=(SpeechHypothesizedEventArgs&& Right) noexcept = delete;
	};
}
#endif
