#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Globalization/CultureInfo.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Globalization/NumberFormatInfo.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Globalization;
using namespace Elysium::Core::Globalization;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Globalization
{
	TEST_CLASS(CultureInfoTest)
	{
	public:
		TEST_METHOD(GetSpecificCultures)
		{
			Vector<Utf8CultureInfo> NeutralCultures = Utf8CultureInfo::GetCultures(CultureTypes::NeutralCultures);
			Vector<Utf8CultureInfo> SpecificCultures = Utf8CultureInfo::GetCultures(CultureTypes::SpecificCultures);
			Vector<Utf8CultureInfo> InstalledCultures = Utf8CultureInfo::GetCultures(CultureTypes::InstalledCultures);
			Vector<Utf8CultureInfo> AllCultures = Utf8CultureInfo::GetCultures(CultureTypes::AllCultures);
			Assert::AreNotSame((Elysium::Core::size)0, AllCultures.GetLength());
			
			for (Elysium::Core::size i = 0; i < AllCultures.GetLength(); i++)
			{
				const Elysium::Core::Utf8String Name = AllCultures[i].GetName();
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
					//Array<byte> Bytes = Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&Name[0], Name.GetLength(), sizeof(wchar_t));
					//Logger::WriteMessage((wchar_t*)&Bytes[0]);
					Logger::WriteMessage("\r\n");
				}
			}
			
			int sdlkjf = 34;
		}
		
		TEST_METHOD(CheckInvariantCulture)
		{
			// check culture
			const Utf8CultureInfo InvariantCulture = Utf8CultureInfo::GetInvariantCulture();
			AssertExtended::AreEqual(127_ui32, InvariantCulture.GetLCID());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"Invariant Language (Invariant Country)"), InvariantCulture.GetEnglishName());
			Assert::AreEqual((Elysium::Core::size)0, InvariantCulture.GetName().GetLength());

			const Elysium::Core::Utf8String DisplayName = InvariantCulture.GetDisplayName();

			// check calendar
			// ...

			// check numberformatinfo
			const Utf8NumberFormatInfo NumberFormat = InvariantCulture.GetNumberFormatInfo();
 			AssertExtended::AreEqual(2_ui32, NumberFormat.GetCurrencyDecimalDigits());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"."), NumberFormat.GetCurrencyDecimalSeparator());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8","), NumberFormat.GetCurrencyGroupSeparator());
			Assert::AreEqual(0_ui32, NumberFormat.GetCurrencyNegativePattern());
			Assert::AreEqual(0_ui32, NumberFormat.GetCurrencyPositivePattern());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"¤"), NumberFormat.GetCurrencySymbol());
			AssertExtended::AreEqual(static_cast<Elysium::Core::uint8_t>(Template::Globalization::DigitShapes::None),
				static_cast<Elysium::Core::uint8_t>(NumberFormat.GetDigitSubstitution()));
			Assert::AreEqual(false, NumberFormat.GetIsReadOnly());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"NaN"), NumberFormat.GetNaNSymbol());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"-Infinity"), NumberFormat.GetNegativeInfinitySymbol());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"-"), NumberFormat.GetNegativeSign());
			Assert::AreEqual(1_ui32, NumberFormat.GetNumberDecimalDigits());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"."), NumberFormat.GetNumberDecimalSeparator());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8","), NumberFormat.GetNumberGroupSeparator());
			AssertExtended::AreEqual(2, NumberFormat.GetPercentDecimalDigits());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"."), NumberFormat.GetPercentDecimalSeparator());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8","), NumberFormat.GetPercentGroupSeparator());
			Assert::AreEqual(0_ui32, NumberFormat.GetPercentNegativePattern());
			Assert::AreEqual(0_ui32, NumberFormat.GetPercentPositivePattern());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"%"), NumberFormat.GetPercentSymbol());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"‰"), NumberFormat.GetPerMilleSymbol());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"Infinity"), NumberFormat.GetPositiveInfinitySymbol());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"+"), NumberFormat.GetPositiveSign());
		}

		TEST_METHOD(CheckCultureGermanAustria)
		{
			// check culture
			const Utf8CultureInfo NamedCulture = Utf8CultureInfo(u8"de-AT", true);
			const Utf8CultureInfo NumberedCulture = Utf8CultureInfo(3079, true);

			const Utf8String dfgdfg1 = NamedCulture.GetName();
			const Utf8String dfgdfg2 = NumberedCulture.GetName();
			
			Assert::AreEqual(NumberedCulture.GetLCID(), NamedCulture.GetLCID());

			CheckCultureGermanAustria(NamedCulture);
			CheckCultureGermanAustria(NumberedCulture);
			
			// change some values (and back again)
			Utf8NumberFormatInfo NumberFormat = NamedCulture.GetNumberFormatInfo();
			int32_t OriginalCurrencyDecimalDigits = NumberFormat.GetCurrencyDecimalDigits();
			Elysium::Core::Utf8String OriginalCurrencyDecimalSeparator = NumberFormat.GetCurrencyDecimalSeparator();

			NumberFormat.SetCurrencyDecimalDigits(OriginalCurrencyDecimalDigits + 1);
			AssertExtended::AreEqual(OriginalCurrencyDecimalDigits + 1, NumberFormat.GetCurrencyDecimalDigits());

			NumberFormat.SetCurrencyDecimalDigits(OriginalCurrencyDecimalDigits);
			AssertExtended::AreEqual(OriginalCurrencyDecimalDigits, NumberFormat.GetCurrencyDecimalDigits());

			NumberFormat.SetCurrencyDecimalSeparator(u8"X");
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"X"), NumberFormat.GetCurrencyDecimalSeparator());

			NumberFormat.SetCurrencyDecimalSeparator(&OriginalCurrencyDecimalSeparator[0]);
			AssertExtended::AreEqual(OriginalCurrencyDecimalSeparator, NumberFormat.GetCurrencyDecimalSeparator());
		}

		TEST_METHOD(CheckValueRanges)
		{
			Vector<Utf8CultureInfo> AllCultures = Utf8CultureInfo::GetCultures(CultureTypes::AllCultures);
			for (Elysium::Core::size i = 0; i < AllCultures.GetLength(); i++)
			{
				Elysium::Core::Globalization::Utf8NumberFormatInfo NumberFormatInfo = AllCultures[i].GetNumberFormatInfo();
				
				AssertLongestValue(NumberFormatInfo, 3, u8"CurrencyDecimalDigits", u8"", NumberFormatInfo.GetCurrencyDecimalDigits());
				AssertLongestValue(NumberFormatInfo, 1, u8"CurrencyDecimalSeparator", NumberFormatInfo.GetCurrencyDecimalSeparator(), NumberFormatInfo.GetCurrencyDecimalSeparator().GetLength());
				AssertLongestValue(NumberFormatInfo, 3, u8"CurrencyGroupSeparator", NumberFormatInfo.GetCurrencyGroupSeparator(), NumberFormatInfo.GetCurrencyGroupSeparator().GetLength());
				//AssertLongestValue(NumberFormatInfo, 1, u8"CurrencyNegativePattern", u8"", NumberFormatInfo.GetCurrencyNegativePattern());
				//AssertLongestValue(NumberFormatInfo, 1, u8"CurrencyPositivePattern", u8"", NumberFormatInfo.GetCurrencyPositivePattern());
				AssertLongestValue(NumberFormatInfo, 9, u8"CurrencySymbol", NumberFormatInfo.GetCurrencySymbol(), NumberFormatInfo.GetCurrencySymbol().GetLength());
				AssertLongestValue(NumberFormatInfo, 45, u8"NaNSymbol", NumberFormatInfo.GetNaNSymbol(), NumberFormatInfo.GetNaNSymbol().GetLength());
				AssertLongestValue(NumberFormatInfo, 65, u8"NegativeInfinitySymbol", NumberFormatInfo.GetNegativeInfinitySymbol(), NumberFormatInfo.GetNegativeInfinitySymbol().GetLength());
				AssertLongestValue(NumberFormatInfo, 1, u8"NegativeSign", NumberFormatInfo.GetNegativeSign(), NumberFormatInfo.GetNegativeSign().GetLength());
				//AssertLongestValue(NumberFormatInfo, 1, u8"NumberDecimalDigits", u8"", NumberFormatInfo.GetNumberDecimalDigits());
				AssertLongestValue(NumberFormatInfo, 1, u8"NumberDecimalSeparator", NumberFormatInfo.GetNumberDecimalSeparator(), NumberFormatInfo.GetNumberDecimalSeparator().GetLength());
				AssertLongestValue(NumberFormatInfo, 3, u8"NumberGroupSeparator", NumberFormatInfo.GetNumberGroupSeparator(), NumberFormatInfo.GetNumberGroupSeparator().GetLength());
				AssertLongestValue(NumberFormatInfo, 2, u8"PercentDecimalDigits", u8"", NumberFormatInfo.GetPercentDecimalDigits());
				AssertLongestValue(NumberFormatInfo, 1, u8"PercentDecimalSeparator", NumberFormatInfo.GetPercentDecimalSeparator(), NumberFormatInfo.GetPercentDecimalSeparator().GetLength());
				AssertLongestValue(NumberFormatInfo, 3, u8"PercentGroupSeparator", NumberFormatInfo.GetPercentGroupSeparator(), NumberFormatInfo.GetPercentGroupSeparator().GetLength());
				//AssertLongestValue(NumberFormatInfo, 7, u8"PercentNegativePattern", u8"", NumberFormatInfo.GetPercentNegativePattern());
				//AssertLongestValue(NumberFormatInfo, 3, u8"PercentPositivePattern", u8"", NumberFormatInfo.GetPercentPositivePattern());
				AssertLongestValue(NumberFormatInfo, 2, u8"PercentSymbol", NumberFormatInfo.GetPercentSymbol(), NumberFormatInfo.GetPercentSymbol().GetLength());
				AssertLongestValue(NumberFormatInfo, 3, u8"PerMilleSymbol", NumberFormatInfo.GetPerMilleSymbol(), NumberFormatInfo.GetPerMilleSymbol().GetLength());
				AssertLongestValue(NumberFormatInfo, 65, u8"PositiveInfinitySymbol", NumberFormatInfo.GetPositiveInfinitySymbol(), NumberFormatInfo.GetPositiveInfinitySymbol().GetLength());
				AssertLongestValue(NumberFormatInfo, 1, u8"PositiveSign", NumberFormatInfo.GetPositiveSign(), NumberFormatInfo.GetPositiveSign().GetLength());
			}
		}
	private:
		static void CheckCultureGermanAustria(const Utf8CultureInfo& Culture)
		{
			AssertExtended::AreEqual(3079_ui32, Culture.GetLCID());
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8"de-AT"), Culture.GetName());

			// check calendar
			// ...

			// check numberformatinfo
			Utf8NumberFormatInfo NumberFormat = Culture.GetNumberFormatInfo();
			AssertExtended::AreEqual(Elysium::Core::Utf8String(u8","), NumberFormat.GetCurrencyDecimalSeparator());
		}

		static void AssertLongestValue(const Elysium::Core::Globalization::Utf8NumberFormatInfo& FormatInfo, const Elysium::Core::size MaximumAllowedLength,
			const Elysium::Core::Utf8String& Method, const Elysium::Core::Utf8String& Value, const Elysium::Core::size ActualLength)
		{
			// bla - this is just for checking values while debugging and can be changed freely
			if (Value.GetLength() > 9 && ActualLength == MaximumAllowedLength)
			{
				bool bla = false;
			}
			// bla - end

			if (ActualLength > MaximumAllowedLength)
			{
				Assert::Fail(L"Elysium::Core::Convert needs to be reevaulated!");
			}
		}
	};
}
