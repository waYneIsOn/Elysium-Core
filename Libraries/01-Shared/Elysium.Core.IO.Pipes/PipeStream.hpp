/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPES_PIPESTREAM
#define ELYSIUM_CORE_IO_PIPES_PIPESTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_PIPEACCESSRIGHTS
#include "PipeAccessRights.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_PIPEDIRECTION
#include "PipeDirection.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_PIPEOPTIONS
#include "PipeOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_PIPETRANSMISSIONMODE
#include "PipeTransmissionMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef _WINBASE_
#include <WinBase.h>
#endif

namespace Elysium::Core::IO::Pipes
{
	class ELYSIUM_CORE_IO_PIPES_API PipeStream
		: public Elysium::Core::IO::Stream
	{
	protected:
		PipeStream(const PipeDirection Direction, const PipeTransmissionMode TransmissionMode, 
			const Elysium::Core::Template::System::size OutBufferSize);
	public:
		PipeStream(const PipeStream& Source) = delete;

		PipeStream(PipeStream&& Right) = delete;

		virtual ~PipeStream() noexcept = default;
	public:
		PipeStream& operator=(const PipeStream& Source) = delete;

		PipeStream& operator=(PipeStream&& Right) noexcept = delete;
	public:
		virtual const bool GetCanRead() const override;

		virtual const bool GetCanSeek() const override;

		virtual const bool GetCanTimeout() const override;

		virtual const bool GetCanWrite() const override;

		virtual const Elysium::Core::size GetLength() const override;

		virtual const Elysium::Core::uint64_t GetPosition() const override;

		virtual const Elysium::Core::uint32_t GetReadTimeout() const override;

		virtual const Elysium::Core::uint32_t GetWriteTimeout() const override;
	public:
		const PipeTransmissionMode GetTransmissionMode() const noexcept;
	public:
		virtual void SetLength(const Elysium::Core::size Value) override;

		virtual void SetPosition(const Elysium::Core::uint64_t  Position) override;

		virtual void SetReadTimeout(const Elysium::Core::uint32_t Value) override;

		virtual void SetWriteTimeout(const Elysium::Core::uint32_t Value) override;
	private:
		const PipeDirection _Direction;
		const PipeTransmissionMode _TransmissionMode;
	};
}
#endif
