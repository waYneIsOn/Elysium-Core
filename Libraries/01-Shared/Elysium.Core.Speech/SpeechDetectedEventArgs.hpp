/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHDETECTEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHDETECTEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API SpeechDetectedEventArgs : public EventArgs
	{
		friend class SpeechRecognitionEngine;
	protected:
		SpeechDetectedEventArgs(const Elysium::Core::TimeSpan AudioPosition);
	public:
		SpeechDetectedEventArgs(const SpeechDetectedEventArgs& Source) = delete;

		SpeechDetectedEventArgs(SpeechDetectedEventArgs&& Right) noexcept = delete;

		virtual ~SpeechDetectedEventArgs();
	public:
		SpeechDetectedEventArgs& operator=(const SpeechDetectedEventArgs& Source) = delete;

		SpeechDetectedEventArgs& operator=(SpeechDetectedEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::TimeSpan& GetAudioPosition() const;
	private:
		Elysium::Core::TimeSpan _AudioPosition;
	};
}
#endif
