/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_ZLIBSOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_ZLIBSOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_ZLIB_ZLIBHEADER
#include "../Compression/Format/ZLib/ZLibHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_ZLIB_ZLIBSTATE
#include "../Compression/Format/ZLib/ZLibState.hpp"
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

#include <cassert>

namespace Elysium::Core::Template::IO::Source
{
	// @ToDo: concept for sources!
	template <class InnerSource>
	class ZLibSource
	{
	public:
		using DeviceType = InnerSource::DeviceType;

		using MostInnerSourceType = InnerSource::MostInnerSourceType;
	public:
		inline constexpr ZLibSource(InnerSource& InnerSource) noexcept
			: _State(Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::ReadingHeader), _Adler32(0x01), 
			_InnerSource(InnerSource), _MostInnerSource(_InnerSource.GetMostInnerSource())
		{ }

		constexpr ZLibSource(const ZLibSource& Source) = delete;

		constexpr ZLibSource(ZLibSource&& Right) noexcept = delete;

		constexpr ~ZLibSource() = default;
	public:
		constexpr ZLibSource& operator=(const ZLibSource& Source) = delete;

		constexpr ZLibSource& operator=(ZLibSource&& Right) noexcept = delete;
	public:
		inline MostInnerSourceType& GetMostInnerSource()
		{
			return _InnerSource.GetMostInnerSource();
		}

		inline DeviceType& GetDevice()
		{
			return _InnerSource.GetDevice();
		}

		inline constexpr DeviceType& GetDevice() const
		{
			return _InnerSource.GetDevice();
		}
	public:
		inline constexpr Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSource.GetLength();
		}

		inline constexpr Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSource.GetPosition();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSource.SetPosition(Position);
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetView)
		{
			// @ToDo: this is nice for debugging but probably unnecessary
			{
				TargetView.SetData(nullptr);
				TargetView.SetLength(0);
			}

			while (true)
			{
				switch (_State)
				{
				case Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::ReadingHeader:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadHeader();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::DecodingBlock:
				{
					const Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(TargetView);
					switch (Result)
					{
					case Elysium::Core::Template::IO::ReadResult::HasData:
					{
						const Elysium::Core::Template::System::byte* Data = TargetView.GetData();
						const Elysium::Core::Template::System::size Length = TargetView.GetLength();
						if (nullptr != Data && 0 != Length)
						{
							_Adler32 = Elysium::Core::Template::Security::Cryptography::Checksum::Adler32::CalculateBytewise(_Adler32, Data, Length);
						}
					}
					return Result;
					case Elysium::Core::Template::IO::ReadResult::Pending:
						return Result;
					case Elysium::Core::Template::IO::ReadResult::EndOfStream:
						_State = Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::ReadingFooter;
						break;
					default:
						// @ToDo: throw specific exception
						throw 1;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::ReadingFooter:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadFooter();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
					_State = Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::Done;
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::Done:
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				default:
					// @ToDo: throw specific exception
					throw;
				}
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			_InnerSource.AdvanceReadingBlock(Length);
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadHeader()
		{
			static constexpr const Elysium::Core::Template::System::size HeaderSize = sizeof(Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibHeader);
			assert(HeaderSize == 2);

			Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibHeader* AddressOfHeader;

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _MostInnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				if (SourceSpan.GetLength() < HeaderSize)
				{
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				AddressOfHeader = reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibHeader*>(SourceSpan.GetData());
			}
				break;
			case Elysium::Core::Template::IO::ReadResult::Pending:
				return Result;
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
				// @ToDo
				throw;
			default:
				// @ToDo
				throw;
			}

			if (!AddressOfHeader->Validate())
			{	// @ToDo
				throw;
			}

			const Elysium::Core::Template::System::byte CompressionMethod = AddressOfHeader->GetCompressionMethod();
			if (8 != CompressionMethod)
			{	// @ToDo: I currently only support deflate (8)
				throw;
			}

			const Elysium::Core::Template::System::byte CompressionInfo = AddressOfHeader->GetCompressionInfo();
			if (7 != CompressionInfo)
			{	// @ToDo: I currently only support deflate with a 32kb history buffer (7)
				throw;
			}

			const Elysium::Core::Template::System::byte FlagLevel = AddressOfHeader->GetFlagLevel();

			const bool UsesPresetDictionary = AddressOfHeader->GetFlagDictionary();
			if (UsesPresetDictionary)
			{
				// @ToDo: read another 4 bytes. that's the dictionary required for decoding!
			}

			_MostInnerSource.AdvanceReadingBlock(HeaderSize);

			_State = Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState::DecodingBlock;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadFooter()
		{
			Elysium::Core::Template::System::uint32_t Adler32;

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				if (SourceSpan.GetLength() < sizeof(Adler32))
				{
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				// adler32 in the footer is BE
				Adler32 = *reinterpret_cast<Elysium::Core::Template::System::uint32_t*>(SourceSpan.GetData());
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Adler32 = (Adler32 << 24) | ((Adler32 << 8) & 0x00FF0000) | ((Adler32 >> 8) & 0x0000FF00) | (Adler32 >> 24);
#endif
				if (_Adler32 != Adler32)
				{	// @ToDo
					throw;
				}

				_InnerSource.AdvanceReadingBlock(sizeof(Adler32));

				return Elysium::Core::Template::IO::ReadResult::EndOfStream;
			}
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
			{	// @ToDo
				throw;
			}
			case Elysium::Core::Template::IO::ReadResult::Pending:
				return Result;
			default:
				throw;
			}
		}
	private:
		Elysium::Core::Template::IO::Compression::Format::ZLib::ZLibState _State;

		Elysium::Core::Template::System::uint32_t _Adler32;

		InnerSource& _InnerSource;
		MostInnerSourceType& _MostInnerSource;
	};
}
#endif