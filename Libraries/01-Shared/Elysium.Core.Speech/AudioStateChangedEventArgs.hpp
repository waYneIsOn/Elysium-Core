/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSTATECHANGEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_RECOGNITION_AUDIOSTATECHANGEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_AUDIOSTATE
#include "AudioState.hpp"
#endif

namespace Elysium::Core::Speech::Recognition
{
	class ELYSIUM_CORE_SPEECH_API AudioStateChangedEventArgs : public EventArgs
	{
	protected:
		AudioStateChangedEventArgs(const AudioFormat::AudioState AudioState);
	public:
		AudioStateChangedEventArgs(const AudioStateChangedEventArgs& Source) = delete;

		AudioStateChangedEventArgs(AudioStateChangedEventArgs&& Right) noexcept = delete;

		virtual ~AudioStateChangedEventArgs();
	public:
		AudioStateChangedEventArgs& operator=(const AudioStateChangedEventArgs& Source) = delete;

		AudioStateChangedEventArgs& operator=(AudioStateChangedEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::Speech::AudioFormat::AudioState& GetAudioState() const;
	private:
		AudioFormat::AudioState _AudioState;
	};
}
#endif
