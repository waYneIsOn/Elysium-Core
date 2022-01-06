/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_LOADGRAMMARCOMPLETEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_LOADGRAMMARCOMPLETEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_GRAMMAR
#include "Grammar.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API LoadGrammarCompletedEventArgs : public EventArgs
	{
		friend class SpeechRecognitionEngine;
	protected:
		LoadGrammarCompletedEventArgs(const Grammar& Grammar);
	public:
		LoadGrammarCompletedEventArgs(const LoadGrammarCompletedEventArgs& Source) = delete;

		LoadGrammarCompletedEventArgs(LoadGrammarCompletedEventArgs&& Right) noexcept = delete;

		virtual ~LoadGrammarCompletedEventArgs();
	public:
		LoadGrammarCompletedEventArgs& operator=(const LoadGrammarCompletedEventArgs& Source) = delete;

		LoadGrammarCompletedEventArgs& operator=(LoadGrammarCompletedEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::Speech::Recognition::Grammar& GetGrammar() const;
	private:
		const Grammar& _Grammar;
	};
}
#endif
