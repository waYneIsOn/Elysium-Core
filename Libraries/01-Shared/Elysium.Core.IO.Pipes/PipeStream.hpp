/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPIES_PIPESTREAM
#define ELYSIUM_CORE_IO_PIPIES_PIPESTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPIES_PIPEDIRECTION
#include "PipeDirection.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPIES_PIPETRANSMISSIONMODE
#include "PipeTransmissionMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Pipes
{
	class ELYSIUM_CORE_IO_PIPES_API PipeStream
		: public Elysium::Core::IO::Stream
	{
	protected:
		constexpr PipeStream(const PipeDirection Direction, const PipeTransmissionMode TransmissionMode, 
			const Elysium::Core::Template::System::size OutBufferSize);
	public:
		constexpr PipeStream(const PipeStream& Source) = delete;

		constexpr PipeStream(PipeStream&& Right) = delete;

		constexpr virtual ~PipeStream();
	public:
		PipeStream& operator=(const PipeStream& Source) = delete;

		PipeStream& operator=(PipeStream&& Right) noexcept = delete;
	public:
		constexpr const PipeTransmissionMode GetTransmissionMode() const noexcept;
	private:
		const PipeDirection _Direction;
		const PipeTransmissionMode _TransmissionMode;
	};
}
#endif
