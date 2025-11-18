/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPES_NAMEDPIPESERVERSTREAM
#define ELYSIUM_CORE_IO_PIPES_NAMEDPIPESERVERSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_PIPESTREAM
#include "PipeStream.hpp"
#endif

#ifndef _WINBASE_
#include <WinBase.h>
#endif

namespace Elysium::Core::IO::Pipes
{
	class ELYSIUM_CORE_IO_PIPES_API NamedPipeServerStream final
		: public PipeStream
	{
	public:
		NamedPipeServerStream(Elysium::Core::Utf8String::ConstCharacterPointer PipeName,
			const PipeDirection Direction = PipeDirection::InOut,
			const Elysium::Core::Template::System::uint8_t MaxNumberOfServerInstances = 1,
			const PipeTransmissionMode TransmissionMode = PipeTransmissionMode::Byte, const PipeOptions Options = PipeOptions::None,
			const Elysium::Core::Template::System::size InBufferSize = 0, const Elysium::Core::Template::System::size OutBufferSize = 0);

		NamedPipeServerStream(const NamedPipeServerStream& Source) = delete;

		NamedPipeServerStream(NamedPipeServerStream&& Right) = delete;

		virtual ~NamedPipeServerStream() noexcept;
	public:
		NamedPipeServerStream& operator=(const NamedPipeServerStream& Source) = delete;

		NamedPipeServerStream& operator=(NamedPipeServerStream&& Right) noexcept = delete;
	public:
		static constexpr const Elysium::Core::Template::System::uint8_t MaxAllowedServerInstances = -1;
	public:
		void WaitForConnection();

		void Disconnect();
	public:
		virtual void Close() override;

		virtual void Flush() override;

		virtual const Elysium::Core::size Seek(const Elysium::Core::int64_t Offset, const Elysium::Core::IO::SeekOrigin Origin) override;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;

		virtual Elysium::Core::byte ReadByte() override;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
	private:
		Elysium::Core::Utf8String BuildFQPipeName(Elysium::Core::Utf8String::ConstCharacterPointer PipeName);

		HANDLE CreateNativeNamedPipeHandle(const Elysium::Core::Utf8String& PipeName, const PipeDirection Direction,
			const Elysium::Core::Template::System::uint8_t MaxNumberOfServerInstances, const PipeTransmissionMode TransmissionMode,
			const PipeOptions Options, const Elysium::Core::Template::System::size InBufferSize,
			const Elysium::Core::Template::System::size OutBufferSize, const PipeAccessRights AdditionalAccessRights);
	private:
		HANDLE _NativeNamedPipeHandle;

		const PipeOptions _Options;
	};
}
#endif
