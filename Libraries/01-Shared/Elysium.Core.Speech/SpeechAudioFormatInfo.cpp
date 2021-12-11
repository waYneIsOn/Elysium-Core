#include "SpeechAudioFormatInfo.hpp"

Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::SpeechAudioFormatInfo(const Elysium::Core::uint32_t SamplesPerSecond, const AudioBitsPerSample BitsPerSample, const AudioChannel Channel)
	: _EncodingFormat(EncodingFormat::Pcm), _SamplesPerSecond(SamplesPerSecond), _BitsPerSample(BitsPerSample), _Channel(Channel)
{ }

Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::~SpeechAudioFormatInfo()
{ }

const Elysium::Core::uint32_t Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::GetAverageBytesPerSecond() const
{
	return _SamplesPerSecond * GetBlockAlign();
}

const Elysium::Core::uint8_t Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::GetBitsPerSample() const
{
	return static_cast<Elysium::Core::uint8_t>(_BitsPerSample);
}

const Elysium::Core::uint32_t Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::GetBlockAlign() const
{
	return static_cast<Elysium::Core::uint32_t>(_Channel) * (static_cast<Elysium::Core::uint32_t>(_BitsPerSample) / 8);
}

const Elysium::Core::uint8_t Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::GetChannelCount() const
{
	return static_cast<Elysium::Core::uint8_t>(_Channel);
}

const Elysium::Core::Speech::AudioFormat::EncodingFormat Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::GetEncodingFormat() const
{
	return _EncodingFormat;
}

const Elysium::Core::uint32_t Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo::GetSamplesPerSecond() const
{
	return _SamplesPerSecond;
}
