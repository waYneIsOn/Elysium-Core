/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_DICTATIONGRAMMAR
#define ELYSIUM_CORE_SPEECH_RECOGNITION_DICTATIONGRAMMAR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_GRAMMAR
#include "Grammar.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API DictationGrammar final : public Grammar
	{
		friend class SpeechRecognitionEngine;
	public:
		DictationGrammar();

		DictationGrammar(const Utf8String& Topic);

		DictationGrammar(const DictationGrammar& Source) = delete;

		DictationGrammar(DictationGrammar&& Right) noexcept = delete;

		virtual ~DictationGrammar();
	public:
		DictationGrammar& operator=(const DictationGrammar& Source) = delete;

		DictationGrammar& operator=(DictationGrammar&& Right) noexcept = delete;
	public:
		void SetDictationContext(const Utf8String& PrecedingText, const Utf8String& SubsequentText);
	protected:
#if defined ELYSIUM_CORE_OS_WINDOWS
		virtual void Load() override;

		virtual void Unload() override;
#endif
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _WindowsEncoding = Elysium::Core::Text::Encoding::UTF16LE();
#endif
	private:
		Elysium::Core::Utf8String _Topic;
	};
}
#endif
