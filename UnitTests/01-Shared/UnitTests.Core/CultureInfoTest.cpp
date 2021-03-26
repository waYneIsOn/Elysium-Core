#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/CultureInfo.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Globalization
{
	TEST_CLASS(CultureInfoTest)
	{
	public:
		TEST_METHOD(CheckInvariantCulture)
		{
			// check culture
			const CultureInfo InvariantCulture = CultureInfo::GetInvariantCulture();
			Assert::AreEqual(127, InvariantCulture.GetLCID());
			AssertExtended::AreEqual(String(u8"Invariant Language (Invariant Country)"), InvariantCulture.GetEnglishName());
			Assert::AreEqual((size_t)0, InvariantCulture.GetName().GetLength());

			const String DisplayName = InvariantCulture.GetDisplayName();

			// check calendar
			// ...

			// check numberformatinfo
			NumberFormatInfo NumberFormat = InvariantCulture.GetNumberFormatInfo();
			Assert::AreEqual(2, NumberFormat.GetCurrencyDecimalDigits());
			AssertExtended::AreEqual(String(u8"."), NumberFormat.GetCurrencyDecimalSeparator());
			AssertExtended::AreEqual(String(u8","), NumberFormat.GetCurrencyGroupSeparator());
			//Assert::AreEqual(0, NumberFormat.GetCurrencyNegativePattern());
			//Assert::AreEqual(0, NumberFormat.GetCurrencyPositivePattern());
			AssertExtended::AreEqual(String(u8"¤"), NumberFormat.GetCurrencySymbol());
			Assert::AreEqual(static_cast<Elysium::Core::uint32_t>(DigitShapes::None), static_cast<Elysium::Core::uint32_t>(NumberFormat.GetDigitSubstitution()));
			Assert::AreEqual(false, NumberFormat.GetIsReadOnly());
			AssertExtended::AreEqual(String(u8"NaN"), NumberFormat.GetNaNSymbol());
			AssertExtended::AreEqual(String(u8"-Infinity"), NumberFormat.GetNegativeInfinitySymbol());
			AssertExtended::AreEqual(String(u8"-"), NumberFormat.GetNegativeSign());
			//Assert::AreEqual(2, NumberFormat.GetNumberDecimalDigits());
			AssertExtended::AreEqual(String(u8"."), NumberFormat.GetNumberDecimalSeparator());
			AssertExtended::AreEqual(String(u8","), NumberFormat.GetNumberGroupSeparator());
			Assert::AreEqual(2, NumberFormat.GetPercentDecimalDigits());
			AssertExtended::AreEqual(String(u8"."), NumberFormat.GetPercentDecimalSeparator());
			AssertExtended::AreEqual(String(u8","), NumberFormat.GetPercentGroupSeparator());
			Assert::AreEqual(0, NumberFormat.GetPercentNegativePattern());
			Assert::AreEqual(0, NumberFormat.GetPercentPositivePattern());
			AssertExtended::AreEqual(String(u8"%"), NumberFormat.GetPercentSymbol());
			AssertExtended::AreEqual(String(u8"‰"), NumberFormat.GetPerMilleSymbol());
			AssertExtended::AreEqual(String(u8"Infinity"), NumberFormat.GetPositiveInfinitySymbol());
			AssertExtended::AreEqual(String(u8"+"), NumberFormat.GetPositiveSign());
		}

		TEST_METHOD(CheckCultureByName)
		{
			// check culture
			const CultureInfo Culture = CultureInfo(u8"de-AT", true);
			Assert::AreEqual(3079, Culture.GetLCID());
			AssertExtended::AreEqual(String(u8"de-AT"), Culture.GetName());

			// check calendar
			// ...

			// check numberformatinfo
			NumberFormatInfo NumberFormat = Culture.GetNumberFormatInfo();
			NumberFormat.SetCurrencyDecimalSeparator(String(u8"X"));
			AssertExtended::AreEqual(String(u8"X"), NumberFormat.GetCurrencyDecimalSeparator());

			NumberFormat.SetCurrencyDecimalSeparator(String(u8","));
			AssertExtended::AreEqual(String(u8","), NumberFormat.GetCurrencyDecimalSeparator());
		}
	};
}
