/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_RECOGNITIONRESULT
#include "RecognitionResult.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API RecognitionEventArgs : public EventArgs
	{
	protected:
		RecognitionEventArgs(RecognitionResult&& Result);
	public:
		RecognitionEventArgs(const RecognitionEventArgs& Source) = delete;

		RecognitionEventArgs(RecognitionEventArgs&& Right) noexcept = delete;

		virtual ~RecognitionEventArgs();
	public:
		RecognitionEventArgs& operator=(const RecognitionEventArgs& Source) = delete;

		RecognitionEventArgs& operator=(RecognitionEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::Speech::Recognition::RecognitionResult& GetResult() const;
	private:
		RecognitionResult _Result;
	};
}
#endif
