/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_ZLIBSINK
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_ZLIBSINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_ZLIB_ZLIBHEADER
#include "../Compression/Format/ZLib/ZLibHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32
#include "../../Security/Cryptography/Checksum/Adler32.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
	// @ToDo: concept for "finishable sinks"!
	// @ToDo: GZip atm only allows deflate-compression so I could even specifically limit to DeflateSink here!
	template <class InnerSink>
	class ZLibSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		inline constexpr ZLibSink(InnerSink& InnerSink) noexcept
			: _InnerSink(InnerSink), _Adler32(0x01), _HasWrittenHeader{}, _HasWrittenFooter{}
		{ }

		constexpr ZLibSink(const ZLibSink& Source) = delete;

		constexpr ZLibSink(ZLibSink&& Right) noexcept = delete;

		inline ~ZLibSink()
		{
			Finish();
		}
	public:
		constexpr ZLibSink& operator=(const ZLibSink& Source) = delete;

		constexpr ZLibSink& operator=(ZLibSink&& Right) noexcept = delete;
	public:
		inline DeviceType& GetDevice()
		{
			return _InnerSink.GetDevice();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSink.GetDevice();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			if constexpr (requires { _InnerSink.SetPosition(Position); })
			{
				_InnerSink.SetPosition();
			}
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				return;
			}

			WriteHeader();

			_Adler32 = Elysium::Core::Template::Security::Cryptography::Checksum::Adler32::CalculateBytewise(_Adler32, Buffer, Count);
			_InnerSink.Write(Buffer, Count);
		}

		inline void Finish()
		{
			// ZLibSink requires _InnerSink to finish before it can write it's footer.
			// So in this case I enforce a compile-time error if _InnerSink doesn't have a Finish()-method!
			// @ToDo: enforce this by having a FinishableSink-concept!
			_InnerSink.Finish();
			/*
			if constexpr (requires { _InnerSink.Finish(); })
			{
				_InnerSink.Finish();
			}
			*/

			WriteFooter();
			Flush();
		}

		inline void Flush()
		{
			if constexpr (requires { _InnerSink.Flush(); })
			{
				_InnerSink.Flush();
			}
		}
	private:
		inline void WriteHeader()
		{
			if (_HasWrittenHeader)
			{
				return;
			}

			static constexpr const Elysium::Core::Template::System::size HeaderSize = sizeof(Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibHeader);
			assert(HeaderSize == 2);

			DeviceType& Device = _InnerSink.GetDevice();

			Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibHeader Header;
			Header.SetCompressionMethod(Elysium::Core::Template::IO::Compression::KnownCompressionAlgorithm::Deflate);
			Header.SetCompressionInfo(0x07);
			Header.SetFlagLevel(0x02);
			Header.SetFlagDictionary(false);
			Header.RecalculateFlagCheck();

			Device.Write(reinterpret_cast<Elysium::Core::Template::System::byte*>(&Header), HeaderSize);

			_HasWrittenHeader = true;
		}

		inline void WriteFooter()
		{
			if (_HasWrittenFooter)
			{
				return;
			}

			DeviceType& Device = _InnerSink.GetDevice();

			// adler32 in the footer is BE
#if defined ELYSIUM_CORE_LITTLEENDIAN
			_Adler32 = (_Adler32 << 24) | ((_Adler32 << 8) & 0x00FF0000) | ((_Adler32 >> 8) & 0x0000FF00) | (_Adler32 >> 24);
#endif

			Device.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_Adler32), sizeof(Elysium::Core::Template::System::uint32_t));
			
			_HasWrittenFooter = true;
		}
	private:
		InnerSink& _InnerSink;

		Elysium::Core::Template::System::uint32_t _Adler32;

		bool _HasWrittenHeader;
		bool _HasWrittenFooter;
	};
}
#endif
