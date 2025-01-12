#include "NamedPipeServerStream.hpp"

constexpr Elysium::Core::IO::Pipes::NamedPipeServerStream::NamedPipeServerStream(const Elysium::Core::Utf8String PipeName, const PipeDirection Direction, const Elysium::Core::Template::System::int32_t MaxNumberOfServerInstances, const PipeTransmissionMode TransmissionMode, const PipeOptions Options, const Elysium::Core::Template::System::size InBufferSize, const Elysium::Core::Template::System::size OutBufferSize)
	: Elysium::Core::IO::Pipes::PipeStream(Direction, TransmissionMode, OutBufferSize),
	_Options(Options)
{ }

constexpr Elysium::Core::IO::Pipes::NamedPipeServerStream::~NamedPipeServerStream()
{ }
