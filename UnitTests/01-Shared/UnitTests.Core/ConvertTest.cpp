#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Decimal.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(ConvertTest)
	{
	public:
		TEST_METHOD(NegativeToString)
		{
			Elysium::Core::int8_t I8 = -27;
			AssertExtended::AreEqual(u8"-11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[0]));
			AssertExtended::AreEqual(u8"-33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[1]));
			AssertExtended::AreEqual(u8"-27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[2]));
			AssertExtended::AreEqual(u8"-1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[3]));

			Elysium::Core::int16_t I16 = -27;
			AssertExtended::AreEqual(u8"-11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[0]));
			AssertExtended::AreEqual(u8"-33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[1]));
			AssertExtended::AreEqual(u8"-27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[2]));
			AssertExtended::AreEqual(u8"-1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[3]));

			Elysium::Core::int32_t I32 = -27;
			AssertExtended::AreEqual(u8"-11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[0]));
			AssertExtended::AreEqual(u8"-33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[1]));
			AssertExtended::AreEqual(u8"-27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[2]));
			AssertExtended::AreEqual(u8"-1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[3]));

			Elysium::Core::int64_t I64 = -27;
			AssertExtended::AreEqual(u8"-11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[0]));
			AssertExtended::AreEqual(u8"-33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[1]));
			AssertExtended::AreEqual(u8"-27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[2]));
			AssertExtended::AreEqual(u8"-1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[3]));
			
			float Floating32 = -27.27f;
			AssertExtended::AreEqual(u8"-11011.11", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[0]));
			AssertExtended::AreEqual(u8"-33.33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[1]));
			AssertExtended::AreEqual(u8"-27.27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[2]));
			AssertExtended::AreEqual(u8"-1B.1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[3]));
			
			double Floating64 = -27.27;
			AssertExtended::AreEqual(u8"-11011.11", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[0]));
			AssertExtended::AreEqual(u8"-33.32", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[1]));
			AssertExtended::AreEqual(u8"-27.26", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[2]));
			AssertExtended::AreEqual(u8"-1B.1A", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[3]));
		}

		TEST_METHOD(PositiveToString)
		{
			Elysium::Core::uint8_t UI8 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(UI8, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(UI8, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(UI8, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(UI8, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[3]));
			/*
			AssertExtended::AreEqual(u"11011", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI8, Bases[0]));
			AssertExtended::AreEqual(u"33", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI8, Bases[1]));
			AssertExtended::AreEqual(u"27", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI8, Bases[2]));
			AssertExtended::AreEqual(u"1B", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI8, Bases[3]));

			AssertExtended::AreEqual(U"11011", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI8, Bases[0]));
			AssertExtended::AreEqual(U"33", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI8, Bases[1]));
			AssertExtended::AreEqual(U"27", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI8, Bases[2]));
			AssertExtended::AreEqual(U"1B", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI8, Bases[3]));

			AssertExtended::AreEqual(L"11011", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI8, Bases[0]));
			AssertExtended::AreEqual(L"33", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI8, Bases[1]));
			AssertExtended::AreEqual(L"27", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI8, Bases[2]));
			AssertExtended::AreEqual(L"1B", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI8, Bases[3]));
			*/
			Elysium::Core::uint16_t UI16 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(UI16, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(UI16, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(UI16, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(UI16, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[3]));

			Elysium::Core::uint32_t UI32 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(UI32, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(UI32, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(UI32, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(UI32, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[3]));

			Elysium::Core::uint64_t UI64 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(UI64, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(UI64, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(UI64, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(UI64, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[3]));

			Elysium::Core::int8_t I8 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(I8, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(I8, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(I8, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(I8, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[3]));

			Elysium::Core::int16_t I16 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(I16, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(I16, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(I16, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(I16, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[3]));

			Elysium::Core::int32_t I32 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(I32, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(I32, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(I32, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(I32, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[3]));

			Elysium::Core::int64_t I64 = 27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(I64, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(I64, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(I64, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(I64, Bases[3]));

			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[3]));

			float Floating32 = 27.27f;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(Floating32, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(Floating32, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(Floating32, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(Floating32, Bases[3]));

			AssertExtended::AreEqual(u8"11011.11", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[0]));
			AssertExtended::AreEqual(u8"33.33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[1]));
			AssertExtended::AreEqual(u8"27.27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[2]));
			AssertExtended::AreEqual(u8"1B.1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[3]));

			double Floating64 = 27.27;
			AssertExtended::AreEqual("11011", Elysium::Core::Template::Text::Convert<char>::ToString(Floating64, Bases[0]));
			AssertExtended::AreEqual("33", Elysium::Core::Template::Text::Convert<char>::ToString(Floating64, Bases[1]));
			AssertExtended::AreEqual("27", Elysium::Core::Template::Text::Convert<char>::ToString(Floating64, Bases[2]));
			AssertExtended::AreEqual("1B", Elysium::Core::Template::Text::Convert<char>::ToString(Floating64, Bases[3]));

			AssertExtended::AreEqual(u8"11011.11", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[0]));
			AssertExtended::AreEqual(u8"33.32", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[1]));
			AssertExtended::AreEqual(u8"27.26", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[2]));
			AssertExtended::AreEqual(u8"1B.1A", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[3]));
		}

		TEST_METHOD(ZeroToString)
		{
			for (Elysium::Core::uint8_t i = 0; i < NumberOfBases; i++)
			{
				Elysium::Core::int8_t I8 = 0;
				AssertExtended::AreEqual("0", Elysium::Core::Template::Text::Convert<char>::ToString(I8, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(I8, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(I8, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(I8, Bases[i]));

				Elysium::Core::int16_t I16 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(I16, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(I16, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(I16, Bases[i]));

				Elysium::Core::int32_t I32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(I32, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(I32, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(I32, Bases[i]));

				Elysium::Core::int64_t I64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(I64, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(I64, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(I64, Bases[i]));

				Elysium::Core::int8_t UI8 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI8, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI8, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI8, Bases[i]));

				Elysium::Core::uint16_t UI16 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI16, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI16, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI16, Bases[i]));

				Elysium::Core::uint32_t UI32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI32, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI32, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI32, Bases[i]));

				Elysium::Core::uint64_t UI64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(UI64, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(UI64, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(UI64, Bases[i]));
				
				float Floating32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(Floating32, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(Floating32, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(Floating32, Bases[i]));

				double Floating64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[i]));
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[i]));
				AssertExtended::AreEqual(u"0", Elysium::Core::Template::Text::Convert<char16_t>::ToString(Floating64, Bases[i]));
				AssertExtended::AreEqual(U"0", Elysium::Core::Template::Text::Convert<char32_t>::ToString(Floating64, Bases[i]));
				AssertExtended::AreEqual(L"0", Elysium::Core::Template::Text::Convert<wchar_t>::ToString(Floating64, Bases[i]));

				//Elysium::Core::Decimal Floating128;
				//AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating128, Bases[i]));
			}
		}

		TEST_METHOD(ZeroToInt)
		{
			for (Elysium::Core::uint8_t i = 0; i < NumberOfBases; i++)
			{
				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char>::ToUInt8("0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char>::ToUInt16("0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char>::ToUInt32("0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char>::ToUInt64("0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char>::ToUInt8("-0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char>::ToUInt16("-0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char>::ToUInt32("-0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char>::ToUInt64("-0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char>::ToUInt8("+0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char>::ToUInt16("+0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char>::ToUInt32("+0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char>::ToUInt64("+0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char>::ToUInt8("0 ", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char>::ToUInt16("0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char>::ToUInt32("0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char>::ToUInt64("0 ", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(u8"0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(u8"0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt32(u8"0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt64(u8"0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(u8"-0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(u8"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt32(u8"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt64(u8"-0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(u8"+0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(u8"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt32(u8"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt64(u8"+0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(u8"0 ", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(u8"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt32(u8"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char8_t>::ToUInt64(u8"0 ", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt8(u"0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt16(u"0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt32(u"0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt64(u"0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt8(u"-0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt16(u"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt32(u"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt64(u"-0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt8(u"+0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt16(u"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt32(u"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt64(u"+0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt8(u"0 ", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt16(u"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt32(u"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char16_t>::ToUInt64(u"0 ", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt8(U"0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt16(U"0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt32(U"0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt64(U"0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt8(U"-0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt16(U"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt32(U"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt64(U"-0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt8(U"+0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt16(U"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt32(U"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt64(U"+0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt8(U"0 ", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt16(U"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt32(U"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<char32_t>::ToUInt64(U"0 ", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt8(L"0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt16(L"0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt32(L"0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt64(L"0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt8(L"-0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt16(L"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt32(L"-0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt64(L"-0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt8(L"+0", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt16(L"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt32(L"+0", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt64(L"+0", 1, Bases[i]));

				Assert::AreEqual(0_ui8, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt8(L"0 ", 1, Bases[i]));
				AssertExtended::AreEqual(0_ui16, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt16(L"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui32, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt32(L"0 ", 1, Bases[i]));
				Assert::AreEqual(0_ui64, Elysium::Core::Template::Text::Convert<wchar_t>::ToUInt64(L"0 ", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char>::ToInt8("0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char>::ToInt16("0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char>::ToInt32("0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char>::ToInt64("0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char>::ToInt8("-0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char>::ToInt16("-0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char>::ToInt32("-0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char>::ToInt64("-0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char>::ToInt8("+0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char>::ToInt16("+0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char>::ToInt32("+0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char>::ToInt64("+0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char>::ToInt8("0 ", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char>::ToInt16("0 ", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char>::ToInt32("0 ", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char>::ToInt64("0 ", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char8_t>::ToInt8(u8"0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char8_t>::ToInt16(u8"0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(u8"0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char8_t>::ToInt64(u8"0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char8_t>::ToInt8(u8"-0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char8_t>::ToInt16(u8"-0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(u8"-0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char8_t>::ToInt64(u8"-0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char8_t>::ToInt8(u8"+0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char8_t>::ToInt16(u8"+0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(u8"+0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char8_t>::ToInt64(u8"+0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char8_t>::ToInt8(u8"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char8_t>::ToInt16(u8"0 ", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(u8"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char8_t>::ToInt64(u8"0 ", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char16_t>::ToInt8(u"0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char16_t>::ToInt16(u"0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char16_t>::ToInt32(u"0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char16_t>::ToInt64(u"0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char16_t>::ToInt8(u"-0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char16_t>::ToInt16(u"-0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char16_t>::ToInt32(u"-0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char16_t>::ToInt64(u"-0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char16_t>::ToInt8(u"+0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char16_t>::ToInt16(u"+0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char16_t>::ToInt32(u"+0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char16_t>::ToInt64(u"+0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char16_t>::ToInt8(u"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char16_t>::ToInt16(u"0 ", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char16_t>::ToInt32(u"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char16_t>::ToInt64(u"0 ", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char32_t>::ToInt8(U"0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char32_t>::ToInt16(U"0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char32_t>::ToInt32(U"0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char32_t>::ToInt64(U"0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char32_t>::ToInt8(U"-0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char32_t>::ToInt16(U"-0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char32_t>::ToInt32(U"-0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char32_t>::ToInt64(U"-0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char32_t>::ToInt8(U"+0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char32_t>::ToInt16(U"+0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char32_t>::ToInt32(U"+0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char32_t>::ToInt64(U"+0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<char32_t>::ToInt8(U"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<char32_t>::ToInt16(U"0 ", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<char32_t>::ToInt32(U"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<char32_t>::ToInt64(U"0 ", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt8(L"0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt16(L"0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt32(L"0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt64(L"0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt8(L"-0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt16(L"-0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt32(L"-0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt64(L"-0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt8(L"+0", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt16(L"+0", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt32(L"+0", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt64(L"+0", 1, Bases[i]));

				Assert::AreEqual(0_i8, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt8(L"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i16, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt16(L"0 ", 1, Bases[i]));
				Assert::AreEqual(0, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt32(L"0 ", 1, Bases[i]));
				Assert::AreEqual(0_i64, Elysium::Core::Template::Text::Convert<wchar_t>::ToInt64(L"0 ", 1, Bases[i]));

				//Assert::AreEqual(0.0f, Elysium::Core::Template::Text::Convert<char>::ToSingle("0", 1, Bases[i]));
				//Assert::AreEqual(0.0, Elysium::Core::Template::Text::Convert<char>::ToDouble("0", 1, Bases[i]));
			}
		}
	private:
		inline static const Elysium::Core::uint8_t NumberOfBases = 4;
		inline static const Elysium::Core::uint8_t Bases[NumberOfBases] = { 2, 8, 10, 16 };
	};
}
