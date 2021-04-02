#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/RegionInfo.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Globalization;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Globalization
{
	TEST_CLASS(RegionInfoTest)
	{
	public:
		TEST_METHOD(CheckInvariantRegion)
		{
			const RegionInfo InvariantRegion = RegionInfo(127);
			AssertExtended::AreEqual(String(u8"Invariant Country"), InvariantRegion.GetEnglishName());
			AssertExtended::AreEqual(String(u8"Invariant Country"), InvariantRegion.GetNativeName());
			Assert::AreEqual((size_t)0, InvariantRegion.GetThreeLetterISORegionName().GetLength());
			AssertExtended::AreEqual(String(u8"IV"), InvariantRegion.GetTwoLetterISORegionName());
			Assert::IsTrue(InvariantRegion.GetIsMetric());
		}

		TEST_METHOD(CheckRegionGermanAustria)
		{
			const RegionInfo NamedRegion = RegionInfo(u8"de-AT");
			AssertExtended::AreEqual(String(u8"Austria"), NamedRegion.GetEnglishName());
			AssertExtended::AreEqual(String(u8"Österreich"), NamedRegion.GetNativeName());
			AssertExtended::AreEqual(String(u8"AUT"), NamedRegion.GetThreeLetterISORegionName());
			AssertExtended::AreEqual(String(u8"AT"), NamedRegion.GetTwoLetterISORegionName());
			Assert::IsTrue(NamedRegion.GetIsMetric());
		}

		TEST_METHOD(CheckRegionEnglishAmerica)
		{
			const RegionInfo NamedRegion = RegionInfo(u8"en-US");
			AssertExtended::AreEqual(String(u8"United States"), NamedRegion.GetEnglishName());
			AssertExtended::AreEqual(String(u8"United States"), NamedRegion.GetNativeName());
			AssertExtended::AreEqual(String(u8"USA"), NamedRegion.GetThreeLetterISORegionName());
			AssertExtended::AreEqual(String(u8"US"), NamedRegion.GetTwoLetterISORegionName());
			Assert::IsFalse(NamedRegion.GetIsMetric());
		}
	};
}
