/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEECHSYNTHESIZEREVENTS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_SPEECHSYNTHESIZEREVENTS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_BOOKMARKREACHEDEVENTARGS
#include "BookmarkReachedEventArgs.hpp"
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

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_STATECHANGEDEVENTARGS
#include "StateChangedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VISEMEREACHEDEVENTARGS
#include "VisemeReachedEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_VOICECHANGEEVENTARGS
#include "VoiceChangeEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_EVENT
#include "../Elysium.Core.Template/Dispatch/Event.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class SpeechSynthesizer;

	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const BookmarkReachedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const PhonemeReachedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const SpeakCompletedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const SpeakProgressEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const SpeakStartedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const StateChangedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const VisemeReachedEventArgs&>;
	template class ELYSIUM_CORE_SPEECH_API Elysium::Core::Template::Dispatch::Event<false, true, false, void, const SpeechSynthesizer&, const VoiceChangeEventArgs&>;
}
#endif
