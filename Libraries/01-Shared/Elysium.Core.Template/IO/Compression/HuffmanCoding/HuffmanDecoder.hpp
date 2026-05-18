/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANDECODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#include "HuffmanTree.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanDecoder
	{
		using Tree = HuffmanTree<S, F>;

		using Node = HuffmanNode<S, F>;
	public:
		constexpr HuffmanDecoder() = default;

		constexpr HuffmanDecoder(const HuffmanDecoder& Source) = delete;

		constexpr HuffmanDecoder(HuffmanDecoder&& Right) noexcept = delete;

		constexpr ~HuffmanDecoder() = default;
	public:
		constexpr HuffmanDecoder& operator=(const HuffmanDecoder& Source) = delete;

		constexpr HuffmanDecoder& operator=(HuffmanDecoder&& Right) noexcept = delete;
	public:

	};
}
#endif
