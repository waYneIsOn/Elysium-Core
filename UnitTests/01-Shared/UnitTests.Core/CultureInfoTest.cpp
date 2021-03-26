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

			// check numberformatinfo
			const NumberFormatInfo NumberFormat = InvariantCulture.GetNumberFormatInfo();
			Assert::AreEqual(2, NumberFormat.GetCurrencyDecimalDigits());
			AssertExtended::AreEqual(String(u8"."), NumberFormat.GetNumberDecimalSeparator());

			int lksjdf = 453;
		}
	};
}
