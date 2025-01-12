/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPIES_NAMEDPIPESERVERSTREAM
#define ELYSIUM_CORE_IO_PIPIES_NAMEDPIPESERVERSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPIES_PIPEOPTIONS
#include "PipeOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPIES_PIPESTREAM
#include "PipeStream.hpp"
#endif

namespace Elysium::Core::IO::Pipes
{
	class NamedPipeServerStream
		: public PipeStream
	{
	public:
		constexpr NamedPipeServerStream(const Elysium::Core::Utf8String PipeName, const PipeDirection Direction,
			const Elysium::Core::Template::System::int32_t MaxNumberOfServerInstances,	const PipeTransmissionMode TransmissionMode,
			const PipeOptions Options, const Elysium::Core::Template::System::size InBufferSize, 
			const Elysium::Core::Template::System::size OutBufferSize);

		constexpr NamedPipeServerStream(const NamedPipeServerStream& Source) = delete;

		constexpr NamedPipeServerStream(NamedPipeServerStream&& Right) = delete;

		constexpr virtual ~NamedPipeServerStream();
	public:
		NamedPipeServerStream& operator=(const NamedPipeServerStream& Source) = delete;

		NamedPipeServerStream& operator=(NamedPipeServerStream&& Right) noexcept = delete;
	public:
		static constexpr const Elysium::Core::Template::System::int32_t MaxAllowedServerInstances = -1;
	private:
		const PipeOptions _Options;
	};
}
#endif
