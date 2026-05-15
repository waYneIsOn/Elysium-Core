#include "CppUnitTest.h"

#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/CharacterTraits.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Compression/HuffmanCoding/HuffmanTree.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/Convert.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::IO::Compression::HuffmanCoding;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO::Compression::HuffmanCoding
{
	TEST_CLASS(HuffmanCodingTests)
	{
	public:
		TEST_METHOD(EncodeAndDecodeString)
		{
			const Elysium::Core::Template::System::byte* Input = reinterpret_cast<const Elysium::Core::Template::System::byte*>(_LoremIpsum);
			const Elysium::Core::Template::System::size InputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(_LoremIpsum);

			HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::uint32_t> Tree =
				HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::uint32_t>::Build(Input, InputLength);
			PrintTree(Tree._Root);
			Logger::WriteMessage("-------------------\r\n");
			
			HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::uint32_t>::CodeMap Codes =
				Tree.GenerateCodes();
			for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Template::System::byte, Elysium::Core::Template::Text::String<char8_t>>::FIterator Iterator = Codes.GetBegin();
				Iterator != Codes.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte, Elysium::Core::Template::Text::String<char8_t>>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte, Elysium::Core::Template::Text::String<char8_t>>& Item = Node->GetItem();

				const char Symbol = Item.GetKey();
				char PrintableSymbol[2] = { Symbol, 0x00 };

				const Elysium::Core::Template::Text::String<char8_t>& Code = Item.GetValue();

				Logger::WriteMessage("Code: ");
				Logger::WriteMessage(PrintableSymbol);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((const char*)&Code[0]);
				Logger::WriteMessage("\r\n");
			}
		}
	private:
		void PrintTree(const HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::uint32_t>::Node* CurrentNode)
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
	private:
		inline static constexpr const char* _LoremIpsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";
	};
}
