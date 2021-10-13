#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/String.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text
{
	TEST_CLASS(StringTests)
	{
	public:
		TEST_METHOD(Bla)
		{
			Elysium::Core::Template::Text::String CharArray = "";
			Elysium::Core::Template::Text::WideString WCharArray = L"";
			Elysium::Core::Template::Text::Utf8String Utf8CharArray = u8"";
			Elysium::Core::Template::Text::Utf16String Utf16CharArray = u"";
			Elysium::Core::Template::Text::Utf32String Utf32CharArray = U"";
		}
	};
}
