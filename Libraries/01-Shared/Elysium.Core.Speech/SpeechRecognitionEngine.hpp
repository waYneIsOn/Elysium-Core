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

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_GRAMMAR
#include "Grammar.hpp"
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
		/*
		Event<void, const SpeechSynthesizer&, const AudioLevelUpdatedEventArgs&> AudioLevelUpdated;
		*/
	public:
		void LoadGrammar(const Grammar& Grammar);

		void SetInputToDefaultAudioDevice();

		void SetInputToWaveFile(const Elysium::Core::String& Path);

		void Recognize();
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _WindowsEncoding = Elysium::Core::Text::Encoding::UTF16LE();

		ISpRecognizer* _NativeRecognizer;
		ISpRecoContext* _NativeRecognizerContext;
		ISpStream* _NativeMemoryStream;

		ISpRecognizer* InitializeNativeRecognizer();

		ISpRecoContext* InitializeNativeRecognizerContext();

		ISpStream* InitializeNativeStream();

		void ProcessEventMessageQueue();
#endif
	};
}
#endif
