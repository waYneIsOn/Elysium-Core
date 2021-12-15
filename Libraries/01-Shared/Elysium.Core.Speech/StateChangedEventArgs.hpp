/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_STATECHANGEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_STATECHANGEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS
#include "PromptEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZERSTATE
#include "SynthesizerState.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API StateChangedEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		StateChangedEventArgs(String&& Prompt, const SynthesizerState PreviousState, const SynthesizerState State);
	public:
		StateChangedEventArgs(const StateChangedEventArgs& Source) = delete;

		StateChangedEventArgs(StateChangedEventArgs&& Right) noexcept = delete;

		virtual ~StateChangedEventArgs();
	public:
		StateChangedEventArgs& operator=(const StateChangedEventArgs& Source) = delete;

		StateChangedEventArgs& operator=(StateChangedEventArgs&& Right) noexcept = delete;
	public:
		const SynthesizerState GetPreviousState() const;

		const SynthesizerState GetState() const;
	private:
		SynthesizerState _PreviousState;
		SynthesizerState _State;
	};
}
#endif


