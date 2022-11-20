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
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[3]));

			Elysium::Core::uint16_t UI16 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[3]));

			Elysium::Core::uint32_t UI32 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[3]));

			Elysium::Core::uint64_t UI64 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[3]));

			Elysium::Core::int8_t I8 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[3]));

			Elysium::Core::int16_t I16 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[3]));

			Elysium::Core::int32_t I32 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[3]));

			Elysium::Core::int64_t I64 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[3]));
			/*
			float Floating32 = 27.58;
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[0]));
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[1]));
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[2]));
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[3]));
			/*
			double Floating64 = 27.58;
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[0]));
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[1]));
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[2]));
			AssertExtended::AreEqual(u8"27.58", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[3]));
			*/
		}

		TEST_METHOD(ZeroToString)
		{
			for (Elysium::Core::uint8_t i = 0; i < NumberOfBases; i++)
			{
				Elysium::Core::int8_t I8 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I8, Bases[i]));

				Elysium::Core::int16_t I16 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I16, Bases[i]));

				Elysium::Core::int32_t I32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I32, Bases[i]));

				Elysium::Core::int64_t I64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(I64, Bases[i]));

				Elysium::Core::int8_t UI8 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI8, Bases[i]));

				Elysium::Core::uint16_t UI16 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI16, Bases[i]));

				Elysium::Core::uint32_t UI32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI32, Bases[i]));

				Elysium::Core::uint64_t UI64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(UI64, Bases[i]));
				
				float Floating32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating32, Bases[i]));

				double Floating64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating64, Bases[i]));

				//Elysium::Core::Decimal Floating128;
				//AssertExtended::AreEqual(u8"0", Elysium::Core::Template::Text::Convert<char8_t>::ToString(Floating128, Bases[i]));
			}
		}
	private:
		inline static const Elysium::Core::uint8_t NumberOfBases = 4;
		inline static const Elysium::Core::uint8_t Bases[NumberOfBases] = { 2, 8, 10, 16 };
	};
}
