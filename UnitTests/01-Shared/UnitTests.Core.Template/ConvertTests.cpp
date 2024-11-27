#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/String.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text
{
	TEST_CLASS(ConvertTests)
	{
	public:
		TEST_METHOD(UnsignedSingleDigitToString)
		{
			for (Elysium::Core::Template::System::size i = 0; i < 9; i++)
			{
				Elysium::Core::Template::System::uint8_t ValueU8 = i;
				Elysium::Core::Template::System::uint16_t ValueU16 = i;
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU8 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU8);
				Elysium::Core::Template::Text::String<wchar_t> StringU16 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU16);
				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(1_ui64, StringU8.GetLength(), &StringU8[0]);
				Assert::AreEqual(1_ui64, StringU16.GetLength(), &StringU16[0]);
				Assert::AreEqual(1_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(1_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}

		TEST_METHOD(UnsignedDoubleDigitToString)
		{
			for (Elysium::Core::Template::System::size i = 10; i < 99; i++)
			{
				Elysium::Core::Template::System::uint8_t ValueU8 = i;
				Elysium::Core::Template::System::uint16_t ValueU16 = i;
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU8 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU8);
				Elysium::Core::Template::Text::String<wchar_t> StringU16 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU16);
				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(2_ui64, StringU8.GetLength(), &StringU8[0]);
				Assert::AreEqual(2_ui64, StringU16.GetLength(), &StringU16[0]);
				Assert::AreEqual(2_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(2_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}

		TEST_METHOD(UnsignedTripleDigitToString)
		{
			for (Elysium::Core::Template::System::size i = 100; i < 256; i++)
			{
				Elysium::Core::Template::System::uint8_t ValueU8 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU8 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU8);

				Assert::AreEqual(3_ui64, StringU8.GetLength(), &StringU8[0]);
			}

			for (Elysium::Core::Template::System::size i = 100; i < 999; i++)
			{
				Elysium::Core::Template::System::uint16_t ValueU16 = i;
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU16 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU16);
				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(3_ui64, StringU16.GetLength(), &StringU16[0]);
				Assert::AreEqual(3_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(3_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}

		TEST_METHOD(UnsignedQuadDigitToString)
		{
			for (Elysium::Core::Template::System::size i = 1000; i < 9999; i++)
			{
				Elysium::Core::Template::System::uint16_t ValueU16 = i;
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU16 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU16);
				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(4_ui64, StringU16.GetLength(), &StringU16[0]);
				Assert::AreEqual(4_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(4_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}
	};
}
