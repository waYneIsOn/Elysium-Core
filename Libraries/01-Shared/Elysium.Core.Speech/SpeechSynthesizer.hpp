/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEECHSYNTHESIZER
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEECHSYNTHESIZER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_INSTALLEDVOICE
#include "InstalledVoice.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEINFO
#include "VoiceInfo.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef __sapi_h__
#include <sapi.h>
#endif
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API SpeechSynthesizer final
	{
	public:
		SpeechSynthesizer();

		SpeechSynthesizer(const SpeechSynthesizer& Source) = delete;

		SpeechSynthesizer(SpeechSynthesizer&& Right) noexcept = delete;

		~SpeechSynthesizer();
	public:
		SpeechSynthesizer& operator=(const SpeechSynthesizer& Source) = delete;

		SpeechSynthesizer& operator=(SpeechSynthesizer&& Right) noexcept = delete;
	public:
		const VoiceInfo GetVoice() const;
	public:
		void SetOutputToDefaultAudioDevice();

		void Speak(const String& TextToSpeak);
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		ISpVoice* _NativeVoice;

		ISpVoice* Initialize();
#endif
	};
}
#endif
