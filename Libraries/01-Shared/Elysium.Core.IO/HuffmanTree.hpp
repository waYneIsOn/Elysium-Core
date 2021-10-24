/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#define ELYSIUM_CORE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "HuffmanNode.hpp"
#endif

namespace Elysium::Core::IO::Compression::HuffmanCoding
{
	class ELYSIUM_CORE_API HuffmanTree final
	{
	public:
		HuffmanTree();
		HuffmanTree(const HuffmanTree& Source) = delete;
		HuffmanTree(HuffmanTree&& Right) noexcept = delete;
		~HuffmanTree();

		HuffmanTree& operator=(const HuffmanTree& Source) = delete;
		HuffmanTree& operator=(HuffmanTree&& Right) noexcept = delete;

		HuffmanNode& GetRootNode();
		const HuffmanNode& GetRootNode() const;
	private:
		HuffmanNode _Root;
	};
}
#endif
