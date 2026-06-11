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
		const Elysium::Core::Template::System::size Decode(Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte*, Elysium::Core::Template::System::size>& SourceSpan,
			Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte*, Elysium::Core::Template::System::size>& TargetSpan)
		{
			Elysium::Core::Template::System::byte* Data = SourceSpan.GetKey();

			while (true)
			{
				switch (_State)
				{
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingHeader:
				{
					// @ToDo: need a BitReader of some sort. while the first block is byte aligned, afterwards it might not be!!!!

					Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader* Header =
						reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader*>(Data);

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
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecodingInvalidReserved:
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done:
					return 0;
				default:
					// @ToDo
					throw 1;
				}
			}

			return 0;
		}
	private:
		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState _State;

	};
}
#endif
