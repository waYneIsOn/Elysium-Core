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

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS
#include "PromptEventArgs.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API VisemeReachedEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		VisemeReachedEventArgs(String&& Prompt);
	public:
		VisemeReachedEventArgs(const VisemeReachedEventArgs& Source) = delete;

		VisemeReachedEventArgs(VisemeReachedEventArgs&& Right) noexcept = delete;

		virtual ~VisemeReachedEventArgs();
	public:
		VisemeReachedEventArgs& operator=(const VisemeReachedEventArgs& Source) = delete;

		VisemeReachedEventArgs& operator=(VisemeReachedEventArgs&& Right) noexcept = delete;
	};
}
#endif
