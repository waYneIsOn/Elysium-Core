#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Globalization/RegionInfo.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Globalization
{
	TEST_CLASS(RegionInfoTest)
	{
	public:
		TEST_METHOD(CheckInvariantRegion)
		{
			const Utf8RegionInfo InvariantRegion = Utf8RegionInfo(127);
			AssertExtended::AreEqual(u8"Invariant Country", InvariantRegion.GetEnglishName());
			AssertExtended::AreEqual(u8"Invariant Country", InvariantRegion.GetNativeName());
			Assert::AreEqual((Elysium::Core::size)0, InvariantRegion.GetThreeLetterISORegionName().GetLength());
			AssertExtended::AreEqual(u8"IV", InvariantRegion.GetTwoLetterISORegionName());
			Assert::IsTrue(InvariantRegion.GetIsMetric());
		}

		TEST_METHOD(CheckRegionGermanAustria)
		{
			const Utf8RegionInfo NamedRegion = Utf8RegionInfo(u8"de-AT");
			AssertExtended::AreEqual(u8"Austria", NamedRegion.GetEnglishName());
			AssertExtended::AreEqual(u8"Österreich", NamedRegion.GetNativeName());
			AssertExtended::AreEqual(u8"AUT", NamedRegion.GetThreeLetterISORegionName());
			AssertExtended::AreEqual(u8"AT", NamedRegion.GetTwoLetterISORegionName());
			Assert::IsTrue(NamedRegion.GetIsMetric());
		}

		TEST_METHOD(CheckRegionEnglishAmerica)
		{
			const Utf8RegionInfo NamedRegion = Utf8RegionInfo(u8"en-US");
			AssertExtended::AreEqual(u8"United States", NamedRegion.GetEnglishName());
			AssertExtended::AreEqual(u8"United States", NamedRegion.GetNativeName());
			AssertExtended::AreEqual(u8"USA", NamedRegion.GetThreeLetterISORegionName());
			AssertExtended::AreEqual(u8"US", NamedRegion.GetTwoLetterISORegionName());
			Assert::IsFalse(NamedRegion.GetIsMetric());
		}
	};
}
