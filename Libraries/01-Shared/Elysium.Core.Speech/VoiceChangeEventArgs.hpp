/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICECHANGEEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICECHANGEEVENTARGS

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
	class ELYSIUM_CORE_SPEECH_API VoiceChangeEventArgs : public PromptEventArgs
	{
	protected:
		VoiceChangeEventArgs();
	public:
		VoiceChangeEventArgs(const VoiceChangeEventArgs& Source) = delete;

		VoiceChangeEventArgs(VoiceChangeEventArgs&& Right) noexcept = delete;

		virtual ~VoiceChangeEventArgs();
	public:
		VoiceChangeEventArgs& operator=(const VoiceChangeEventArgs& Source) = delete;

		VoiceChangeEventArgs& operator=(VoiceChangeEventArgs&& Right) noexcept = delete;
	};
}
#endif
