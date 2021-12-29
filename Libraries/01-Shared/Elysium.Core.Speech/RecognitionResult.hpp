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

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API RecognitionResult final
	{
		friend class SpeechRecognitionEngine;
	protected:
		RecognitionResult();
	public:
		RecognitionResult(const RecognitionResult& Source) = delete;

		RecognitionResult(RecognitionResult&& Right) noexcept;

		~RecognitionResult();
	public:
		RecognitionResult& operator=(const RecognitionResult& Source) = delete;

		RecognitionResult& operator=(RecognitionResult&& Right) noexcept;
	};
}
#endif
