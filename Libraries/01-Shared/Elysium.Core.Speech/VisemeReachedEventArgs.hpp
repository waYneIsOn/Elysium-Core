/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VISEMEREACHEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_VISEMEREACHEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
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
	class ELYSIUM_CORE_SPEECH_API VisemeReachedEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		VisemeReachedEventArgs(String&& Prompt, const Elysium::Core::uint64_t AudioPositionTicks, const Elysium::Core::uint64_t DurationMilliseconds,
			const SynthesizerEmphasis Emphasis, const Elysium::Core::uint16_t Viseme, const Elysium::Core::uint16_t NextViseme);
	public:
		VisemeReachedEventArgs(const VisemeReachedEventArgs& Source) = delete;

		VisemeReachedEventArgs(VisemeReachedEventArgs&& Right) noexcept = delete;

		virtual ~VisemeReachedEventArgs();
	public:
		VisemeReachedEventArgs& operator=(const VisemeReachedEventArgs& Source) = delete;

		VisemeReachedEventArgs& operator=(VisemeReachedEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::TimeSpan& GetAudioPosition() const;

		const Elysium::Core::TimeSpan& GetDuration() const;

		const SynthesizerEmphasis GetEmphasis() const;

		const Elysium::Core::uint16_t GetViseme() const;

		const Elysium::Core::uint16_t GetNextViseme() const;
	private:
		TimeSpan _AudioPosition;
		TimeSpan _Duration;
		SynthesizerEmphasis _Emphasis;
		Elysium::Core::uint16_t _Viseme;
		Elysium::Core::uint16_t _NextViseme;
	};
}
#endif
