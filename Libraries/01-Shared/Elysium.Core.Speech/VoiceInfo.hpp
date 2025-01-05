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

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#include "../Elysium.Core.Globalization/CultureInfo.hpp"
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

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEAGE
#include "VoiceAge.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEGENDER
#include "VoiceGender.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#include "../Elysium.Core.Template/UnorderedMap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef __sapi_h__
#pragma warning(disable: 4996)	// sapi is using GetVersionEx under certain conditions
#include <sapi.h>
#pragma warning(default: 4996)
#endif
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API VoiceInfo final
	{
		friend class InstalledVoice;
		friend class SpeechSynthesizer;
	private:
		VoiceInfo();

#if defined ELYSIUM_CORE_OS_WINDOWS
		VoiceInfo(ISpObjectToken* VoiceToken, const bool OwnsVoiceToken);
#endif
	public:
		VoiceInfo(const VoiceInfo& Source) = delete;

		VoiceInfo(VoiceInfo&& Right) noexcept;

		~VoiceInfo();
	public:
		VoiceInfo& operator=(const VoiceInfo& Source) = delete;

		VoiceInfo& operator=(VoiceInfo&& Right) noexcept;
	public:
		const VoiceAge GetAge() const;

		const Elysium::Core::Globalization::CultureInfo GetCulture() const;

		const VoiceGender GetGender() const;

		const Elysium::Core::Utf8String GetId() const;

		const Elysium::Core::Utf8String GetName() const;
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _WindowsEncoding = Elysium::Core::Text::Encoding::UTF16LE();

		ISpObjectToken* _VoiceToken;
		bool _OwnsVoiceToken;
#endif

		//Template::Container::HashTable<String, String> _AdditionalInfo;
	};
}
#endif
