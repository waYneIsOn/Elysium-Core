/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNITIONENGINE
#define ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNITIONENGINE

#ifdef _MSC_VER
#pragma once
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

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_SPEECHAUDIOFORMATINFO
#include "SpeechAudioFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_GRAMMAR
#include "Grammar.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNITIONENGINEEVENTS
#include "SpeechRecognitionEngineEvents.hpp"
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

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API SpeechRecognitionEngine final
	{
	public:
		SpeechRecognitionEngine();

		SpeechRecognitionEngine(const Elysium::Core::Globalization::CultureInfo& Culture);

		SpeechRecognitionEngine(const SpeechRecognitionEngine& Source) = delete;

		SpeechRecognitionEngine(SpeechRecognitionEngine&& Right) noexcept = delete;

		~SpeechRecognitionEngine();
	public:
		SpeechRecognitionEngine& operator=(const SpeechRecognitionEngine& Source) = delete;

		SpeechRecognitionEngine& operator=(SpeechRecognitionEngine&& Right) noexcept = delete;
	public:
		//Event<void, const SpeechRecognitionEngine&, const AudioLevelUpdatedEventArgs&> AudioLevelUpdated;
		
		//Event<void, const SpeechRecognitionEngine&, const AudioSignalProblemOccurredEventArgs&> AudioSignalProblemOccurred;
		
		Event<void, const SpeechRecognitionEngine&, const AudioStateChangedEventArgs&> AudioStateChanged;
		
		//Event<void, const SpeechRecognitionEngine&, const EmulateRecognizeCompletedEventArgs&> EmulateRecognizeCompleted;
		
		//Event<void, const SpeechRecognitionEngine&, const LoadGrammarCompletedEventArgs&> LoadGrammarCompleted;
		
		//Event<void, const SpeechRecognitionEngine&, const RecognizeCompletedEventArgs&> RecognizeCompleted;
		
		//Event<void, const SpeechRecognitionEngine&, const RecognizerUpdateReachedEventArgs&> RecognizerUpdateReachedEventArgs;
		
		//Event<void, const SpeechRecognitionEngine&, const SpeechDetectedEventArgs&> SpeechDetected;
		
		//Event<void, const SpeechRecognitionEngine&, const SpeechHypothesizedEventArgs&> SpeechHypothesized;
		
		//Event<void, const SpeechRecognitionEngine&, const SpeechRecognitionRejectedEventArgs&> SpeechRecognitionRejected;

		Event<void, const SpeechRecognitionEngine&, const SpeechRecognizedEventArgs&> SpeechRecognized;
	public:
		void LoadGrammar(Grammar& Grammar);

		void SetInputToDefaultAudioDevice();

		void SetInputToAudioStream(Elysium::Core::IO::Stream& AudioStream, const Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo& FormatInfo);

		void SetInputToWaveFile(const Elysium::Core::Utf8String& Path);

		void Recognize();
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _WindowsEncoding = Elysium::Core::Text::Encoding::UTF16LE();

		ISpRecognizer* _NativeRecognizer;
		ISpRecoContext* _NativeRecognizerContext;
		ISpStream* _NativeMemoryStream;
	private:
		ISpRecognizer* InitializeNativeRecognizer();

		ISpRecoContext* InitializeNativeRecognizerContext();

		ISpStream* InitializeNativeStream();

		void ProcessEventMessageQueue();
#endif
	};
}
#endif
