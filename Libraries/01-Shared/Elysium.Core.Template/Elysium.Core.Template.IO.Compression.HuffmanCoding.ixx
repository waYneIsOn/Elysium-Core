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

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "IO/Compression/HuffmanCoding/HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#include "IO/Compression/HuffmanCoding/HuffmanTree.hpp"
#endif

export module Elysium.Core.Template.IO.Compression.HuffmanCoding;

export
{
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanNode;
	using Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanTree;
}