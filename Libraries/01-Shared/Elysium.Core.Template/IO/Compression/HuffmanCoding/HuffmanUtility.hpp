/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANUTILITY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANUTILITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_QUEUE_VECTOR
#include "../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANCODE
#include "HuffmanCode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLCODELENGTHPAIR
#include "HuffmanSymbolCodeLengthPair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S>
	class HuffmanUtility
	{
	public:
		using SymbolCodeMap = Elysium::Core::Template::Container::UnorderedMap<S, HuffmanCode>;
	public:
		constexpr HuffmanUtility() = delete;

		constexpr HuffmanUtility(const HuffmanUtility& Source) = delete;

		constexpr HuffmanUtility(HuffmanUtility&& Right) noexcept = delete;

		constexpr ~HuffmanUtility() = delete;
	public:
		constexpr HuffmanUtility& operator=(const HuffmanUtility& Source) = delete;

		constexpr HuffmanUtility& operator=(HuffmanUtility&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Packs fields into a single key to help prevent hash-collisions during decoding.
		/// </summary>
		/// <param name="Bits"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		inline static constexpr const Elysium::Core::Template::System::uint64_t GetPackedKey(const Elysium::Core::Template::System::uint32_t Bits,
			Elysium::Core::Template::System::uint8_t Length)
		{
			return (static_cast<Elysium::Core::Template::System::uint64_t>(Length) << 32 | Bits);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="SymbolCodeLengths"></param>
		/// <returns></returns>
		inline static SymbolCodeMap CreateFromSymbolCodeLengths(const Elysium::Core::Template::Container::Vector<HuffmanSymbolCodeLengthPair<S>>& SymbolCodeLengths)
		{
			SymbolCodeMap Codes = SymbolCodeMap();
			Elysium::Core::Template::System::size CurrentCode = 0;
			Elysium::Core::Template::System::size CurrentCodeLength = SymbolCodeLengths[0]._CodeLength;
			for (Elysium::Core::Template::System::size i = 0; i < SymbolCodeLengths.GetLength(); ++i)
			{
				const char Symbol = SymbolCodeLengths[i]._Symbol;

				if (SymbolCodeLengths[i]._CodeLength > CurrentCodeLength)
				{
					CurrentCode <<= (SymbolCodeLengths[i]._CodeLength - CurrentCodeLength);
					CurrentCodeLength = SymbolCodeLengths[i]._CodeLength;
				}

				Codes.Set(SymbolCodeLengths[i]._Symbol, HuffmanCode(CurrentCode, SymbolCodeLengths[i]._CodeLength));
				++CurrentCode;
			}

			return Codes;
		}
	};
}
#endif
