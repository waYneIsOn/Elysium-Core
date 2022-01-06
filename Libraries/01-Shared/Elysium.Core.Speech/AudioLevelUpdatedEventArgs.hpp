/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOLEVELUPDATEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOLEVELUPDATEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API AudioLevelUpdatedEventArgs : public EventArgs
	{
		friend class SpeechRecognitionEngine;
	protected:
		AudioLevelUpdatedEventArgs(const Elysium::Core::uint32_t AudioLevel);
	public:
		AudioLevelUpdatedEventArgs(const AudioLevelUpdatedEventArgs& Source) = delete;

		AudioLevelUpdatedEventArgs(AudioLevelUpdatedEventArgs&& Right) noexcept = delete;

		virtual ~AudioLevelUpdatedEventArgs();
	public:
		AudioLevelUpdatedEventArgs& operator=(const AudioLevelUpdatedEventArgs& Source) = delete;

		AudioLevelUpdatedEventArgs& operator=(AudioLevelUpdatedEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::uint32_t GetAudioLevel() const;
	private:
		Elysium::Core::uint32_t _AudioLevel;
	};
}
#endif
