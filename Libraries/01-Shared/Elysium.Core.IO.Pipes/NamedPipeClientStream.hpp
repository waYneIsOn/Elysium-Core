/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPES_NAMEDPIPECLIENTSTREAM
#define ELYSIUM_CORE_IO_PIPES_NAMEDPIPECLIENTSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_HANDLEINHERITABILITY
#include "../Elysium.Core.IO/HandleInheritability.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PIPES_PIPESTREAM
#include "PipeStream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_PRINCIPAL_TOKENIMPERSONATIONLEVEL
#include "../Elysium.Core.Security/Principal/TokenImpersonationLevel.hpp"
#endif

#ifndef _WINBASE_
#include <WinBase.h>
#endif

#ifndef _NAMEDPIPE_H_
#include <namedpipeapi.h>
#endif

namespace Elysium::Core::IO::Pipes
{
	class ELYSIUM_CORE_IO_PIPES_API NamedPipeClientStream final
		: public PipeStream
	{
	public:
		NamedPipeClientStream(Elysium::Core::Utf8String::ConstCharacterPointer PipeName,
			Elysium::Core::Utf8String::ConstCharacterPointer ServerName = u8".", 
			const PipeDirection Direction = PipeDirection::InOut, const PipeOptions Options = PipeOptions::None,
			Elysium::Core::Security::Principal::TokenImpersonationLevel ImpersonationLevel = 
				Elysium::Core::Security::Principal::TokenImpersonationLevel::None,
			Elysium::Core::IO::HandleInheritability Inheritability = HandleInheritability::None);
		
		NamedPipeClientStream(const NamedPipeClientStream& Source) = delete;

		NamedPipeClientStream(NamedPipeClientStream&& Right) = delete;

		virtual ~NamedPipeClientStream() noexcept;
	public:
		NamedPipeClientStream& operator=(const NamedPipeClientStream& Source) = delete;

		NamedPipeClientStream& operator=(NamedPipeClientStream&& Right) noexcept = delete;
	public:
		// @ToDo: is this always 0 in .net? why is this property even there in that case?
		//constexpr const Elysium::Core::Template::System::uint8_t GetNumberOfServerInstances() const noexcept;
	public:
		void Connect(const TimeSpan Timeout = TimeSpan::FromTicks(0));
	public:
		virtual void Close() override;

		virtual void Flush() override;

		virtual const Elysium::Core::size Seek(const Elysium::Core::int64_t Offset, const Elysium::Core::IO::SeekOrigin Origin) override;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;

		virtual Elysium::Core::byte ReadByte() override;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
	private:
		Elysium::Core::Utf8String BuildFQPipeName(Elysium::Core::Utf8String::ConstCharacterPointer PipeName, Elysium::Core::Utf8String::ConstCharacterPointer ServerName);
	private:
		Elysium::Core::Utf8String _FQPipeName;

		HANDLE _NativeNamedPipeHandle;
	};
}
#endif
