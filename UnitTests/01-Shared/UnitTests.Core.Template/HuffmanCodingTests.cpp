#include "CppUnitTest.h"

#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/CharacterTraits.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/HuffmanTree.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"

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

			Assert::Fail();
		}
	private:
		inline static constexpr const char* _LoremIpsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";
	};
}
