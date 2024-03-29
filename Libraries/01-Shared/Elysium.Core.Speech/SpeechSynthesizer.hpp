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

#ifndef ELYSIUM_CORE_EVENT
#include "../Elysium.Core/Event.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#include "../Elysium.Core.Globalization/CultureInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_SPEECHAUDIOFORMATINFO
#include "SpeechAudioFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_BOOKMARKREACHEDEVENTARGS
#include "BookmarkReachedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_INSTALLEDVOICE
#include "InstalledVoice.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PHONEMEREACHEDEVENTARGS
#include "PhonemeReachedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKCOMPLETEDEVENTARGS
#include "SpeakCompletedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKPROGRESSEVENTARGS
#include "SpeakProgressEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEAKSTARTEDEVENTARGS
#include "SpeakStartedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEECHSYNTHESIZEREVENTS
#include "SpeechSynthesizerEvents.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_STATECHANGEDEVENTARGS
#include "StateChangedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SYNTHESIZERSTATE
#include "SynthesizerState.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VISEMEREACHEDEVENTARGS
#include "VisemeReachedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICECHANGEEVENTARGS
#include "VoiceChangeEventArgs.hpp"
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
	/// <summary>
	/// Provides access to the functionality of an installed speech synthesis engine.
	/// </summary>
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
		const Elysium::Core::uint32_t GetRate() const;

		const SynthesizerState GetState() const;

		const VoiceInfo GetVoice() const;

		const Elysium::Core::uint16_t GetVolume() const;

		void SetRate(const Elysium::Core::uint32_t Value);

		void SetVolume(const Elysium::Core::uint16_t Value);
	public:
		const Elysium::Core::Template::Container::Vector<InstalledVoice> GetInstalledVoices();

		const Elysium::Core::Template::Container::Vector<InstalledVoice> GetInstalledVoices(const Elysium::Core::Globalization::Utf8CultureInfo& Culture);

		void Pause();

		void Resume();

		void SelectVoice(const Elysium::Core::Utf8String& Name);

		void SelectVoice(const VoiceInfo& Info);

		void SetOutputToAudioStream(Elysium::Core::IO::Stream& AudioDestination, const AudioFormat::SpeechAudioFormatInfo& FormatInfo);

		void SetOutputToDefaultAudioDevice();

		void SetOutputToWaveFile(const Elysium::Core::Utf8String& Path, const AudioFormat::SpeechAudioFormatInfo& FormatInfo);

		void SetOutputToWaveStream(Elysium::Core::IO::Stream& AudioDestination);

		void Speak(const char8_t* TextToSpeak);

		void Speak(const Elysium::Core::Utf8String& TextToSpeak);

		void SpeakAsync(const char8_t* TextToSpeak);

		void SpeakAsync(const Elysium::Core::Utf8String& TextToSpeak);

		void SpeakSsml(const char8_t* TextToSpeak);

		void SpeakSsml(const Elysium::Core::Utf8String& TextToSpeak);

		void SpeakSsmlAsync(const char8_t* TextToSpeak);

		void SpeakSsmlAsync(const Elysium::Core::Utf8String& TextToSpeak);

		void WaitUntilDone(const Elysium::Core::TimeSpan Timeout);
	public:
		/// <summary>
		/// Raised when the SpeechSynthesizer encounters a bookmark in a prompt.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const BookmarkReachedEventArgs&> BookmarkReached;

		/// <summary>
		/// Raised when a phoneme is reached.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const PhonemeReachedEventArgs&> PhonemeReached;

		/// <summary>
		/// Raised when the SpeechSynthesizer completes the speaking of a prompt.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const SpeakCompletedEventArgs&> SpeakCompleted;

		/// <summary>
		/// Raised after the SpeechSynthesizer speaks each individual word of a prompt.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const SpeakProgressEventArgs&> SpeakProgress;

		/// <summary>
		/// Raised when the SpeechSynthesizer begins the speaking of a prompt.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const SpeakStartedEventArgs&> SpeakStarted;

		/// <summary>
		/// Raised when the state of the SpeechSynthesizer changes.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const StateChangedEventArgs&> StateChanged;

		/// <summary>
		/// Raised when a viseme is reached.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const VisemeReachedEventArgs&> VisemeReached;

		/// <summary>
		/// Raised when the voice of the SpeechSynthesizer changes.
		/// </summary>
		Event<void, const SpeechSynthesizer&, const VoiceChangeEventArgs&> VoiceChanged;
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _WindowsEncoding = Elysium::Core::Text::Encoding::UTF16LE();

		ISpVoice* _NativeSynthesizer;
		ISpStream* _NativeMemoryStream;
		Elysium::Core::IO::Stream* _TargetStream;

		ISpVoice* InitializeNativeSynthesizer();

		ISpStream* InitializeNativeStream();

		HRESULT SetNativeVoice(ISpObjectToken* VoiceToken) noexcept;

		HRESULT SpeakNatively(const wchar_t* TextToSpeak, const Elysium::Core::int32_t Flags) noexcept;

		void ProcessEventMessageQueue();
#endif
	};
}
#endif
