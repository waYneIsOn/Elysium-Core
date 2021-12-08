/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEINFO
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEAGE
#include "VoiceAge.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEGENDER
#include "VoiceGender.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API VoiceInfo final
	{
		friend class InstalledVoice;
	private:
		VoiceInfo();
	public:
		VoiceInfo(const VoiceInfo& Source) = delete;

		VoiceInfo(VoiceInfo&& Right) noexcept = delete;

		~VoiceInfo();
	public:
		VoiceInfo& operator=(const VoiceInfo& Source) = delete;

		VoiceInfo& operator=(VoiceInfo&& Right) noexcept = delete;
	public:
		const VoiceAge GetAge() const;

		const VoiceGender GetGender() const;

		const String GetId() const;

		const String GetName() const;
	private:
		VoiceAge _Age;
		VoiceGender _Gender;
	};
}
#endif
