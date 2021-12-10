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
	private:
		InstalledVoice(const bool Enabled, const VoiceInfo& VoiceInfo);
	public:
		InstalledVoice(const InstalledVoice& Source) = delete;

		InstalledVoice(InstalledVoice&& Right) noexcept = delete;

		~InstalledVoice();
	public:
		InstalledVoice& operator=(const InstalledVoice& Source) = delete;

		InstalledVoice& operator=(InstalledVoice&& Right) noexcept = delete;
	public:
		const bool GetEnabled() const;

		//const VoiceInfo& GetVoiceInfo() const;

		void SetEnabled(const bool Value);
	private:
		bool _Enabled;
		const VoiceInfo& _VoiceInfo;
	};
}
#endif
