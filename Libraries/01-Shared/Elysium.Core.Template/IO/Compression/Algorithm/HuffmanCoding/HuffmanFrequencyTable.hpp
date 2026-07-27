/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANFREQUENCYTABLE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANFREQUENCYTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "../../../../TypeTraits/Conditional.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F, Elysium::Core::Template::System::size AlphabetLength>
	class HuffmanFrequencyTable
	{
	public:
		using ContainerType = Elysium::Core::Template::TypeTraits::ConditionalType<AlphabetLength <= 256, F[AlphabetLength], Elysium::Core::Template::Container::Vector<F>>;
	public:
		constexpr HuffmanFrequencyTable() = default;

		constexpr HuffmanFrequencyTable(const HuffmanFrequencyTable& Source) = delete;

		constexpr HuffmanFrequencyTable(HuffmanFrequencyTable&& Right) noexcept = default;

		constexpr ~HuffmanFrequencyTable() = default;
	public:
		constexpr HuffmanFrequencyTable& operator=(const HuffmanFrequencyTable& Source) = delete;

		constexpr HuffmanFrequencyTable& operator=(HuffmanFrequencyTable&& Right) noexcept = delete;
	public:
		inline constexpr Elysium::Core::Template::System::size operator[](const Elysium::Core::Template::System::byte Symbol) const
		{
			return _Frequencies[Symbol];
		}
	public:
		inline constexpr Elysium::Core::Template::System::size GetAlphabetLength() const
		{
			return AlphabetLength;
		}

		inline constexpr Elysium::Core::Template::System::size GetFrequency(const Elysium::Core::Template::System::byte Symbol)
		{
			return _Frequencies[Symbol];
		}
	public:
		inline constexpr void Increment(const Elysium::Core::Template::System::byte Symbol)
		{
			++_Frequencies[Symbol];
		}
	private:
		ContainerType _Frequencies{};
	};
}
#endif
