/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_INSTALLEDVOICE
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_INSTALLEDVOICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEINFO
#include "VoiceInfo.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API InstalledVoice final
	{
		friend class SpeechSynthesizer;
	private:
		InstalledVoice(const bool Enabled, VoiceInfo&& VoiceInfo);
	public:
		InstalledVoice(const InstalledVoice& Source) = delete;

		InstalledVoice(InstalledVoice&& Right) noexcept;

		~InstalledVoice();
	public:
		InstalledVoice& operator=(const InstalledVoice& Source) = delete;

		InstalledVoice& operator=(InstalledVoice&& Right) noexcept;
	public:
		const bool GetEnabled() const;

		const VoiceInfo& GetVoiceInfo() const;

		void SetEnabled(const bool Value);
	private:
		bool _Enabled;
		VoiceInfo _VoiceInfo;
	};
}
#endif
