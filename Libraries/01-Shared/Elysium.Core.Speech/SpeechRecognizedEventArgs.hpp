/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNIZEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNIZEDEVENTARGS

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
	class ELYSIUM_CORE_SPEECH_API SpeechRecognizedEventArgs final : public RecognitionEventArgs
	{
		friend class SpeechRecognitionEngine;
	protected:
		SpeechRecognizedEventArgs(RecognitionResult&& Result);
	public:
		SpeechRecognizedEventArgs(const SpeechRecognizedEventArgs& Source) = delete;

		SpeechRecognizedEventArgs(SpeechRecognizedEventArgs&& Right) noexcept = delete;

		virtual ~SpeechRecognizedEventArgs();
	public:
		SpeechRecognizedEventArgs& operator=(const SpeechRecognizedEventArgs& Source) = delete;

		SpeechRecognizedEventArgs& operator=(SpeechRecognizedEventArgs&& Right) noexcept = delete;
	};
}
#endif
