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
		TEST_METHOD(Decimal)
		{
			Elysium::Core::Template::Math::Decimal Zero = Elysium::Core::Template::Math::Decimal(0_i64, 0_ui64);
			Elysium::Core::Template::Math::Decimal Positive = Elysium::Core::Template::Math::Decimal(3_i64, 5_ui64);
			Elysium::Core::Template::Math::Decimal Negative = Elysium::Core::Template::Math::Decimal(-2_i64, 345_ui64);
			Elysium::Core::Template::Math::Decimal NonHandledPostDecimalPoint = Elysium::Core::Template::Math::Decimal(2_i64, 123456789_ui64);
			Elysium::Core::Template::Math::Decimal NotWorking = -2.345;

			Elysium::Core::Template::Text::String<wchar_t> ZeroWString = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(Zero);
			Elysium::Core::Template::Text::String<wchar_t> PositiveWString = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(Positive);
			Elysium::Core::Template::Text::String<wchar_t> NegativeWString = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(Negative);
			Elysium::Core::Template::Text::String<wchar_t> NonHandledPostDecimalPointWString = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(NonHandledPostDecimalPoint);
			//Elysium::Core::Template::Text::String<wchar_t> NotWorkingWString = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(NotWorking);

			Logger::WriteMessage(&ZeroWString[0]);
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(&PositiveWString[0]);
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(&NegativeWString[0]);
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(&NonHandledPostDecimalPointWString[0]);
			Logger::WriteMessage("\r\n");
			/*
			Logger::WriteMessage(&NotWorkingWString[0]);
			Logger::WriteMessage("\r\n");
			*/
		}

		TEST_METHOD(Ui8ToString)
		{
			Elysium::Core::Template::System::uint8_t Bases[] = { 2, 8, 10, 16 };

			for (Elysium::Core::Template::System::size i = 0_ui64; i < 256_ui64; i++)
			{
				for (Elysium::Core::Template::System::size j = 0_ui64; j < 4_ui64; j++)
				{
					Elysium::Core::Template::System::uint8_t Value = i;
					Elysium::Core::Template::Text::String<wchar_t> WideString = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(Value, Bases[j]);

					//Assert::AreEqual(1_ui64, WideString.GetLength(), &WideString[0]);
				}
			}
		}

		TEST_METHOD(UnsignedSingleDigitToString)
		{
			Elysium::Core::Template::System::uint8_t Bases[] = { 2, 8, 10, 16 };
			Elysium::Core::Template::System::uint8_t ExpectedLengths[] = { 1, 1, 1, 1 };

			for (Elysium::Core::Template::System::size i = 0_ui64; i < 9_ui64; i++)
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
			for (Elysium::Core::Template::System::size i = 10_ui64; i < 99_ui64; i++)
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
			for (Elysium::Core::Template::System::size i = 100_ui64; i < 256_ui64; i++)
			{
				Elysium::Core::Template::System::uint8_t ValueU8 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU8 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU8);

				Assert::AreEqual(3_ui64, StringU8.GetLength(), &StringU8[0]);
			}

			for (Elysium::Core::Template::System::size i = 100_ui64; i < 999_ui64; i++)
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
			for (Elysium::Core::Template::System::size i = 1000_ui64; i < 9999_ui64; i++)
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

		TEST_METHOD(UnsignedQuintDigitToString)
		{
			for (Elysium::Core::Template::System::size i = 10000_ui64; i < 65535_ui64; i++)
			{
				Elysium::Core::Template::System::uint16_t ValueU16 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU16 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU16);

				Assert::AreEqual(5_ui64, StringU16.GetLength(), &StringU16[0]);
			}

			for (Elysium::Core::Template::System::size i = 10000_ui64; i < 99999_ui64; i++)
			{
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(5_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(5_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}

		TEST_METHOD(UnsignedSextDigitToString)
		{
			for (Elysium::Core::Template::System::size i = 100000_ui64; i < 999999_ui64; i++)
			{
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(6_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(6_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}

		// This methods runs for a few minutes at least, so ignore it unless you specifically want to run it!
		BEGIN_TEST_METHOD_ATTRIBUTE(UnsignedSeptimDigitToString)
		TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(UnsignedSeptimDigitToString)
		{
			for (Elysium::Core::Template::System::size i = 1000000_ui64; i < 9999999_ui64; i++)
			{
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(7_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(7_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}

		// This methods runs for way too long, so ignore it unless you specifically want to run it!
		BEGIN_TEST_METHOD_ATTRIBUTE(UnsignedOctoDigitToString)
		TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(UnsignedOctoDigitToString)
		{
			Elysium::Core::Template::System::uint32_t fdsgdfg1 = 10000000;
			Elysium::Core::Template::System::uint32_t fdsgdfg12 = 99999999;

			for (Elysium::Core::Template::System::size i = 10000000_ui64; i < 99999999_ui64; i++)
			{
				Elysium::Core::Template::System::uint32_t ValueU32 = i;
				Elysium::Core::Template::System::uint64_t ValueU64 = i;

				Elysium::Core::Template::Text::String<wchar_t> StringU32 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU32);
				Elysium::Core::Template::Text::String<wchar_t> StringU64 = Elysium::Core::Template::Text::Convert<wchar_t>::ToString(ValueU64);

				Assert::AreEqual(8_ui64, StringU32.GetLength(), &StringU32[0]);
				Assert::AreEqual(8_ui64, StringU64.GetLength(), &StringU64[0]);
			}
		}
	};
}
