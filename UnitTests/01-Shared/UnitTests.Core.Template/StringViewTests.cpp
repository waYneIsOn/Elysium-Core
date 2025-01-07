#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/StringView.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text
{
	TEST_CLASS(StringViewTests)
	{
	public:
		TEST_METHOD(Constexpr)
		{
			constexpr const Elysium::Core::Template::Text::StringView<char> SmallView = "small";
			constexpr const Elysium::Core::Template::Text::StringView<char8_t> SmallUtf8View = u8"small";
			constexpr const Elysium::Core::Template::Text::StringView<wchar_t> SmallWideView = L"small";
			constexpr const Elysium::Core::Template::Text::StringView<char16_t> SmallUt168View = u"small";
			constexpr const Elysium::Core::Template::Text::StringView<char32_t> SmallUtf32View = U"small";
		}

		TEST_METHOD(Literals)
		{
			constexpr const Elysium::Core::Template::Text::StringView<char> SmallView = "small"_sv;
			constexpr const Elysium::Core::Template::Text::StringView<char8_t> SmallUtf8View = u8"small"_sv;
			constexpr const Elysium::Core::Template::Text::StringView<wchar_t> SmallWideView = L"small"_sv;
			constexpr const Elysium::Core::Template::Text::StringView<char16_t> SmallUt168View = u"small"_sv;
			constexpr const Elysium::Core::Template::Text::StringView<char32_t> SmallUtf32View = U"small"_sv;
		}
	};
}
