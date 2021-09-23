#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core.IO/HuffmanTree.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Algorithms.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Tuple.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::IO::Compression;
using namespace Elysium::Core::IO::Compression::HuffmanCoding;
using namespace Elysium::Core::Template;
using namespace Elysium::Core::Template::Algorithms::Sorting;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO::Compression::HuffmanCoding
{
	template<template <class, class> class T, class T1, class T2>
	struct TupleSymbolFrequencyComparer
	{
		bool operator()(const T<T1, T2>& Value1, const T<T1, T2>& Value2) const
		{
			return Value1.GetItem2() > Value2.GetItem2();
		}
	};

	TEST_CLASS(HuffmanTreeTests)
	{
	public:
		TEST_METHOD(BuildManuallyAndDecompress)
		{
			HuffmanTree Tree = HuffmanTree();
			HuffmanNode& RootNode = Tree.GetRootNode();

			HuffmanNode* Node0 = RootNode.SetLeft();
			HuffmanNode* Node00 = Node0->SetLeft(0x00);
			HuffmanNode* Node01 = Node0->SetRight();
			HuffmanNode* Node010 = Node01->SetLeft(0x01);
			HuffmanNode* Node011 = Node01->SetRight(0x02);

			HuffmanNode* Node1 = RootNode.SetRight();
			HuffmanNode* Node10 = Node1->SetLeft();
			HuffmanNode* Node100 = Node10->SetLeft(0x03);
			HuffmanNode* Node101 = Node10->SetRight(0x04);
			HuffmanNode* Node11 = Node1->SetRight();
			HuffmanNode* Node110 = Node11->SetLeft(0x05);
			HuffmanNode* Node111 = Node11->SetRight();
			HuffmanNode* Node1110 = Node111->SetLeft(0x06);
			HuffmanNode* Node1111 = Node111->SetRight();
			HuffmanNode* Node11110 = Node1111->SetLeft(0x07);
			HuffmanNode* Node11111 = Node1111->SetRight();
			HuffmanNode* Node111110 = Node11111->SetLeft(0x08);
			HuffmanNode* Node111111 = Node11111->SetRight();
			HuffmanNode* Node1111110 = Node111111->SetLeft(0x08);
			HuffmanNode* Node1111111 = Node111111->SetRight();
			HuffmanNode* Node11111110 = Node1111111->SetLeft(0x09);
			HuffmanNode* Node11111111 = Node1111111->SetRight();
			HuffmanNode* Node111111110 = Node1111111->SetLeft(0x0A);
			HuffmanNode* Node111111111 = Node1111111->SetRight();
			HuffmanNode* Node1111111110 = Node111111111->SetLeft(0x0B);

			// 0x8A: 1000 1010
			// 0x28: 0010 1000
			// 0x00: 0000 0000
			// 0xA2: 1010 0010
			// 0x03: 0000 0011

			/*
			Elysium::Core::uint8_t CompressedDataLength = 255;
			Elysium::Core::byte CompressedData[] = 
			{
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2,

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28, 0x00, 0xA2, 

				0x8A, 0x28, 0x00, 0xA2, 
				0x8A, 0x28,	0x03
			};
			*/

			MemoryStream TargetStream = MemoryStream();

			Assert::Fail();
		}

		TEST_METHOD(CompressAndDecompress)
		{
			Tuple<char8_t, int32_t> SymbolFrequencies[] =
			{
				Tuple<char8_t, int32_t>(0x00, 0), Tuple<char8_t, int32_t>(0x01, 0), Tuple<char8_t, int32_t>(0x02, 0), Tuple<char8_t, int32_t>(0x03, 0),
				Tuple<char8_t, int32_t>(0x04, 0), Tuple<char8_t, int32_t>(0x05, 0), Tuple<char8_t, int32_t>(0x06, 0), Tuple<char8_t, int32_t>(0x07, 0),
				Tuple<char8_t, int32_t>(0x08, 0), Tuple<char8_t, int32_t>(0x09, 0), Tuple<char8_t, int32_t>(0x0A, 0), Tuple<char8_t, int32_t>(0x0B, 0),
				Tuple<char8_t, int32_t>(0x0C, 0), Tuple<char8_t, int32_t>(0x0D, 0), Tuple<char8_t, int32_t>(0x0E, 0), Tuple<char8_t, int32_t>(0x0F, 0),

				Tuple<char8_t, int32_t>(0x10, 0), Tuple<char8_t, int32_t>(0x11, 0), Tuple<char8_t, int32_t>(0x12, 0), Tuple<char8_t, int32_t>(0x13, 0),
				Tuple<char8_t, int32_t>(0x14, 0), Tuple<char8_t, int32_t>(0x15, 0), Tuple<char8_t, int32_t>(0x16, 0), Tuple<char8_t, int32_t>(0x17, 0),
				Tuple<char8_t, int32_t>(0x18, 0), Tuple<char8_t, int32_t>(0x19, 0), Tuple<char8_t, int32_t>(0x1A, 0), Tuple<char8_t, int32_t>(0x1B, 0),
				Tuple<char8_t, int32_t>(0x1C, 0), Tuple<char8_t, int32_t>(0x1D, 0), Tuple<char8_t, int32_t>(0x1E, 0), Tuple<char8_t, int32_t>(0x1F, 0),

				Tuple<char8_t, int32_t>(0x20, 0), Tuple<char8_t, int32_t>(0x21, 0), Tuple<char8_t, int32_t>(0x22, 0), Tuple<char8_t, int32_t>(0x23, 0),
				Tuple<char8_t, int32_t>(0x24, 0), Tuple<char8_t, int32_t>(0x25, 0), Tuple<char8_t, int32_t>(0x26, 0), Tuple<char8_t, int32_t>(0x27, 0),
				Tuple<char8_t, int32_t>(0x28, 0), Tuple<char8_t, int32_t>(0x29, 0), Tuple<char8_t, int32_t>(0x2A, 0), Tuple<char8_t, int32_t>(0x2B, 0),
				Tuple<char8_t, int32_t>(0x2C, 0), Tuple<char8_t, int32_t>(0x2D, 0), Tuple<char8_t, int32_t>(0x2E, 0), Tuple<char8_t, int32_t>(0x2F, 0),

				Tuple<char8_t, int32_t>(0x30, 0), Tuple<char8_t, int32_t>(0x31, 0), Tuple<char8_t, int32_t>(0x32, 0), Tuple<char8_t, int32_t>(0x33, 0),
				Tuple<char8_t, int32_t>(0x34, 0), Tuple<char8_t, int32_t>(0x35, 0), Tuple<char8_t, int32_t>(0x36, 0), Tuple<char8_t, int32_t>(0x37, 0),
				Tuple<char8_t, int32_t>(0x38, 0), Tuple<char8_t, int32_t>(0x39, 0), Tuple<char8_t, int32_t>(0x3A, 0), Tuple<char8_t, int32_t>(0x3B, 0),
				Tuple<char8_t, int32_t>(0x3C, 0), Tuple<char8_t, int32_t>(0x3D, 0), Tuple<char8_t, int32_t>(0x3E, 0), Tuple<char8_t, int32_t>(0x3F, 0),

				Tuple<char8_t, int32_t>(0x40, 0), Tuple<char8_t, int32_t>(0x41, 0), Tuple<char8_t, int32_t>(0x42, 0), Tuple<char8_t, int32_t>(0x43, 0),
				Tuple<char8_t, int32_t>(0x44, 0), Tuple<char8_t, int32_t>(0x45, 0), Tuple<char8_t, int32_t>(0x46, 0), Tuple<char8_t, int32_t>(0x47, 0),
				Tuple<char8_t, int32_t>(0x48, 0), Tuple<char8_t, int32_t>(0x49, 0), Tuple<char8_t, int32_t>(0x4A, 0), Tuple<char8_t, int32_t>(0x4B, 0),
				Tuple<char8_t, int32_t>(0x4C, 0), Tuple<char8_t, int32_t>(0x4D, 0), Tuple<char8_t, int32_t>(0x4E, 0), Tuple<char8_t, int32_t>(0x4F, 0),

				Tuple<char8_t, int32_t>(0x50, 0), Tuple<char8_t, int32_t>(0x51, 0), Tuple<char8_t, int32_t>(0x52, 0), Tuple<char8_t, int32_t>(0x53, 0),
				Tuple<char8_t, int32_t>(0x54, 0), Tuple<char8_t, int32_t>(0x55, 0), Tuple<char8_t, int32_t>(0x56, 0), Tuple<char8_t, int32_t>(0x57, 0),
				Tuple<char8_t, int32_t>(0x58, 0), Tuple<char8_t, int32_t>(0x59, 0), Tuple<char8_t, int32_t>(0x5A, 0), Tuple<char8_t, int32_t>(0x5B, 0),
				Tuple<char8_t, int32_t>(0x5C, 0), Tuple<char8_t, int32_t>(0x5D, 0), Tuple<char8_t, int32_t>(0x5E, 0), Tuple<char8_t, int32_t>(0x5F, 0),

				Tuple<char8_t, int32_t>(0x60, 0), Tuple<char8_t, int32_t>(0x61, 0), Tuple<char8_t, int32_t>(0x62, 0), Tuple<char8_t, int32_t>(0x63, 0),
				Tuple<char8_t, int32_t>(0x64, 0), Tuple<char8_t, int32_t>(0x65, 0), Tuple<char8_t, int32_t>(0x66, 0), Tuple<char8_t, int32_t>(0x67, 0),
				Tuple<char8_t, int32_t>(0x68, 0), Tuple<char8_t, int32_t>(0x69, 0), Tuple<char8_t, int32_t>(0x6A, 0), Tuple<char8_t, int32_t>(0x6B, 0),
				Tuple<char8_t, int32_t>(0x6C, 0), Tuple<char8_t, int32_t>(0x6D, 0), Tuple<char8_t, int32_t>(0x6E, 0), Tuple<char8_t, int32_t>(0x6F, 0),

				Tuple<char8_t, int32_t>(0x70, 0), Tuple<char8_t, int32_t>(0x71, 0), Tuple<char8_t, int32_t>(0x72, 0), Tuple<char8_t, int32_t>(0x73, 0),
				Tuple<char8_t, int32_t>(0x74, 0), Tuple<char8_t, int32_t>(0x75, 0), Tuple<char8_t, int32_t>(0x76, 0), Tuple<char8_t, int32_t>(0x77, 0),
				Tuple<char8_t, int32_t>(0x78, 0), Tuple<char8_t, int32_t>(0x79, 0), Tuple<char8_t, int32_t>(0x7A, 0), Tuple<char8_t, int32_t>(0x7B, 0),
				Tuple<char8_t, int32_t>(0x7C, 0), Tuple<char8_t, int32_t>(0x7D, 0), Tuple<char8_t, int32_t>(0x7E, 0), Tuple<char8_t, int32_t>(0x7F, 0),

				Tuple<char8_t, int32_t>(0x80, 0), Tuple<char8_t, int32_t>(0x81, 0), Tuple<char8_t, int32_t>(0x82, 0), Tuple<char8_t, int32_t>(0x83, 0),
				Tuple<char8_t, int32_t>(0x84, 0), Tuple<char8_t, int32_t>(0x85, 0), Tuple<char8_t, int32_t>(0x86, 0), Tuple<char8_t, int32_t>(0x87, 0),
				Tuple<char8_t, int32_t>(0x88, 0), Tuple<char8_t, int32_t>(0x89, 0), Tuple<char8_t, int32_t>(0x8A, 0), Tuple<char8_t, int32_t>(0x8B, 0),
				Tuple<char8_t, int32_t>(0x8C, 0), Tuple<char8_t, int32_t>(0x8D, 0), Tuple<char8_t, int32_t>(0x8E, 0), Tuple<char8_t, int32_t>(0x8F, 0),

				Tuple<char8_t, int32_t>(0x90, 0), Tuple<char8_t, int32_t>(0x91, 0), Tuple<char8_t, int32_t>(0x92, 0), Tuple<char8_t, int32_t>(0x93, 0),
				Tuple<char8_t, int32_t>(0x94, 0), Tuple<char8_t, int32_t>(0x95, 0), Tuple<char8_t, int32_t>(0x96, 0), Tuple<char8_t, int32_t>(0x97, 0),
				Tuple<char8_t, int32_t>(0x98, 0), Tuple<char8_t, int32_t>(0x99, 0), Tuple<char8_t, int32_t>(0x9A, 0), Tuple<char8_t, int32_t>(0x9B, 0),
				Tuple<char8_t, int32_t>(0x9C, 0), Tuple<char8_t, int32_t>(0x9D, 0), Tuple<char8_t, int32_t>(0x9E, 0), Tuple<char8_t, int32_t>(0x9F, 0),

				Tuple<char8_t, int32_t>(0xA0, 0), Tuple<char8_t, int32_t>(0xA1, 0), Tuple<char8_t, int32_t>(0xA2, 0), Tuple<char8_t, int32_t>(0xA3, 0),
				Tuple<char8_t, int32_t>(0xA4, 0), Tuple<char8_t, int32_t>(0xA5, 0), Tuple<char8_t, int32_t>(0xA6, 0), Tuple<char8_t, int32_t>(0xA7, 0),
				Tuple<char8_t, int32_t>(0xA8, 0), Tuple<char8_t, int32_t>(0xA9, 0), Tuple<char8_t, int32_t>(0xAA, 0), Tuple<char8_t, int32_t>(0xAB, 0),
				Tuple<char8_t, int32_t>(0xAC, 0), Tuple<char8_t, int32_t>(0xAD, 0), Tuple<char8_t, int32_t>(0xAE, 0), Tuple<char8_t, int32_t>(0xAF, 0),

				Tuple<char8_t, int32_t>(0xB0, 0), Tuple<char8_t, int32_t>(0xB1, 0), Tuple<char8_t, int32_t>(0xB2, 0), Tuple<char8_t, int32_t>(0xB3, 0),
				Tuple<char8_t, int32_t>(0xB4, 0), Tuple<char8_t, int32_t>(0xB5, 0), Tuple<char8_t, int32_t>(0xB6, 0), Tuple<char8_t, int32_t>(0xB7, 0),
				Tuple<char8_t, int32_t>(0xB8, 0), Tuple<char8_t, int32_t>(0xB9, 0), Tuple<char8_t, int32_t>(0xBA, 0), Tuple<char8_t, int32_t>(0xBB, 0),
				Tuple<char8_t, int32_t>(0xBC, 0), Tuple<char8_t, int32_t>(0xBD, 0), Tuple<char8_t, int32_t>(0xBE, 0), Tuple<char8_t, int32_t>(0xBF, 0),

				Tuple<char8_t, int32_t>(0xC0, 0), Tuple<char8_t, int32_t>(0xC1, 0), Tuple<char8_t, int32_t>(0xC2, 0), Tuple<char8_t, int32_t>(0xC3, 0),
				Tuple<char8_t, int32_t>(0xC4, 0), Tuple<char8_t, int32_t>(0xC5, 0), Tuple<char8_t, int32_t>(0xC6, 0), Tuple<char8_t, int32_t>(0xC7, 0),
				Tuple<char8_t, int32_t>(0xC8, 0), Tuple<char8_t, int32_t>(0xC9, 0), Tuple<char8_t, int32_t>(0xCA, 0), Tuple<char8_t, int32_t>(0xCB, 0),
				Tuple<char8_t, int32_t>(0xCC, 0), Tuple<char8_t, int32_t>(0xCD, 0), Tuple<char8_t, int32_t>(0xCE, 0), Tuple<char8_t, int32_t>(0xCF, 0),

				Tuple<char8_t, int32_t>(0xD0, 0), Tuple<char8_t, int32_t>(0xD1, 0), Tuple<char8_t, int32_t>(0xD2, 0), Tuple<char8_t, int32_t>(0xD3, 0),
				Tuple<char8_t, int32_t>(0xD4, 0), Tuple<char8_t, int32_t>(0xD5, 0), Tuple<char8_t, int32_t>(0xD6, 0), Tuple<char8_t, int32_t>(0xD7, 0),
				Tuple<char8_t, int32_t>(0xD8, 0), Tuple<char8_t, int32_t>(0xD9, 0), Tuple<char8_t, int32_t>(0xDA, 0), Tuple<char8_t, int32_t>(0xDB, 0),
				Tuple<char8_t, int32_t>(0xDC, 0), Tuple<char8_t, int32_t>(0xDD, 0), Tuple<char8_t, int32_t>(0xDE, 0), Tuple<char8_t, int32_t>(0xDF, 0),

				Tuple<char8_t, int32_t>(0xE0, 0), Tuple<char8_t, int32_t>(0xE1, 0), Tuple<char8_t, int32_t>(0xE2, 0), Tuple<char8_t, int32_t>(0xE3, 0),
				Tuple<char8_t, int32_t>(0xE4, 0), Tuple<char8_t, int32_t>(0xE5, 0), Tuple<char8_t, int32_t>(0xE6, 0), Tuple<char8_t, int32_t>(0xE7, 0),
				Tuple<char8_t, int32_t>(0xE8, 0), Tuple<char8_t, int32_t>(0xE9, 0), Tuple<char8_t, int32_t>(0xEA, 0), Tuple<char8_t, int32_t>(0xEB, 0),
				Tuple<char8_t, int32_t>(0xEC, 0), Tuple<char8_t, int32_t>(0xED, 0), Tuple<char8_t, int32_t>(0xEE, 0), Tuple<char8_t, int32_t>(0xEF, 0),

				Tuple<char8_t, int32_t>(0xF0, 0), Tuple<char8_t, int32_t>(0xF1, 0), Tuple<char8_t, int32_t>(0xF2, 0), Tuple<char8_t, int32_t>(0xF3, 0),
				Tuple<char8_t, int32_t>(0xF4, 0), Tuple<char8_t, int32_t>(0xF5, 0), Tuple<char8_t, int32_t>(0xF6, 0), Tuple<char8_t, int32_t>(0xF7, 0),
				Tuple<char8_t, int32_t>(0xF8, 0), Tuple<char8_t, int32_t>(0xF9, 0), Tuple<char8_t, int32_t>(0xFA, 0), Tuple<char8_t, int32_t>(0xFB, 0),
				Tuple<char8_t, int32_t>(0xFC, 0), Tuple<char8_t, int32_t>(0xFD, 0), Tuple<char8_t, int32_t>(0xFE, 0), Tuple<char8_t, int32_t>(0xFF, 0),
			};

			String Input = u8">This is some< test הצ?`ßהצü.";
			for (size_t i = 0; i < Input.GetLength(); i++)
			{
				Elysium::Core::byte CurrentByte = Input[i];
				SymbolFrequencies[CurrentByte].GetItem2()++;
			}

			TupleSymbolFrequencyComparer<Tuple, char8_t, int32_t> Comparer = TupleSymbolFrequencyComparer<Tuple, char8_t, int32_t>();
			BubbleSort(&SymbolFrequencies[0], 255, Comparer);

			size_t FirstSymbolWithFrequency = -1;
			for (size_t i = 0; i < 255; i++)
			{
				if (SymbolFrequencies[i].GetItem2() > 0)
				{
					FirstSymbolWithFrequency = i;
					break;
				}
			}

			if (FirstSymbolWithFrequency == -1)
			{
				Assert::Fail(L"No symbols with frequency found. Input must have been empty.");
			}






			Assert::Fail();
		}
	};
}
