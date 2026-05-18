/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../Concepts/UnsignedInteger.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanEncoder;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanDecoder;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanTree;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanNode
	{
		friend class HuffmanEncoder<S, F>;
		friend class HuffmanDecoder<S, F>;
		friend class HuffmanTree<S, F>;
	public:
		constexpr HuffmanNode() = delete;

		inline constexpr HuffmanNode(const S Symbol, const F Frequency)
			: _Symbol(Symbol), _Frequency(Frequency), _Left(nullptr), _Right(nullptr)
		{ }
	private:
		inline constexpr HuffmanNode(HuffmanNode* Left, HuffmanNode* Right)
			: _Symbol(0x00), _Frequency(Left->_Frequency + Right->_Frequency), _Left(Left), _Right(Right)
		{ }
	public:
		constexpr HuffmanNode(const HuffmanNode& Source) = delete;

		constexpr HuffmanNode(HuffmanNode&& Right) noexcept = delete;

		inline constexpr ~HuffmanNode()
		{
			if (nullptr != _Left)
			{
				delete _Left;
				_Left = nullptr;
			}

			if (nullptr != _Right)
			{
				delete _Right;
				_Right = nullptr;
			}
		}
	public:
		constexpr HuffmanNode& operator=(const HuffmanNode& Source) = delete;

		constexpr HuffmanNode& operator=(HuffmanNode&& Right) noexcept = delete;
	//private:
	public:
		S _Symbol;
		F _Frequency;

		HuffmanNode* _Left;
		HuffmanNode* _Right;
	};
}
#endif
