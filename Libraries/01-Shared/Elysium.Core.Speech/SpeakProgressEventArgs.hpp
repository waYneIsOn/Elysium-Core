/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKPROGRESSEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKPROGRESSEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS
#include "PromptEventArgs.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API SpeakProgressEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		SpeakProgressEventArgs(Elysium::Core::Utf8String&& Prompt, const Elysium::Core::uint64_t AudioPositionTicks, const Elysium::Core::uint64_t CharacterCount,
			const Elysium::Core::uint64_t CharacterPosition);
	public:
		SpeakProgressEventArgs(const SpeakProgressEventArgs& Source) = delete;

		SpeakProgressEventArgs(SpeakProgressEventArgs&& Right) noexcept = delete;

		virtual ~SpeakProgressEventArgs();
	public:
		SpeakProgressEventArgs& operator=(const SpeakProgressEventArgs& Source) = delete;

		SpeakProgressEventArgs& operator=(SpeakProgressEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::TimeSpan& GetAudioPosition() const;

		const Elysium::Core::uint64_t GetCharacterCount() const;

		const Elysium::Core::uint64_t GetCharacterPosition() const;
	private:
		TimeSpan _AudioPosition;
		Elysium::Core::uint64_t _CharacterCount;
		Elysium::Core::uint64_t _CharacterPosition;
		//String _Text;	// ToDo: StringView would make more sense here imo!
	};
}
#endif
