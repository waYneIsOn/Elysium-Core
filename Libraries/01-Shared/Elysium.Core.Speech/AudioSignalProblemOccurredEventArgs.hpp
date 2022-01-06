/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSIGNALPROBLEMOCCURREDEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSIGNALPROBLEMOCCURREDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSIGNALPROBLEM
#include "AudioSignalProblem.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API AudioSignalProblemOccurredEventArgs : public EventArgs
	{
		friend class SpeechRecognitionEngine;
	protected:
		AudioSignalProblemOccurredEventArgs(const AudioSignalProblem Problem, const Elysium::Core::uint32_t AudioLevel);
	public:
		AudioSignalProblemOccurredEventArgs(const AudioSignalProblemOccurredEventArgs& Source) = delete;

		AudioSignalProblemOccurredEventArgs(AudioSignalProblemOccurredEventArgs&& Right) noexcept = delete;

		virtual ~AudioSignalProblemOccurredEventArgs();
	public:
		AudioSignalProblemOccurredEventArgs& operator=(const AudioSignalProblemOccurredEventArgs& Source) = delete;

		AudioSignalProblemOccurredEventArgs& operator=(AudioSignalProblemOccurredEventArgs&& Right) noexcept = delete;
	public:
		const AudioSignalProblem GetAudioSignalProblem() const;

		const Elysium::Core::uint32_t GetAudioLevel() const;
	private:
		AudioSignalProblem _AudioSignalProblem;
		Elysium::Core::uint32_t _AudioLevel;
	};
}
#endif
