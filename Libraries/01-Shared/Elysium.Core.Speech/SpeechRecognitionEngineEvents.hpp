/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNITIONENGINEEVENTS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNITIONENGINEEVENTS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENT
#include "../Elysium.Core/Event.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOLEVELUPDATEDEVENTARGS
#include "AudioLevelUpdatedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSIGNALPROBLEMOCCURREDEVENTARGS
#include "AudioSignalProblemOccurredEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSTATECHANGEDEVENTARGS
#include "AudioStateChangedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_LOADGRAMMARCOMPLETEDEVENTARGS
#include "LoadGrammarCompletedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHDETECTEDEVENTARGS
#include "SpeechDetectedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHHYPOTHESIZEDEVENTARGS
#include "SpeechHypothesizedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONEVENTARGS
#include "RecognitionEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNIZEDEVENTARGS
#include "SpeechRecognizedEventArgs.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class SpeechRecognitionEngine;

	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const AudioLevelUpdatedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const AudioSignalProblemOccurredEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const AudioStateChangedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const LoadGrammarCompletedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const SpeechDetectedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const SpeechHypothesizedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const SpeechRecognizedEventArgs&>;
}
#endif
