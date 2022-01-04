/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNIZEDPHRASE
#define ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNIZEDPHRASE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API RecognizedPhrase
	{
	protected:
		RecognizedPhrase(Elysium::Core::Utf8String && Text);
	public:
		RecognizedPhrase(const RecognizedPhrase& Source) = delete;

		RecognizedPhrase(RecognizedPhrase&& Right) noexcept;

		virtual ~RecognizedPhrase();
	public:
		RecognizedPhrase& operator=(const RecognizedPhrase& Source) = delete;

		RecognizedPhrase& operator=(RecognizedPhrase&& Right) noexcept;
	public:
		const Elysium::Core::Utf8String& GetText() const;
	private:
		Elysium::Core::Utf8String _Text;
	};
}
#endif
