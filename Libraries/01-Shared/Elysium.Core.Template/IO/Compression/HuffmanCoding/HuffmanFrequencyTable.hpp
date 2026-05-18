/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANFREQUENCYTABLE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANFREQUENCYTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#include "../../../Container/UnorderedMap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanEncoder;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanDecoder;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanFrequencyTable
	{
		friend class HuffmanEncoder<S, F>;
		friend class HuffmanDecoder<S, F>;
	private:
		constexpr HuffmanFrequencyTable() = default;
	public:
		constexpr HuffmanFrequencyTable(const HuffmanFrequencyTable& Source) = delete;

		constexpr HuffmanFrequencyTable(HuffmanFrequencyTable&& Right) noexcept = delete;

		constexpr ~HuffmanFrequencyTable() = default;
	public:
		constexpr HuffmanFrequencyTable& operator=(const HuffmanFrequencyTable& Source) = delete;

		constexpr HuffmanFrequencyTable& operator=(HuffmanFrequencyTable&& Right) noexcept = delete;
	public:
		inline constexpr const F operator[](const S Symbol) const
		{
			return _Occurrences[Symbol];
		}
	public:
		inline constexpr void Add(const S Symbol)
		{
			if (_Occurrences[Symbol])
			{
				++_Occurrences[Symbol];
			}
			else
			{
				_Occurrences.Set(Symbol, 1);
			}
		}

		inline constexpr const F GetLength() const
		{
			// @ToDo
			return 0;
			//return _Occurrences.GetLength()
		}
	private:
		Elysium::Core::Template::Container::UnorderedMap<S, F> _Occurrences{};
	};

	template<>
	class HuffmanFrequencyTable<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>
	{
		//static_assert(std::is_trivially_move_constructible_v< HuffmanFrequencyTable<S, F>>);

		friend class HuffmanEncoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
		friend class HuffmanDecoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
	private:
		constexpr HuffmanFrequencyTable() = default;
	public:
		constexpr HuffmanFrequencyTable(const HuffmanFrequencyTable& Source) = delete;

		constexpr HuffmanFrequencyTable(HuffmanFrequencyTable&& Right) noexcept = default;

		constexpr ~HuffmanFrequencyTable() = default;
	public:
		constexpr HuffmanFrequencyTable& operator=(const HuffmanFrequencyTable& Source) = delete;

		constexpr HuffmanFrequencyTable& operator=(HuffmanFrequencyTable&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size operator[](const Elysium::Core::Template::System::byte Symbol) const
		{
			return _Occurrences[Symbol];
		}
	public:
		inline constexpr void Add(const Elysium::Core::Template::System::byte Symbol)
		{
			++_Occurrences[Symbol];
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return OccurrencesLength;
		}
	private:
		static constexpr const Elysium::Core::Template::System::size OccurrencesLength = 256;
		Elysium::Core::Template::System::size _Occurrences[OccurrencesLength] = { 0 };
	};
}
#endif
