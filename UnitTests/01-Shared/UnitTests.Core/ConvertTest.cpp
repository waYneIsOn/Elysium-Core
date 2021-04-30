#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Convert.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(ConvertTest)
	{
	public:
		TEST_METHOD(NegativeToString)
		{
			Elysium::Core::int16_t I16 = -27;
			AssertExtended::AreEqual(u8"-11011", Elysium::Core::Convert::ToString(I16, Bases[0]));
			AssertExtended::AreEqual(u8"-33", Elysium::Core::Convert::ToString(I16, Bases[1]));
			AssertExtended::AreEqual(u8"-27", Elysium::Core::Convert::ToString(I16, Bases[2]));
			AssertExtended::AreEqual(u8"-1B", Elysium::Core::Convert::ToString(I16, Bases[3]));
		}

		TEST_METHOD(PositiveToString)
		{
			Elysium::Core::int16_t I16 = 27;
			AssertExtended::AreEqual(u8"11011", Elysium::Core::Convert::ToString(I16, Bases[0]));
			AssertExtended::AreEqual(u8"33", Elysium::Core::Convert::ToString(I16, Bases[1]));
			AssertExtended::AreEqual(u8"27", Elysium::Core::Convert::ToString(I16, Bases[2]));
			AssertExtended::AreEqual(u8"1B", Elysium::Core::Convert::ToString(I16, Bases[3]));
		}

		TEST_METHOD(ZeroToString)
		{
			for (Elysium::Core::uint8_t i = 0; i < NumberOfBases; i++)
			{
				Elysium::Core::int8_t I8 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(I8, Bases[i]));

				Elysium::Core::int16_t I16 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(I16, Bases[i]));

				Elysium::Core::int32_t I32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(I32, Bases[i]));

				Elysium::Core::int64_t I64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(I64, Bases[i]));

				Elysium::Core::int8_t UI8 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(UI8, Bases[i]));

				Elysium::Core::uint16_t UI16 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(UI16, Bases[i]));

				Elysium::Core::uint32_t UI32 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(UI32, Bases[i]));

				Elysium::Core::uint64_t UI64 = 0;
				AssertExtended::AreEqual(u8"0", Elysium::Core::Convert::ToString(UI64, Bases[i]));
			}
		}
	private:
		inline static const Elysium::Core::uint8_t NumberOfBases = 4;
		inline static const Elysium::Core::uint8_t Bases[NumberOfBases] = { 2, 8, 10, 16 };
	};
}
