module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os"
#endif

#include <cassert>

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef _NEW_
#include <new>
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANCODE
#include "IO/Compression/HuffmanCoding/HuffmanCode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANDECODER
#include "IO/Compression/HuffmanCoding/HuffmanDecoder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANENCODER
#include "IO/Compression/HuffmanCoding/HuffmanEncoder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANFREQUENCYTABLE
#include "HuffmanFrequencyTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "IO/Compression/HuffmanCoding/HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLCODELENGTHPAIR
#include "IO/Compression/HuffmanCoding/HuffmanSymbolCodeLengthPair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLTRAITS
#include "IO/Compression/HuffmanCoding/HuffmanSymbolTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#include "IO/Compression/HuffmanCoding/HuffmanTree.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANUTILITY
#include "IO/Compression/HuffmanCoding/HuffmanUtility.hpp"
#endif

export module Elysium.Core.Template.IO.Compression.HuffmanCoding;

export
{
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanCode;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanDecoder;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanEncoder;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanFrequencyTable;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanNode;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanSymbolCodeLengthPair;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanSymbolTraits;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanTree;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanUtility;
}