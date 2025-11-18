#include "PipeStream.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "../Elysium.Core.Template/Literals.hpp"
#endif

Elysium::Core::IO::Pipes::PipeStream::PipeStream(const PipeDirection Direction, const PipeTransmissionMode TransmissionMode, const Elysium::Core::Template::System::size OutBufferSize)
	: Elysium::Core::IO::Stream(),
	_Direction(Direction), _TransmissionMode(TransmissionMode)
{ }

const bool Elysium::Core::IO::Pipes::PipeStream::GetCanRead() const
{
	Elysium::Core::uint8_t MostRightBit = static_cast<Elysium::Core::uint8_t>(_Direction) & 0x01;
	return MostRightBit == 1_ui8 ? true : false;
}

const bool Elysium::Core::IO::Pipes::PipeStream::GetCanSeek() const
{
	return false;
}

const bool Elysium::Core::IO::Pipes::PipeStream::GetCanTimeout() const
{
	return false;
}

const bool Elysium::Core::IO::Pipes::PipeStream::GetCanWrite() const
{
	Elysium::Core::uint8_t SecondMostRightBit = static_cast<Elysium::Core::uint8_t>(_Direction) & 0x02;
	return SecondMostRightBit == 2_ui8 ? true : false;
}

const Elysium::Core::size Elysium::Core::IO::Pipes::PipeStream::GetLength() const
{
	return 0;
}

const Elysium::Core::uint64_t Elysium::Core::IO::Pipes::PipeStream::GetPosition() const
{
	return 0;
}

const Elysium::Core::uint32_t Elysium::Core::IO::Pipes::PipeStream::GetReadTimeout() const
{
	return 0;
}

const Elysium::Core::uint32_t Elysium::Core::IO::Pipes::PipeStream::GetWriteTimeout() const
{
	return 0;
}

const Elysium::Core::IO::Pipes::PipeTransmissionMode Elysium::Core::IO::Pipes::PipeStream::GetTransmissionMode() const noexcept
{
	return _TransmissionMode;
}

void Elysium::Core::IO::Pipes::PipeStream::SetLength(const Elysium::Core::size Value)
{ }

void Elysium::Core::IO::Pipes::PipeStream::SetPosition(const Elysium::Core::uint64_t Position)
{ }

void Elysium::Core::IO::Pipes::PipeStream::SetReadTimeout(const Elysium::Core::uint32_t Value)
{ }

void Elysium::Core::IO::Pipes::PipeStream::SetWriteTimeout(const Elysium::Core::uint32_t Value)
{ }