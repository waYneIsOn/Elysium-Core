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

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONEVENTARGS
#include "SpeechRecognitionEngineEvents.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_SPEECHRECOGNIZEDEVENTARGS
#include "SpeechRecognizedEventArgs.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class SpeechRecognitionEngine;

	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Event<void, const SpeechRecognitionEngine&, const SpeechRecognizedEventArgs&>;
}
#endif
