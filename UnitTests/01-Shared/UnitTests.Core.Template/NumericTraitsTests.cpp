#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/NumericTraits.hpp"

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Numeric
{
	TEST_CLASS(NumericTraitsTests)
	{
	public:
		TEST_METHOD(GetLowAndHigh)
		{
			constexpr const Elysium::Core::uint32_t Input = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::uint32_t>::Maximum - 1294967295;

			constexpr const Elysium::Core::uint16_t LowWindows = LOWORD(Input);
			constexpr const Elysium::Core::uint16_t LowElysium = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::uint32_t>::GetLow(Input);

			constexpr const Elysium::Core::uint16_t HighWindows = HIWORD(Input);
			constexpr const Elysium::Core::uint16_t HighElysium = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::uint32_t>::GetHigh(Input);

			AssertExtended::AreEqual(static_cast<Elysium::Core::uint16_t>(LowWindows), LowElysium);
			AssertExtended::AreEqual(static_cast<Elysium::Core::uint16_t>(HighWindows), HighElysium);
		}
	};
}