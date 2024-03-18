/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#define ELYSIUM_CORE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE

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
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression::HuffmanCoding
{
	class ELYSIUM_CORE_API HuffmanNode final
	{
		friend class HuffmanTree;
	public:
		HuffmanNode(const Elysium::Core::byte Symbol);

		HuffmanNode(const HuffmanNode& Source) = delete;

		HuffmanNode(HuffmanNode&& Right) noexcept = delete;

		~HuffmanNode();
	public:
		HuffmanNode& operator=(const HuffmanNode& Source) = delete;

		HuffmanNode& operator=(HuffmanNode&& Right) noexcept = delete;
	public:
		const Elysium::Core::byte GetSymbol() const;

		const HuffmanNode* GetLeft() const;

		const HuffmanNode* GetRight() const;

		const bool GetIsLeaf() const;
	public:
		void SetSymbol(const Elysium::Core::byte Value);

		HuffmanNode* SetLeft(const Elysium::Core::byte Symbol = 0x00);

		HuffmanNode* SetRight(const Elysium::Core::byte Symbol = 0x00);
	public:
		const HuffmanNode* Find(const Elysium::Core::byte Symbol) const;
	private:
		Elysium::Core::byte _Symbol;
		HuffmanNode* _Left;
		HuffmanNode* _Right;
	};
}
#endif
