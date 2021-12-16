/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PHONEMEREACHEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_PHONEMEREACHEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS
#include "PromptEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZEREMPHASIS
#include "SynthesizerEmphasis.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API PhonemeReachedEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		PhonemeReachedEventArgs(String&& Prompt, const Elysium::Core::uint64_t AudioPositionTicks, const Elysium::Core::uint64_t DurationMilliseconds,
			const SynthesizerEmphasis Emphasis);
	public:
		PhonemeReachedEventArgs(const PhonemeReachedEventArgs& Source) = delete;

		PhonemeReachedEventArgs(PhonemeReachedEventArgs&& Right) noexcept = delete;

		virtual ~PhonemeReachedEventArgs();
	public:
		PhonemeReachedEventArgs& operator=(const PhonemeReachedEventArgs& Source) = delete;

		PhonemeReachedEventArgs& operator=(PhonemeReachedEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::TimeSpan& GetAudioPosition() const;

		const Elysium::Core::TimeSpan& GetDuration() const;

		const SynthesizerEmphasis GetEmphasis() const;
	private:
		TimeSpan _AudioPosition;
		TimeSpan _Duration;
		SynthesizerEmphasis _Emphasis;
	};
}
#endif
