#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/String.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text
{
	TEST_CLASS(StringTests)
	{
	public:
		TEST_METHOD(SizesAndCapacities)
		{
			// sizes
			constexpr const Elysium::Core::size StringSize = sizeof(Elysium::Core::String);
			constexpr const Elysium::Core::size WideStringSize = sizeof(Elysium::Core::WideString);
			constexpr const Elysium::Core::size Utf8StringSize = sizeof(Elysium::Core::Utf8String);
			constexpr const Elysium::Core::size Utf16StringSize = sizeof(Elysium::Core::Utf16String);
			constexpr const Elysium::Core::size Utf32StringSize = sizeof(Elysium::Core::Utf32String);

			Assert::AreEqual(24_ui64, StringSize);
			Assert::AreEqual(24_ui64, WideStringSize);
			Assert::AreEqual(24_ui64, Utf8StringSize);
			Assert::AreEqual(24_ui64, Utf16StringSize);
			Assert::AreEqual(24_ui64, Utf32StringSize);

			Assert::AreEqual(23_ui8, Elysium::Core::String::MaximumSizeOnStack);
			Assert::AreEqual(23_ui8, Elysium::Core::WideString::MaximumSizeOnStack);
			Assert::AreEqual(23_ui8, Elysium::Core::Utf8String::MaximumSizeOnStack);
			Assert::AreEqual(23_ui8, Elysium::Core::Utf16String::MaximumSizeOnStack);
			Assert::AreEqual(23_ui8, Elysium::Core::Utf32String::MaximumSizeOnStack);

			Assert::AreEqual(23_ui8, Elysium::Core::String::MaximumLengthOnStack);
			Assert::AreEqual(11_ui8, Elysium::Core::WideString::MaximumLengthOnStack);
			Assert::AreEqual(23_ui8, Elysium::Core::Utf8String::MaximumLengthOnStack);
			Assert::AreEqual(11_ui8, Elysium::Core::Utf16String::MaximumLengthOnStack);
			Assert::AreEqual(5_ui8, Elysium::Core::Utf32String::MaximumLengthOnStack);

			Assert::AreEqual(9223372036854775807_ui64, Elysium::Core::String::MaximumSizeOnHeap);
			Assert::AreEqual(9223372036854775807_ui64, Elysium::Core::WideString::MaximumSizeOnHeap);
			Assert::AreEqual(9223372036854775807_ui64, Elysium::Core::Utf8String::MaximumSizeOnHeap);
			Assert::AreEqual(9223372036854775807_ui64, Elysium::Core::Utf16String::MaximumSizeOnHeap);
			Assert::AreEqual(9223372036854775807_ui64, Elysium::Core::Utf32String::MaximumSizeOnHeap);

			Assert::AreEqual(9223372036854775807_ui64, Elysium::Core::String::MaximumLengthOnHeap);
			Assert::AreEqual(4611686018427387903_ui64, Elysium::Core::WideString::MaximumLengthOnHeap);
			Assert::AreEqual(9223372036854775807_ui64, Elysium::Core::Utf8String::MaximumLengthOnHeap);
			Assert::AreEqual(4611686018427387903_ui64, Elysium::Core::Utf16String::MaximumLengthOnHeap);
			Assert::AreEqual(2305843009213693951_ui64, Elysium::Core::Utf32String::MaximumLengthOnHeap);
			
			// empty strings
			Elysium::Core::String EmptyCharArray = Elysium::Core::String();
			Elysium::Core::WideString EmptyWideCharArray = Elysium::Core::WideString();
			Elysium::Core::Utf8String EmptyUtf8CharArray = Elysium::Core::Utf8String();
			Elysium::Core::Utf16String EmptyUtf16CharArray = Elysium::Core::Utf16String();
			Elysium::Core::Utf32String EmptyUtf32CharArray = Elysium::Core::Utf32String();

			Assert::AreEqual(0_ui64, EmptyCharArray.GetLength());
			Assert::AreEqual(0_ui64, EmptyWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, EmptyUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, EmptyUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, EmptyUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, EmptyCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, EmptyWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, EmptyUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, EmptyUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, EmptyUtf32CharArray.GetCapacity());

			// null strings
			Elysium::Core::String NullCharArray = Elysium::Core::String(nullptr);
			Elysium::Core::WideString NullWideCharArray = Elysium::Core::WideString(nullptr);
			Elysium::Core::Utf8String NullUtf8CharArray = Elysium::Core::Utf8String(nullptr);
			Elysium::Core::Utf16String NullUtf16CharArray = Elysium::Core::Utf16String(nullptr);
			Elysium::Core::Utf32String NullUtf32CharArray = Elysium::Core::Utf32String(nullptr);

			Assert::AreEqual(0_ui64, NullCharArray.GetLength());
			Assert::AreEqual(0_ui64, NullWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, NullUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, NullUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, NullUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, NullCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, NullWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, NullUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, NullUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, NullUtf32CharArray.GetCapacity());
			
			// stack strings with maximum size
			Elysium::Core::String MaxStackCharArray = Elysium::Core::String("12345678911131517192123");
			Elysium::Core::WideString MaxStackWideCharArray = Elysium::Core::WideString(L"12345678911");
			Elysium::Core::Utf8String MaxStackUtf8CharArray = Elysium::Core::Utf8String(u8"12345678911131517192123");
			Elysium::Core::Utf16String MaxStackUtf16CharArray = Elysium::Core::Utf16String(u"12345678911");
			Elysium::Core::Utf32String MaxStackUtf32CharArray = Elysium::Core::Utf32String(U"12345");

			Assert::AreEqual(23_ui64, MaxStackCharArray.GetLength());
			Assert::AreEqual(11_ui64, MaxStackWideCharArray.GetLength());
			Assert::AreEqual(23_ui64, MaxStackUtf8CharArray.GetLength());
			Assert::AreEqual(11_ui64, MaxStackUtf16CharArray.GetLength());
			Assert::AreEqual(5_ui64, MaxStackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, MaxStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, MaxStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, MaxStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, MaxStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, MaxStackUtf32CharArray.GetCapacity());

			// stack strings
			Elysium::Core::String StackCharArray = Elysium::Core::String("xyz");
			Elysium::Core::WideString StackWideCharArray = Elysium::Core::WideString(L"xyz");
			Elysium::Core::Utf8String StackUtf8CharArray = Elysium::Core::Utf8String(u8"xyz");
			Elysium::Core::Utf16String StackUtf16CharArray = Elysium::Core::Utf16String(u"xyz");
			Elysium::Core::Utf32String StackUtf32CharArray = Elysium::Core::Utf32String(U"xyz");

			Assert::AreEqual(3_ui64, StackCharArray.GetLength());
			Assert::AreEqual(3_ui64, StackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, StackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, StackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, StackUtf32CharArray.GetCapacity());
			
			// heap strings
			Elysium::Core::String HeapCharArray = Elysium::Core::String("this string is too large to fit onto stack");
			Elysium::Core::WideString HeapWideCharArray = Elysium::Core::WideString(L"this string is too large to fit onto stack");
			Elysium::Core::Utf8String HeapUtf8CharArray = Elysium::Core::Utf8String(u8"this string is too large to fit onto stack");
			Elysium::Core::Utf16String HeapUtf16CharArray = Elysium::Core::Utf16String(u"this string is too large to fit onto stack");
			Elysium::Core::Utf32String HeapUtf32CharArray = Elysium::Core::Utf32String(U"this string is too large to fit onto stack");

			Assert::AreEqual(42_ui64, HeapCharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetLength());
			
			Assert::AreEqual(42_ui64, HeapCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetCapacity());

			// "length" stack strings
			Elysium::Core::String StackSizeCharArray = Elysium::Core::String(1);
			Elysium::Core::WideString StackSizeWideCharArray = Elysium::Core::WideString(1);
			Elysium::Core::Utf8String StackSizeUtf8CharArray = Elysium::Core::Utf8String(1);
			Elysium::Core::Utf16String StackSizeUtf16CharArray = Elysium::Core::Utf16String(1);
			Elysium::Core::Utf32String StackSizeUtf32CharArray = Elysium::Core::Utf32String(1);

			Assert::AreEqual(0_ui64, StackSizeCharArray.GetLength());
			Assert::AreEqual(0_ui64, StackSizeWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, StackSizeUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, StackSizeUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, StackSizeUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, StackSizeCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackSizeWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, StackSizeUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackSizeUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, StackSizeUtf32CharArray.GetCapacity());

			// "length" heap strings
			Elysium::Core::String HeapSizeCharArray = Elysium::Core::String(127);
			Elysium::Core::WideString HeapSizeWideCharArray = Elysium::Core::WideString(127);
			Elysium::Core::Utf8String HeapSizeUtf8CharArray = Elysium::Core::Utf8String(127);
			Elysium::Core::Utf16String HeapSizeUtf16CharArray = Elysium::Core::Utf16String(127);
			Elysium::Core::Utf32String HeapSizeUtf32CharArray = Elysium::Core::Utf32String(127);

			Assert::AreEqual(0_ui64, HeapSizeCharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapSizeWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapSizeUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapSizeUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapSizeUtf32CharArray.GetLength());

			Assert::AreEqual(127_ui64, HeapSizeCharArray.GetCapacity());
			Assert::AreEqual(127_ui64, HeapSizeWideCharArray.GetCapacity());
			Assert::AreEqual(127_ui64, HeapSizeUtf8CharArray.GetCapacity());
			Assert::AreEqual(127_ui64, HeapSizeUtf16CharArray.GetCapacity());
			Assert::AreEqual(127_ui64, HeapSizeUtf32CharArray.GetCapacity());
		}

		TEST_METHOD(CharMoves)
		{
			// stack strings
			Elysium::Core::String TargetStackCharArray = "xyz";
			Elysium::Core::WideString TargetStackWideCharArray = L"xyz";
			Elysium::Core::Utf8String TargetStackUtf8CharArray = u8"xyz";
			Elysium::Core::Utf16String TargetStackUtf16CharArray = u"xyz";
			Elysium::Core::Utf32String TargetStackUtf32CharArray = U"xyz";

			Assert::AreEqual(3_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, TargetStackUtf32CharArray.GetCapacity());

			// heap strings
			Elysium::Core::String TargetHeapCharArray = "this string is too large to fit onto stack";
			Elysium::Core::WideString TargetHeapWideCharArray = L"this string is too large to fit onto stack";
			Elysium::Core::Utf8String TargetHeapUtf8CharArray = u8"this string is too large to fit onto stack";
			Elysium::Core::Utf16String TargetHeapUtf16CharArray = u"this string is too large to fit onto stack";
			Elysium::Core::Utf32String TargetHeapUtf32CharArray = U"this string is too large to fit onto stack";

			Assert::AreEqual(42_ui64, TargetHeapCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, TargetHeapCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetHeapWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetHeapUtf32CharArray.GetCapacity());
			
			// copy stack sized chars to stack string using copy-operator
			TargetStackCharArray = "12";
			TargetStackWideCharArray = L"12";
			TargetStackUtf8CharArray = u8"12";
			TargetStackUtf16CharArray = u"12";
			TargetStackUtf32CharArray = U"12";
			
			Assert::AreEqual(2_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(2_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(2_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(2_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(2_ui64, TargetStackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, TargetStackUtf32CharArray.GetCapacity());

			// copy larger heap sized chars to heap string using copy-operator
			TargetHeapCharArray = "this string is too large to fit onto stack and is larger";
			TargetHeapWideCharArray = L"this string is too large to fit onto stack and is larger";
			TargetHeapUtf8CharArray = u8"this string is too large to fit onto stack and is larger";
			TargetHeapUtf16CharArray = u"this string is too large to fit onto stack and is larger";
			TargetHeapUtf32CharArray = U"this string is too large to fit onto stack and is larger";

			Assert::AreEqual(56_ui64, TargetHeapCharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetHeapWideCharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetHeapUtf8CharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetHeapUtf16CharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetHeapUtf32CharArray.GetLength());

			Assert::AreEqual(56_ui64, TargetHeapCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapWideCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf32CharArray.GetCapacity());

			// copy smaller heap sized chars to heap string using copy-operator
			TargetHeapCharArray = "this string is too large to fit onto stack";
			TargetHeapWideCharArray = L"this string is too large to fit onto stack";
			TargetHeapUtf8CharArray = u8"this string is too large to fit onto stack";
			TargetHeapUtf16CharArray = u"this string is too large to fit onto stack";
			TargetHeapUtf32CharArray = U"this string is too large to fit onto stack";

			Assert::AreEqual(42_ui64, TargetHeapCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetHeapUtf32CharArray.GetLength());

			Assert::AreEqual(56_ui64, TargetHeapCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapWideCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf32CharArray.GetCapacity());

			// copy stack sized chars to heap string using copy-operator
			TargetHeapCharArray = "xyz";
			TargetHeapWideCharArray = L"xyz";
			TargetHeapUtf8CharArray = u8"xyz";
			TargetHeapUtf16CharArray = u"xyz";
			TargetHeapUtf32CharArray = U"xyz";

			Assert::AreEqual(3_ui64, TargetHeapCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetHeapWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetHeapUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetHeapUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetHeapUtf32CharArray.GetLength());

			Assert::AreEqual(56_ui64, TargetHeapCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapWideCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetHeapUtf32CharArray.GetCapacity());
			
			// copy heap sized chars to stack string using copy-operator
			TargetStackCharArray = "this string is too large to fit onto stack";
			TargetStackWideCharArray = L"this string is too large to fit onto stack";
			TargetStackUtf8CharArray = u8"this string is too large to fit onto stack";
			TargetStackUtf16CharArray = u"this string is too large to fit onto stack";
			TargetStackUtf32CharArray = U"this string is too large to fit onto stack";

			Assert::AreEqual(42_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackUtf32CharArray.GetCapacity());
		}

		TEST_METHOD(StringCopies)
		{
			// stack strings
			Elysium::Core::String SourceStackCharArray = Elysium::Core::String("xyz");
			Elysium::Core::WideString SourceStackWideCharArray = Elysium::Core::WideString(L"xyz");
			Elysium::Core::Utf8String SourceStackUtf8CharArray = Elysium::Core::Utf8String(u8"xyz");
			Elysium::Core::Utf16String SourceStackUtf16CharArray = Elysium::Core::Utf16String(u"xyz");
			Elysium::Core::Utf32String SourceStackUtf32CharArray = Elysium::Core::Utf32String(U"xyz");

			Assert::AreEqual(3_ui64, SourceStackCharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, SourceStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, SourceStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, SourceStackUtf32CharArray.GetCapacity());

			// heap strings
			Elysium::Core::String SourceHeapCharArray = Elysium::Core::String("this string is too large to fit onto stack");
			Elysium::Core::WideString SourceHeapWideCharArray = Elysium::Core::WideString(L"this string is too large to fit onto stack");
			Elysium::Core::Utf8String SourceHeapUtf8CharArray = Elysium::Core::Utf8String(u8"this string is too large to fit onto stack");
			Elysium::Core::Utf16String SourceHeapUtf16CharArray = Elysium::Core::Utf16String(u"this string is too large to fit onto stack");
			Elysium::Core::Utf32String SourceHeapUtf32CharArray = Elysium::Core::Utf32String(U"this string is too large to fit onto stack");

			Assert::AreEqual(42_ui64, SourceHeapCharArray.GetLength());
			Assert::AreEqual(42_ui64, SourceHeapWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, SourceHeapUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, SourceHeapUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, SourceHeapUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, SourceHeapCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, SourceHeapWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, SourceHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, SourceHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, SourceHeapUtf32CharArray.GetCapacity());
			
			// copy stack string using copy-constructor
			Elysium::Core::String StackCharArray = Elysium::Core::String(SourceStackCharArray);
			Elysium::Core::WideString StackWideCharArray = Elysium::Core::WideString(SourceStackWideCharArray);
			Elysium::Core::Utf8String StackUtf8CharArray = Elysium::Core::Utf8String(SourceStackUtf8CharArray);
			Elysium::Core::Utf16String StackUtf16CharArray = Elysium::Core::Utf16String(SourceStackUtf16CharArray);
			Elysium::Core::Utf32String StackUtf32CharArray = Elysium::Core::Utf32String(SourceStackUtf32CharArray);

			Assert::AreEqual(3_ui64, StackCharArray.GetLength());
			Assert::AreEqual(3_ui64, StackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, StackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, StackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, StackUtf32CharArray.GetCapacity());

			// copy heap string using copy-constructor
			Elysium::Core::String HeapCharArray = Elysium::Core::String(SourceHeapCharArray);
			Elysium::Core::WideString HeapWideCharArray = Elysium::Core::WideString(SourceHeapWideCharArray);
			Elysium::Core::Utf8String HeapUtf8CharArray = Elysium::Core::Utf8String(SourceHeapUtf8CharArray);
			Elysium::Core::Utf16String HeapUtf16CharArray = Elysium::Core::Utf16String(SourceHeapUtf16CharArray);
			Elysium::Core::Utf32String HeapUtf32CharArray = Elysium::Core::Utf32String(SourceHeapUtf32CharArray);

			Assert::AreEqual(42_ui64, HeapCharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, HeapCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetCapacity());

			// copy stack string to stack string using copy-operator
			Elysium::Core::String TargetStackCharArray = Elysium::Core::String("1234");
			Elysium::Core::WideString TargetStackWideCharArray = Elysium::Core::WideString(L"1234");
			Elysium::Core::Utf8String TargetStackUtf8CharArray = Elysium::Core::Utf8String(u8"1234");
			Elysium::Core::Utf16String TargetStackUtf16CharArray = Elysium::Core::Utf16String(u"1234");
			Elysium::Core::Utf32String TargetStackUtf32CharArray = Elysium::Core::Utf32String(U"1234");

			TargetStackCharArray = SourceStackCharArray;
			TargetStackWideCharArray = SourceStackWideCharArray;
			TargetStackUtf8CharArray = SourceStackUtf8CharArray;
			TargetStackUtf16CharArray = SourceStackUtf16CharArray;
			TargetStackUtf32CharArray = SourceStackUtf32CharArray;

			Assert::AreEqual(3_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf32CharArray.GetLength());
			
			Assert::AreEqual(23_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, TargetStackUtf32CharArray.GetCapacity());
			
			// copy heap string to stack string using copy-operator
			TargetStackCharArray = HeapCharArray;
			TargetStackWideCharArray = HeapWideCharArray;
			TargetStackUtf8CharArray = HeapUtf8CharArray;
			TargetStackUtf16CharArray = HeapUtf16CharArray;
			TargetStackUtf32CharArray = HeapUtf32CharArray;
			
			Assert::AreEqual(42_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, TargetStackUtf32CharArray.GetCapacity());

			// copy larger heap string to heap string using copy-operator
			Elysium::Core::String LargerSourceHeapCharArray = Elysium::Core::String("this string is too large to fit onto stack and is larger");
			Elysium::Core::WideString LargerSourceHeapWideCharArray = Elysium::Core::WideString(L"this string is too large to fit onto stack and is larger");
			Elysium::Core::Utf8String LargerSourceHeapUtf8CharArray = Elysium::Core::Utf8String(u8"this string is too large to fit onto stack and is larger");
			Elysium::Core::Utf16String LargerSourceHeapUtf16CharArray = Elysium::Core::Utf16String(u"this string is too large to fit onto stack and is larger");
			Elysium::Core::Utf32String LargerSourceHeapUtf32CharArray = Elysium::Core::Utf32String(U"this string is too large to fit onto stack and is larger");

			TargetStackCharArray = LargerSourceHeapCharArray;
			TargetStackWideCharArray = LargerSourceHeapWideCharArray;
			TargetStackUtf8CharArray = LargerSourceHeapUtf8CharArray;
			TargetStackUtf16CharArray = LargerSourceHeapUtf16CharArray;
			TargetStackUtf32CharArray = LargerSourceHeapUtf32CharArray;

			Assert::AreEqual(56_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(56_ui64, TargetStackUtf32CharArray.GetLength());

			Assert::AreEqual(56_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf32CharArray.GetCapacity());

			// copy smaller heap string to heap string using copy-operator
			TargetStackCharArray = SourceHeapCharArray;
			TargetStackWideCharArray = SourceHeapWideCharArray;
			TargetStackUtf8CharArray = SourceHeapUtf8CharArray;
			TargetStackUtf16CharArray = SourceHeapUtf16CharArray;
			TargetStackUtf32CharArray = SourceHeapUtf32CharArray;

			Assert::AreEqual(42_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, TargetStackUtf32CharArray.GetLength());

			Assert::AreEqual(56_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf32CharArray.GetCapacity());

			// copy stack string to heap string using copy-operator
			TargetStackCharArray = SourceStackCharArray;
			TargetStackWideCharArray = SourceStackWideCharArray;
			TargetStackUtf8CharArray = SourceStackUtf8CharArray;
			TargetStackUtf16CharArray = SourceStackUtf16CharArray;
			TargetStackUtf32CharArray = SourceStackUtf32CharArray;

			Assert::AreEqual(3_ui64, TargetStackCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, TargetStackUtf32CharArray.GetLength());
			
			Assert::AreEqual(56_ui64, TargetStackCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackWideCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, TargetStackUtf32CharArray.GetCapacity());
		}

		TEST_METHOD(StringMoves)
		{
			// stack strings
			Elysium::Core::String SourceStackCharArray = Elysium::Core::String("xyz");
			Elysium::Core::WideString SourceStackWideCharArray = Elysium::Core::WideString(L"xyz");
			Elysium::Core::Utf8String SourceStackUtf8CharArray = Elysium::Core::Utf8String(u8"xyz");
			Elysium::Core::Utf16String SourceStackUtf16CharArray = Elysium::Core::Utf16String(u"xyz");
			Elysium::Core::Utf32String SourceStackUtf32CharArray = Elysium::Core::Utf32String(U"xyz");

			// heap strings
			Elysium::Core::String SourceHeapCharArray = Elysium::Core::String("this string is too large to fit onto stack");
			Elysium::Core::WideString SourceHeapWideCharArray = Elysium::Core::WideString(L"this string is too large to fit onto stack");
			Elysium::Core::Utf8String SourceHeapUtf8CharArray = Elysium::Core::Utf8String(u8"this string is too large to fit onto stack");
			Elysium::Core::Utf16String SourceHeapUtf16CharArray = Elysium::Core::Utf16String(u"this string is too large to fit onto stack");
			Elysium::Core::Utf32String SourceHeapUtf32CharArray = Elysium::Core::Utf32String(U"this string is too large to fit onto stack");

			// move stack string using move-constructor
			Elysium::Core::String StackCharArray = Elysium::Core::String(Elysium::Core::Template::Functional::Move(SourceStackCharArray));
			Elysium::Core::WideString StackWideCharArray = Elysium::Core::WideString(Elysium::Core::Template::Functional::Move(SourceStackWideCharArray));
			Elysium::Core::Utf8String StackUtf8CharArray = Elysium::Core::Utf8String(Elysium::Core::Template::Functional::Move(SourceStackUtf8CharArray));
			Elysium::Core::Utf16String StackUtf16CharArray = Elysium::Core::Utf16String(Elysium::Core::Template::Functional::Move(SourceStackUtf16CharArray));
			Elysium::Core::Utf32String StackUtf32CharArray = Elysium::Core::Utf32String(Elysium::Core::Template::Functional::Move(SourceStackUtf32CharArray));

			Assert::AreEqual(3_ui64, StackCharArray.GetLength());
			Assert::AreEqual(3_ui64, StackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, StackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, StackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, StackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, StackUtf32CharArray.GetCapacity());

			Assert::AreEqual(0_ui64, SourceStackCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, SourceStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, SourceStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, SourceStackUtf32CharArray.GetCapacity());

			// move heap string using move-constructor
			Elysium::Core::String HeapCharArray = Elysium::Core::String(Elysium::Core::Template::Functional::Move(SourceHeapCharArray));
			Elysium::Core::WideString HeapWideCharArray = Elysium::Core::WideString(Elysium::Core::Template::Functional::Move(SourceHeapWideCharArray));
			Elysium::Core::Utf8String HeapUtf8CharArray = Elysium::Core::Utf8String(Elysium::Core::Template::Functional::Move(SourceHeapUtf8CharArray));
			Elysium::Core::Utf16String HeapUtf16CharArray = Elysium::Core::Utf16String(Elysium::Core::Template::Functional::Move(SourceHeapUtf16CharArray));
			Elysium::Core::Utf32String HeapUtf32CharArray = Elysium::Core::Utf32String(Elysium::Core::Template::Functional::Move(SourceHeapUtf32CharArray));

			Assert::AreEqual(42_ui64, HeapCharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, HeapCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, HeapUtf32CharArray.GetCapacity());

			Assert::AreEqual(0_ui64, SourceHeapCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, SourceHeapCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceHeapWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, SourceHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, SourceHeapUtf32CharArray.GetCapacity());

			// move stack string to stack string using move-operator
			SourceStackCharArray = Elysium::Core::Template::Functional::Move(StackCharArray);
			SourceStackWideCharArray = Elysium::Core::Template::Functional::Move(StackWideCharArray);
			SourceStackUtf8CharArray = Elysium::Core::Template::Functional::Move(StackUtf8CharArray);
			SourceStackUtf16CharArray = Elysium::Core::Template::Functional::Move(StackUtf16CharArray);
			SourceStackUtf32CharArray = Elysium::Core::Template::Functional::Move(StackUtf32CharArray);

			Assert::AreEqual(3_ui64, SourceStackCharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, SourceStackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, SourceStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, SourceStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, SourceStackUtf32CharArray.GetCapacity());

			Assert::AreEqual(0_ui64, StackCharArray.GetLength());
			Assert::AreEqual(0_ui64, StackWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, StackUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, StackUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, StackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, StackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, StackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, StackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, StackUtf32CharArray.GetCapacity());

			// move heap string to stack string using move-operator
			StackCharArray = Elysium::Core::Template::Functional::Move(HeapCharArray);
			StackWideCharArray = Elysium::Core::Template::Functional::Move(HeapWideCharArray);
			StackUtf8CharArray = Elysium::Core::Template::Functional::Move(HeapUtf8CharArray);
			StackUtf16CharArray = Elysium::Core::Template::Functional::Move(HeapUtf16CharArray);
			StackUtf32CharArray = Elysium::Core::Template::Functional::Move(HeapUtf32CharArray);

			Assert::AreEqual(42_ui64, StackCharArray.GetLength());
			Assert::AreEqual(42_ui64, StackWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, StackUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, StackUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, StackUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, StackCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, StackWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, StackUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, StackUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, StackUtf32CharArray.GetCapacity());

			Assert::AreEqual(0_ui64, HeapCharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, HeapUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, HeapCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, HeapWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, HeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, HeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, HeapUtf32CharArray.GetCapacity());

			// move larger heap string to heap string using move-operator
			Elysium::Core::String LargerSourceHeapCharArray = Elysium::Core::String("this string is too large to fit onto stack and is larger");
			Elysium::Core::WideString LargerSourceHeapWideCharArray = Elysium::Core::WideString(L"this string is too large to fit onto stack and is larger");
			Elysium::Core::Utf8String LargerSourceHeapUtf8CharArray = Elysium::Core::Utf8String(u8"this string is too large to fit onto stack and is larger");
			Elysium::Core::Utf16String LargerSourceHeapUtf16CharArray = Elysium::Core::Utf16String(u"this string is too large to fit onto stack and is larger");
			Elysium::Core::Utf32String LargerSourceHeapUtf32CharArray = Elysium::Core::Utf32String(U"this string is too large to fit onto stack and is larger");

			StackCharArray = Elysium::Core::Template::Functional::Move(LargerSourceHeapCharArray);
			StackWideCharArray = Elysium::Core::Template::Functional::Move(LargerSourceHeapWideCharArray);
			StackUtf8CharArray = Elysium::Core::Template::Functional::Move(LargerSourceHeapUtf8CharArray);
			StackUtf16CharArray = Elysium::Core::Template::Functional::Move(LargerSourceHeapUtf16CharArray);
			StackUtf32CharArray = Elysium::Core::Template::Functional::Move(LargerSourceHeapUtf32CharArray);

			Assert::AreEqual(56_ui64, StackCharArray.GetLength());
			Assert::AreEqual(56_ui64, StackWideCharArray.GetLength());
			Assert::AreEqual(56_ui64, StackUtf8CharArray.GetLength());
			Assert::AreEqual(56_ui64, StackUtf16CharArray.GetLength());
			Assert::AreEqual(56_ui64, StackUtf32CharArray.GetLength());

			Assert::AreEqual(56_ui64, StackCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, StackWideCharArray.GetCapacity());
			Assert::AreEqual(56_ui64, StackUtf8CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, StackUtf16CharArray.GetCapacity());
			Assert::AreEqual(56_ui64, StackUtf32CharArray.GetCapacity());

			Assert::AreEqual(0_ui64, LargerSourceHeapCharArray.GetLength());
			Assert::AreEqual(0_ui64, LargerSourceHeapWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, LargerSourceHeapUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, LargerSourceHeapUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, LargerSourceHeapUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, LargerSourceHeapCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, LargerSourceHeapWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, LargerSourceHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, LargerSourceHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, LargerSourceHeapUtf32CharArray.GetCapacity());
			
			// move smaller heap string to heap string using move-operator
			SourceHeapCharArray = Elysium::Core::String("this string is too large to fit onto stack");
			SourceHeapWideCharArray = Elysium::Core::WideString(L"this string is too large to fit onto stack");
			SourceHeapUtf8CharArray = Elysium::Core::Utf8String(u8"this string is too large to fit onto stack");
			SourceHeapUtf16CharArray = Elysium::Core::Utf16String(u"this string is too large to fit onto stack");
			SourceHeapUtf32CharArray = Elysium::Core::Utf32String(U"this string is too large to fit onto stack");

			LargerSourceHeapCharArray = Elysium::Core::Template::Functional::Move(SourceHeapCharArray);
			LargerSourceHeapWideCharArray = Elysium::Core::Template::Functional::Move(SourceHeapWideCharArray);
			LargerSourceHeapUtf8CharArray = Elysium::Core::Template::Functional::Move(SourceHeapUtf8CharArray);
			LargerSourceHeapUtf16CharArray = Elysium::Core::Template::Functional::Move(SourceHeapUtf16CharArray);
			LargerSourceHeapUtf32CharArray = Elysium::Core::Template::Functional::Move(SourceHeapUtf32CharArray);

			Assert::AreEqual(42_ui64, LargerSourceHeapCharArray.GetLength());
			Assert::AreEqual(42_ui64, LargerSourceHeapWideCharArray.GetLength());
			Assert::AreEqual(42_ui64, LargerSourceHeapUtf8CharArray.GetLength());
			Assert::AreEqual(42_ui64, LargerSourceHeapUtf16CharArray.GetLength());
			Assert::AreEqual(42_ui64, LargerSourceHeapUtf32CharArray.GetLength());

			Assert::AreEqual(42_ui64, LargerSourceHeapCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, LargerSourceHeapWideCharArray.GetCapacity());
			Assert::AreEqual(42_ui64, LargerSourceHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, LargerSourceHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(42_ui64, LargerSourceHeapUtf32CharArray.GetCapacity());

			Assert::AreEqual(0_ui64, SourceHeapCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceHeapUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, SourceHeapCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceHeapWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, SourceHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, SourceHeapUtf32CharArray.GetCapacity());
			
			// move stack string to heap string using move-operator
			SourceStackCharArray = Elysium::Core::String("xyz");
			SourceStackWideCharArray = Elysium::Core::WideString(L"xyz");
			SourceStackUtf8CharArray = Elysium::Core::Utf8String(u8"xyz");
			SourceStackUtf16CharArray = Elysium::Core::Utf16String(u"xyz");
			SourceStackUtf32CharArray = Elysium::Core::Utf32String(U"xyz");

			LargerSourceHeapCharArray = Elysium::Core::Template::Functional::Move(SourceStackCharArray);
			LargerSourceHeapWideCharArray = Elysium::Core::Template::Functional::Move(SourceStackWideCharArray);
			LargerSourceHeapUtf8CharArray = Elysium::Core::Template::Functional::Move(SourceStackUtf8CharArray);
			LargerSourceHeapUtf16CharArray = Elysium::Core::Template::Functional::Move(SourceStackUtf16CharArray);
			LargerSourceHeapUtf32CharArray = Elysium::Core::Template::Functional::Move(SourceStackUtf32CharArray);

			Assert::AreEqual(3_ui64, LargerSourceHeapCharArray.GetLength());
			Assert::AreEqual(3_ui64, LargerSourceHeapWideCharArray.GetLength());
			Assert::AreEqual(3_ui64, LargerSourceHeapUtf8CharArray.GetLength());
			Assert::AreEqual(3_ui64, LargerSourceHeapUtf16CharArray.GetLength());
			Assert::AreEqual(3_ui64, LargerSourceHeapUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, LargerSourceHeapCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, LargerSourceHeapWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, LargerSourceHeapUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, LargerSourceHeapUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, LargerSourceHeapUtf32CharArray.GetCapacity());

			Assert::AreEqual(0_ui64, SourceStackCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackWideCharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackUtf8CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackUtf16CharArray.GetLength());
			Assert::AreEqual(0_ui64, SourceStackUtf32CharArray.GetLength());

			Assert::AreEqual(23_ui64, SourceStackCharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackWideCharArray.GetCapacity());
			Assert::AreEqual(23_ui64, SourceStackUtf8CharArray.GetCapacity());
			Assert::AreEqual(11_ui64, SourceStackUtf16CharArray.GetCapacity());
			Assert::AreEqual(5_ui64, SourceStackUtf32CharArray.GetCapacity());
		}

		TEST_METHOD(StaticMethods)
		{
			// this is true as a nullptr will result in a stack-string
			Assert::IsTrue(Elysium::Core::String::IsEmpty(nullptr));

			Assert::IsTrue(Elysium::Core::String::IsEmpty(1));
			Assert::IsTrue(Elysium::Core::WideString::IsEmpty(1));
			Assert::IsTrue(Elysium::Core::Utf8String::IsEmpty(1));
			Assert::IsTrue(Elysium::Core::Utf16String::IsEmpty(1));
			Assert::IsTrue(Elysium::Core::Utf32String::IsEmpty(1));

			Assert::IsTrue(Elysium::Core::String::IsEmpty(""));
			Assert::IsTrue(Elysium::Core::WideString::IsEmpty(L""));
			Assert::IsTrue(Elysium::Core::Utf8String::IsEmpty(u8""));
			Assert::IsTrue(Elysium::Core::Utf16String::IsEmpty(u""));
			Assert::IsTrue(Elysium::Core::Utf32String::IsEmpty(U""));

			Assert::IsFalse(Elysium::Core::String::IsEmpty("xyz"));
			Assert::IsFalse(Elysium::Core::WideString::IsEmpty(L"xyz"));
			Assert::IsFalse(Elysium::Core::Utf8String::IsEmpty(u8"xyz"));
			Assert::IsFalse(Elysium::Core::Utf16String::IsEmpty(u"xyz"));
			Assert::IsFalse(Elysium::Core::Utf32String::IsEmpty(U"xyz"));

			Assert::IsFalse(Elysium::Core::String::IsEmpty("this string is too large to fit onto stack"));
			Assert::IsFalse(Elysium::Core::WideString::IsEmpty(L"this string is too large to fit onto stack"));
			Assert::IsFalse(Elysium::Core::Utf8String::IsEmpty(u8"this string is too large to fit onto stack"));
			Assert::IsFalse(Elysium::Core::Utf16String::IsEmpty(u"this string is too large to fit onto stack"));
			Assert::IsFalse(Elysium::Core::Utf32String::IsEmpty(U"this string is too large to fit onto stack"));
		}
	};
}
