/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONRESULT
#define ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNIZEDPHRASE
#include "RecognizedPhrase.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API RecognitionResult final : public RecognizedPhrase
	{
		friend class SpeechRecognitionEngine;
	protected:
		RecognitionResult(Elysium::Core::Utf8String&& Text);
	public:
		RecognitionResult(const RecognitionResult& Source) = delete;

		RecognitionResult(RecognitionResult&& Right) noexcept;

		virtual ~RecognitionResult();
	public:
		RecognitionResult& operator=(const RecognitionResult& Source) = delete;

		RecognitionResult& operator=(RecognitionResult&& Right) noexcept;
	private:
	};
}
#endif
