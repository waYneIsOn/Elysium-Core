/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_SPEECHAUDIOFORMATINFO
#define ELYSIUM_CORE_SPEECH_AUDIOFORMAT_SPEECHAUDIOFORMATINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_AUDIOBITSPERSAMPLE
#include "AudioBitsPerSample.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_AUDIOCHANNEL
#include "AudioChannel.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_AUDIOFORMAT_ENCODINGFORMAT
#include "EncodingFormat.hpp"
#endif

namespace Elysium::Core::Speech::AudioFormat
{
	class ELYSIUM_CORE_SPEECH_API SpeechAudioFormatInfo final
	{
	public:
		SpeechAudioFormatInfo(const Elysium::Core::uint32_t SamplesPerSecond, const AudioBitsPerSample BitsPerSample, const AudioChannel Channel);
		/*
		SpeechAudioFormatInfo(const EncodingFormat EncodingFormat, const Elysium::Core::int32_t SamplesPerSecond,
			const Elysium::Core::int32_t BitsPerChannel, const Elysium::Core::int32_t ChannelCount, const Elysium::Core::int32_t AverageBytesPerSecond,
			const Elysium::Core::int32_t BlockAlign, );
		*/
		SpeechAudioFormatInfo(const SpeechAudioFormatInfo& Source) = delete;

		SpeechAudioFormatInfo(SpeechAudioFormatInfo&& Right) noexcept = delete;

		~SpeechAudioFormatInfo();
	public:
		SpeechAudioFormatInfo& operator=(const SpeechAudioFormatInfo& Source) = delete;

		SpeechAudioFormatInfo& operator=(SpeechAudioFormatInfo&& Right) noexcept = delete;
	public:
		const Elysium::Core::uint32_t GetAverageBytesPerSecond() const;

		const Elysium::Core::uint8_t GetBitsPerSample() const;

		const Elysium::Core::uint32_t GetBlockAlign() const;

		const Elysium::Core::uint8_t GetChannelCount() const;

		const EncodingFormat GetEncodingFormat() const;

		const Elysium::Core::uint32_t GetSamplesPerSecond() const;
	private:
		EncodingFormat _EncodingFormat;
		Elysium::Core::uint32_t _SamplesPerSecond;
		AudioBitsPerSample _BitsPerSample;
		AudioChannel _Channel;
	};
}
#endif
