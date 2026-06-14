/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEDECODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR
#include "../../Container/KeyValuePair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_BITREADER
#include "../../../BitReader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKHEADER
#include "../../Format/Deflate/DeflateBlockHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#include "../../Format/Deflate/DeflateBlockType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATESTATE
#include "../../Format/Deflate/DeflateState.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::Deflate
{
	class DeflateDecoder final
	{
	public:
		inline constexpr DeflateDecoder() noexcept
			: _State(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingHeader)
		{ }

		constexpr DeflateDecoder(const DeflateDecoder& Source) = delete;

		constexpr DeflateDecoder(DeflateDecoder&& Right) noexcept = delete;

		~DeflateDecoder() = default;
	public:
		constexpr DeflateDecoder & operator=(const DeflateDecoder & Source) = delete;

		constexpr DeflateDecoder& operator=(DeflateDecoder&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState GetState() const noexcept
		{
			return _State;
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult Decode(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2>& SourceSpans,
			Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2>& TargetSpan)
		{
			const Elysium::Core::Template::System::byte* SourceData = SourceSpans.GetFirst().GetData();
			const Elysium::Core::Template::System::size SourceLength = SourceSpans.GetFirst().GetLength();

			Elysium::Core::Template::IO::BitReader Reader(SourceData, SourceLength);

			while (true)
			{
				switch (_State)
				{
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingHeader:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadHeader();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{	// @ToDo
						throw 1;
					}

					const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader* Header =
						reinterpret_cast<const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader*>(SourceData);

					const bool IsFinalBlock = Header->GetIsFinalBlock();
					const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType BlockType = Header->GetCompressionMethod();

					switch (BlockType)
					{
					case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Uncompressed:
						_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::CopyingUncompressed;
						break;
					case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::FixedHuffman:
						_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecodingFixedHuffman;
						break;
					case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::DynamicHuffman:
						_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecodingDynamicHuffman;
						break;
					case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Invalid:
						_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecodingInvalidReserved;
						// @ToDo: throw specific exception
						throw 1;
					default:
						// @ToDo: is there actually anything to do? with two bits all bases are covered and this case should never happen
						throw 1;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::CopyingUncompressed:
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecodingFixedHuffman:
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecodingDynamicHuffman:
				{

					//Elysium::Core::Template::System::uint16_t HLIT = Data[0] & 0x1F;
					//Elysium::Core::Template::System::uint16_t HLIT = (Data[0] & 0x1F) + 257;

					


					const bool fasdf = false;
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecodingInvalidReserved:
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done:
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				default:
					// @ToDo
					throw 1;
				}
			}

			return Elysium::Core::Template::IO::ReadResult::EndOfStream;
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadHeader()
		{


			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
	private:
		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState _State;

	};
}
#endif
