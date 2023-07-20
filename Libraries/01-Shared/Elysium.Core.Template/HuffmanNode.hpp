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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<class T>
	class HuffmanNode
	{
	public:
		HuffmanNode(const T Symbol);

		HuffmanNode(const HuffmanNode& Source) = delete;

		HuffmanNode(HuffmanNode&& Right) noexcept = delete;

		~HuffmanNode();
	public:
		HuffmanNode& operator=(const HuffmanNode& Source) = delete;

		HuffmanNode& operator=(HuffmanNode&& Right) noexcept = delete;
	private:
		T _Symbol;
		HuffmanNode* _Left;
		HuffmanNode* _Right;
	};

	template<class T>
	Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanNode<T>::HuffmanNode(const T Symbol)
		: _Symbol(Symbol), _Left(nullptr), _Right(nullptr)
	{ }

	template<class T>
	Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanNode<T>::~HuffmanNode()
	{ }

}
#endif
