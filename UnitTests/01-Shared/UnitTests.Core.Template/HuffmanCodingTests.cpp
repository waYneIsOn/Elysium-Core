#include "CppUnitTest.h"

#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Algorithms/Sorting/BubbleSort.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Container/Vector.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Compression/HuffmanCoding/HuffmanEncoder.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Compression/HuffmanCoding/HuffmanTree.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/CharacterTraits.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/Convert.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::IO::Compression::HuffmanCoding;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO::Compression::HuffmanCoding
{
	TEST_CLASS(HuffmanCodingTests)
	{
		//using BinaryHuffmanX = ;

		using BinaryHuffmanTree = HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
	public:
		TEST_METHOD(UseCalculatedHuffmanCodes)
		{
			const Elysium::Core::Template::System::byte* Input = reinterpret_cast<const Elysium::Core::Template::System::byte*>(_LoremIpsum);
			const Elysium::Core::Template::System::size InputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(_LoremIpsum);

			// https://www.rfc-editor.org/rfc/rfc1951
			// https://www.rfc-editor.org/rfc/rfc1951
			// https://www.rfc-editor.org/rfc/rfc1951
			// https://www.rfc-editor.org/rfc/rfc1951
			// https://www.rfc-editor.org/rfc/rfc1951
			// https://www.rfc-editor.org/rfc/rfc1951
			// https://www.rfc-editor.org/rfc/rfc1951
			// https://www.rfc-editor.org/rfc/rfc1951

			/*
			* Steps to do "tree-based" huffman coding (used in ...):
			* 1.) Count occurrences of each symbol
			* 2.) Generate huffman tree
			* 3.) Generate codes directly
			* 
			* Steps to do "canonical" huffman coding (used in deflate, jpg (can use arithmetic huffman coding but rarely used bc of patents), brotli, bzip2 etc.):
			* 1.) Count occurrences of each symbol
			* 2.) Generate huffman tree (NOTE: conceptual tree! it does not need to exist) @ToDo: skip that part and derive code-lengths directly from occurrences!
			* 3.) Derive code-lengths for each symbol from that tree
			* 4.) Sort that symbol/code-length pair
			* 5.) Generate codes from that ordered data
			*/

			BinaryHuffmanTree Tree = BinaryHuffmanTree::Build(Input, InputLength, true);
			PrintTree(Tree._Root);
			Logger::WriteMessage("-------------------\r\n");
			
			BinaryHuffmanTree::CodeLengthsMap CodeLengths = Tree.DeriveCodeLengths();
			



			Elysium::Core::Template::Container::Vector<BinaryHuffmanTree::SymbolCodeLengthPair> SymbolCodeLengths;
			for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>::FIterator Iterator = CodeLengths.GetBegin();
				Iterator != CodeLengths.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>& Item = Node->GetItem();
				
				SymbolCodeLengths.PushBack(BinaryHuffmanTree::SymbolCodeLengthPair(Item.GetKey(), Item.GetValue()));
			}
			
			BinaryHuffmanTree::SymbolCodeLengthPair& First = *SymbolCodeLengths.GetBegin();
			BinaryHuffmanTree::SymbolCodeLengthPair& Last = *SymbolCodeLengths.GetEnd();
			Elysium::Core::Template::Algorithms::Sorting::BubbleSort<BinaryHuffmanTree::SymbolCodeLengthPair*>(&First, &Last);




			PrintCodeLengths(SymbolCodeLengths);
			// -----------------------
			
			BinaryHuffmanTree::SymbolCodeMap SymbolCodes = Tree.GenerateCanonicalCodes(SymbolCodeLengths);
			PrintCodes(SymbolCodes);
			// -----------------------
			/*
			BinaryHuffmanTree::SymbolCodeMap NonCanonicalCodes = Tree.GenerateNonCanonicalCodes();
			PrintCodes(NonCanonicalCodes);
			// -----------------------
			*/
		}

		TEST_METHOD(UseFixedHuffmanCodes)
		{
			// "Fixed huffman code" simply means holding predefined symbols and their code-lengths.
			// So nothing really changes except that I can skip the first three steps.
			// Assuming the fixed/predefined symbols and their code-lengths are sorted already, that leaves only the last step:
			// 5.) Generate canonical codes from that ordering

			Elysium::Core::Template::Container::Vector<BinaryHuffmanTree::SymbolCodeLengthPair> SymbolCodeLengths = 
				Elysium::Core::Template::Container::Vector<BinaryHuffmanTree::SymbolCodeLengthPair>(4);
			SymbolCodeLengths[0].Symbol = 'A';
			SymbolCodeLengths[0].CodeLength = 2;
			SymbolCodeLengths[1].Symbol = 'B';
			SymbolCodeLengths[1].CodeLength = 3;
			SymbolCodeLengths[2].Symbol = 'C';
			SymbolCodeLengths[2].CodeLength = 3;
			SymbolCodeLengths[3].Symbol = 'D';
			SymbolCodeLengths[3].CodeLength = 3;

			PrintCodeLengths(SymbolCodeLengths);
			// -----------------------

			BinaryHuffmanTree Tree{};
			BinaryHuffmanTree::SymbolCodeMap SymbolCodes = Tree.GenerateCanonicalCodes(SymbolCodeLengths);
			PrintCodes(SymbolCodes);
			// -----------------------




			constexpr const char* Text = "AACCCDDDBBB";
			const Elysium::Core::Template::System::byte* Input = reinterpret_cast<const Elysium::Core::Template::System::byte*>(Text);
			const Elysium::Core::Template::System::size InputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Text);
		}
	private:
		void PrintTree(const HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>::Node* CurrentNode)
		{
			if (nullptr == CurrentNode)
			{
				return;
			}

			if (!CurrentNode->_Left && !CurrentNode->_Right)
			{
				char PrintableSymbol[2] = { CurrentNode->_Symbol, 0x00 };
				Elysium::Core::Template::Text::String<char> Frequency = Elysium::Core::Template::Text::Convert<char>::ToString(CurrentNode->_Frequency);

				Logger::WriteMessage("Frequency: ");
				Logger::WriteMessage(PrintableSymbol);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&Frequency[0]);
				Logger::WriteMessage("\r\n");
			}

			PrintTree(CurrentNode->_Left);
			PrintTree(CurrentNode->_Right);
		}

		void PrintCodeLengths(const Elysium::Core::Template::Container::Vector<BinaryHuffmanTree::SymbolCodeLengthPair>& SymbolCodeLengths)
		{
			for (Elysium::Core::Template::System::size i = 0; i < SymbolCodeLengths.GetLength(); ++i)
			{
				const char Symbol = SymbolCodeLengths[i].Symbol;
				char PrintableSymbol[2] = { Symbol, 0x00 };

				const Elysium::Core::Template::Text::String<char>& CodeLength =
					Elysium::Core::Template::Text::Convert<char>::ToString(SymbolCodeLengths[i].CodeLength);

				Logger::WriteMessage("CodeLengths: ");
				Logger::WriteMessage(PrintableSymbol);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&CodeLength[0]);
				Logger::WriteMessage("\r\n");
			}
			Logger::WriteMessage("-------------------\r\n");
		}

		void PrintCodes(BinaryHuffmanTree::SymbolCodeMap& Codes)
		{
			for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Template::System::byte, Elysium::Core::Template::Text::String<char>>::FIterator Iterator = Codes.GetBegin();
				Iterator != Codes.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte, Elysium::Core::Template::Text::String<char>>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte, Elysium::Core::Template::Text::String<char>>& Item = Node->GetItem();

				const char Symbol = Item.GetKey();
				char PrintableSymbol[2] = { Symbol, 0x00 };

				const Elysium::Core::Template::Text::String<char>& Code = Item.GetValue();

				Logger::WriteMessage("Code: ");
				Logger::WriteMessage(PrintableSymbol);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&Code[0]);
				Logger::WriteMessage("\r\n");
			}
			Logger::WriteMessage("-------------------\r\n");
		}
	private:
		inline static constexpr const char* _LoremIpsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";
	};
}
