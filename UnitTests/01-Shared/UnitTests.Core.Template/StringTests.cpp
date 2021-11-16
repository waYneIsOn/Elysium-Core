#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/String.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text
{
	TEST_CLASS(StringTests)
	{
	public:
		TEST_METHOD(SizesAndCapacities)
		{
			// sizes
			constexpr const Elysium::Core::size StringSize = sizeof(Elysium::Core::Template::Text::String);
			constexpr const Elysium::Core::size WideStringSize = sizeof(Elysium::Core::Template::Text::WideString);
			constexpr const Elysium::Core::size Utf8StringSize = sizeof(Elysium::Core::Template::Text::Utf8String);
			constexpr const Elysium::Core::size Utf16StringSize = sizeof(Elysium::Core::Template::Text::Utf16String);
			constexpr const Elysium::Core::size Utf32StringSize = sizeof(Elysium::Core::Template::Text::Utf32String);

			Assert::AreEqual(24_ui64, StringSize);
			Assert::AreEqual(24_ui64, WideStringSize);
			Assert::AreEqual(24_ui64, Utf8StringSize);
			Assert::AreEqual(24_ui64, Utf16StringSize);
			Assert::AreEqual(24_ui64, Utf32StringSize);

			// empty strings
			Elysium::Core::Template::Text::String EmptyCharArray = Elysium::Core::Template::Text::String();
			Elysium::Core::Template::Text::WideString EmptyWideCharArray = Elysium::Core::Template::Text::WideString();
			Elysium::Core::Template::Text::Utf8String EmptyUtf8CharArray = Elysium::Core::Template::Text::Utf8String();
			Elysium::Core::Template::Text::Utf16String EmptyUtf16CharArray = Elysium::Core::Template::Text::Utf16String();
			Elysium::Core::Template::Text::Utf32String EmptyUtf32CharArray = Elysium::Core::Template::Text::Utf32String();

			Assert::AreEqual(0_ui64, EmptyCharArray.GetSize());
			Assert::AreEqual(0_ui64, EmptyWideCharArray.GetSize());
			Assert::AreEqual(0_ui64, EmptyUtf8CharArray.GetSize());
			Assert::AreEqual(0_ui64, EmptyUtf16CharArray.GetSize());
			Assert::AreEqual(0_ui64, EmptyUtf32CharArray.GetSize());

			Assert::AreEqual(23_ui64, EmptyCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, EmptyWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, EmptyUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, EmptyUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, EmptyUtf32CharArray.GetCapacity());

			// null strings
			Elysium::Core::Template::Text::String NullCharArray = Elysium::Core::Template::Text::String(nullptr);
			Elysium::Core::Template::Text::WideString NullWideCharArray = Elysium::Core::Template::Text::WideString(nullptr);
			Elysium::Core::Template::Text::Utf8String NullUtf8CharArray = Elysium::Core::Template::Text::Utf8String(nullptr);
			Elysium::Core::Template::Text::Utf16String NullUtf16CharArray = Elysium::Core::Template::Text::Utf16String(nullptr);
			Elysium::Core::Template::Text::Utf32String NullUtf32CharArray = Elysium::Core::Template::Text::Utf32String(nullptr);

			Assert::AreEqual(0_ui64, NullCharArray.GetSize());
			Assert::AreEqual(0_ui64, NullWideCharArray.GetSize());
			Assert::AreEqual(0_ui64, NullUtf8CharArray.GetSize());
			Assert::AreEqual(0_ui64, NullUtf16CharArray.GetSize());
			Assert::AreEqual(0_ui64, NullUtf32CharArray.GetSize());

			Assert::AreEqual(23_ui64, NullCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, NullWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, NullUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, NullUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, NullUtf32CharArray.GetCapacity());
			
			// stack strings with maximum size
			Elysium::Core::Template::Text::String MaxStackCharArray = Elysium::Core::Template::Text::String("12345678911131517192123");
			Elysium::Core::Template::Text::WideString MaxStackWideCharArray = Elysium::Core::Template::Text::WideString(L"12345678911");
			Elysium::Core::Template::Text::Utf8String MaxStackUtf8CharArray = Elysium::Core::Template::Text::Utf8String(u8"12345678911131517192123");
			Elysium::Core::Template::Text::Utf16String MaxStackUtf16CharArray = Elysium::Core::Template::Text::Utf16String(u"12345678911");
			Elysium::Core::Template::Text::Utf32String MaxStackUtf32CharArray = Elysium::Core::Template::Text::Utf32String(U"12345");

			Assert::AreEqual(23_ui64, MaxStackCharArray.GetSize());
			Assert::AreEqual(11_ui64, MaxStackWideCharArray.GetSize());
			Assert::AreEqual(23_ui64, MaxStackUtf8CharArray.GetSize());
			Assert::AreEqual(11_ui64, MaxStackUtf16CharArray.GetSize());
			Assert::AreEqual(5_ui64, MaxStackUtf32CharArray.GetSize());

			Assert::AreEqual(23_ui64, MaxStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, MaxStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, MaxStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, MaxStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, MaxStackUtf32CharArray.GetCapacity());

			// stack strings
			Elysium::Core::Template::Text::String StackCharArray = Elysium::Core::Template::Text::String("xyz");
			Elysium::Core::Template::Text::WideString StackWCharArray = Elysium::Core::Template::Text::WideString(L"xyz");
			Elysium::Core::Template::Text::Utf8String StackUtf8CharArray = Elysium::Core::Template::Text::Utf8String(u8"xyz");
			Elysium::Core::Template::Text::Utf16String StackUtf16CharArray = Elysium::Core::Template::Text::Utf16String(u"xyz");
			Elysium::Core::Template::Text::Utf32String StackUtf32CharArray = Elysium::Core::Template::Text::Utf32String(U"xyz");

			Assert::AreEqual(3_ui64, StackCharArray.GetSize());
			Assert::AreEqual(3_ui64, StackWCharArray.GetSize());
			Assert::AreEqual(3_ui64, StackUtf8CharArray.GetSize());
			Assert::AreEqual(3_ui64, StackUtf16CharArray.GetSize());
			Assert::AreEqual(3_ui64, StackUtf32CharArray.GetSize());

			Assert::AreEqual(23_ui64, StackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackWCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, StackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, StackUtf32CharArray.GetCapacity());
			
			// heap strings
			Elysium::Core::Template::Text::String HeapCharArray = Elysium::Core::Template::Text::String("this string is too large to fit onto stack");
			Elysium::Core::Template::Text::WideString HeapWideCharArray = Elysium::Core::Template::Text::WideString(L"this string is too large to fit onto stack");
			Elysium::Core::Template::Text::Utf8String HeapUtf8CharArray = Elysium::Core::Template::Text::Utf8String(u8"this string is too large to fit onto stack");
			Elysium::Core::Template::Text::Utf16String HeapUtf16CharArray = Elysium::Core::Template::Text::Utf16String(u"this string is too large to fit onto stack");
			Elysium::Core::Template::Text::Utf32String HeapUtf32CharArray = Elysium::Core::Template::Text::Utf32String(U"this string is too large to fit onto stack");

			Assert::AreEqual(42_ui64, HeapCharArray.GetSize());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetSize());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetSize());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetSize());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetSize());
			
			Assert::AreEqual(42_ui64, HeapCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetCapacity());
		}
	};
}
