#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Globalization/CultureInfo.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Globalization;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Globalization
{
	TEST_CLASS(CultureInfoTest)
	{
	public:
		TEST_METHOD(GetSpecificCultures)
		{
			Array<CultureInfo> NeutralCultures = CultureInfo::GetCultures(CultureTypes::NeutralCultures);
			Array<CultureInfo> SpecificCultures = CultureInfo::GetCultures(CultureTypes::SpecificCultures);
			Array<CultureInfo> InstalledCultures = CultureInfo::GetCultures(CultureTypes::InstalledCultures);
			Array<CultureInfo> AllCultures = CultureInfo::GetCultures(CultureTypes::AllCultures);
			Assert::AreNotSame((size_t)0, AllCultures.GetLength());
			
			for (size_t i = 0; i < AllCultures.GetLength(); i++)
			{
				const String Name = AllCultures[i].GetName();
				if (Name == u8"aa")
				{
					int lkdfjg = 45;
				}

				if (Name.GetLength() == 0)
				{
					Logger::WriteMessage("\r\n");
				}
				else
				{
					Array<byte> Bytes = Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&Name[0], Name.GetLength(), sizeof(wchar_t));
					//Logger::WriteMessage((wchar_t*)&Bytes[0]);
					Logger::WriteMessage("\r\n");
				}
			}
			
			int sdlkjf = 34;
		}
		
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

		TEST_METHOD(CheckCultureGermanAustria)
		{
			// check culture
			const CultureInfo NamedCulture = CultureInfo(u8"de-AT", true);
			const CultureInfo NumberedCulture = CultureInfo(3079, true);

			Assert::AreEqual(NumberedCulture.GetLCID(), NamedCulture.GetLCID());

			CheckCultureGermanAustria(NamedCulture);
			CheckCultureGermanAustria(NumberedCulture);

			// change some values (and back again)
			NumberFormatInfo NumberFormat = NamedCulture.GetNumberFormatInfo();
			int32_t OriginalCurrencyDecimalDigits = NumberFormat.GetCurrencyDecimalDigits();
			String OriginalCurrencyDecimalSeparator = NumberFormat.GetCurrencyDecimalSeparator();

			NumberFormat.SetCurrencyDecimalDigits(OriginalCurrencyDecimalDigits + 1);
			Assert::AreEqual(OriginalCurrencyDecimalDigits + 1, NumberFormat.GetCurrencyDecimalDigits());

			NumberFormat.SetCurrencyDecimalDigits(OriginalCurrencyDecimalDigits);
			Assert::AreEqual(OriginalCurrencyDecimalDigits, NumberFormat.GetCurrencyDecimalDigits());

			NumberFormat.SetCurrencyDecimalSeparator(String(u8"X"));
			AssertExtended::AreEqual(String(u8"X"), NumberFormat.GetCurrencyDecimalSeparator());

			NumberFormat.SetCurrencyDecimalSeparator(OriginalCurrencyDecimalSeparator);
			AssertExtended::AreEqual(OriginalCurrencyDecimalSeparator, NumberFormat.GetCurrencyDecimalSeparator());
		}

		TEST_METHOD(GetBiggestValues)
		{
			Array<CultureInfo> AllCultures = CultureInfo::GetCultures(CultureTypes::AllCultures);
			for (size_t i = 0; i < AllCultures.GetLength(); i++)
			{

			}
		}
	private:
		static void CheckCultureGermanAustria(const CultureInfo& Culture)
		{
			Assert::AreEqual(3079, Culture.GetLCID());
			AssertExtended::AreEqual(String(u8"de-AT"), Culture.GetName());

			// check calendar
			// ...

			// check numberformatinfo
			NumberFormatInfo NumberFormat = Culture.GetNumberFormatInfo();
			AssertExtended::AreEqual(String(u8","), NumberFormat.GetCurrencyDecimalSeparator());
		}
	};
}
