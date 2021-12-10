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

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_INSTALLEDVOICE
#include "InstalledVoice.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZERSTATE
#include "SynthesizerState.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICEINFO
#include "VoiceInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
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
		const Elysium::Core::int32_t GetRate() const;

		//const SynthesizerState GetState() const;

		const VoiceInfo GetVoice() const;

		const Elysium::Core::int32_t GetVolume() const;
	public:
		const Elysium::Core::Template::Container::Vector<InstalledVoice> GetInstalledVoices();

		const Elysium::Core::Template::Container::Vector<InstalledVoice> GetInstalledVoices(const Elysium::Core::Globalization::CultureInfo& Culture);

		void SelectVoice(const String& Name);

		void SelectVoice(const VoiceInfo& Info);

		void Speak(const char8_t* TextToSpeak, const Elysium::Core::size Length);

		void Speak(const char8_t* TextToSpeak);

		void Speak(const String& TextToSpeak);

		void SpeakSsml(const char8_t* TextToSpeak, const Elysium::Core::size Length);

		void SpeakSsml(const char8_t* TextToSpeak);

		void SpeakSsml(const String& TextToSpeak);
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _WindowsEncoding = Elysium::Core::Text::Encoding::UTF16LE();

		ISpVoice* _NativeSynthesizer;

		ISpVoice* Initialize();

		HRESULT SelectNativeVoice(ISpObjectToken* VoiceToken);
#endif
	};
}
#endif
