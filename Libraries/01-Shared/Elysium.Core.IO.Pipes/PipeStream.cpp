#include "PipeStream.hpp"

constexpr Elysium::Core::IO::Pipes::PipeStream::PipeStream(const PipeDirection Direction, const PipeTransmissionMode TransmissionMode, const Elysium::Core::Template::System::size BufferSize)
	: Elysium::Core::IO::Stream(),
	_Direction(Direction), _TransmissionMode(TransmissionMode)
{ }

constexpr Elysium::Core::IO::Pipes::PipeStream::~PipeStream()
{ }

constexpr const Elysium::Core::IO::Pipes::PipeTransmissionMode Elysium::Core::IO::Pipes::PipeStream::GetTransmissionMode() const noexcept
{
	return _TransmissionMode;
}
