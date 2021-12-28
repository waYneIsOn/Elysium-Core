/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_GRAMMAR
#define ELYSIUM_CORE_SPEECH_RECOGNITION_GRAMMAR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
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
	class ELYSIUM_CORE_SPEECH_API Grammar
	{
		friend class SpeechRecognitionEngine;
	protected:
		Grammar();
	public:
		Grammar(const String& Path);
	public:
		Grammar(const Grammar& Source) = delete;

		Grammar(Grammar&& Right) noexcept = delete;

		virtual ~Grammar();
	public:
		Grammar& operator=(const Grammar& Source) = delete;

		Grammar& operator=(Grammar&& Right) noexcept = delete;
	public:
		const Elysium::Core::String& GetName() const;

		//const Elysium::Core::String& GetRuleName() const;

		void SetName(const String& Value);
	private:
		String _Name;
	};
}
#endif
