#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Utility/__MakeIntegerSequence.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Utility/__Repeat.hpp"

using namespace Elysium::Core::Template::Utility;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Utility
{
	TEST_CLASS(__RepeatTests)
	{
	public:
		TEST_METHOD(Bla)
		{
			__Repeat<IntegerSequence<Elysium::Core::Template::System::int8_t, -7>>::Type MinusSevenToZero =
				IntegerSequence<Elysium::Core::Template::System::int8_t, -7, -6, -5, -4, -3, -2, -1, 0>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::int8_t, -7, -6>>::Type MinusSevenToEight =
				IntegerSequence<Elysium::Core::Template::System::int8_t, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t, 0>>::Type ZeroToSeven =
				IntegerSequence<Elysium::Core::Template::System::uint8_t, 0, 1, 2, 3, 4, 5, 6, 7>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t, 1, 2>, 25, 26>::Type ZeroToSixteenPlusAdditional =
				IntegerSequence<Elysium::Core::Template::System::uint8_t, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
				25, 26>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t, 0>>::Type ZeroToSevenThroughMakeIntegerSequence =
				MakeIntegerSequence<Elysium::Core::Template::System::uint8_t, 8>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t, 0, 1>>::Type ZeroToSixteenThroughMakeIntegerSequence =
				MakeIntegerSequence<Elysium::Core::Template::System::uint8_t, 16>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t, 0, 0>, 25, 26>::Type SomeSequence0 =
				IntegerSequence<Elysium::Core::Template::System::uint8_t, 0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14, 25, 26>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t, 1, 1>, 25, 26>::Type SomeSequence1 =
				IntegerSequence<Elysium::Core::Template::System::uint8_t, 1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15, 25, 26>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t, 0, 0, 0>, 25, 26>::Type SomeSequence2 =
				IntegerSequence<Elysium::Core::Template::System::uint8_t, 0, 0, 0, 3, 3, 3, 6, 6, 6, 9, 9, 9, 12, 12, 12, 15, 15, 15, 18, 18, 18,
				21, 21, 21, 25, 26>();

			__Repeat<IntegerSequence<Elysium::Core::Template::System::uint8_t,
				0, 1, 2, 3, 4, 5, 6, 7,
				8, 9, 10, 11, 12, 13, 14, 15,
				16, 17, 18, 19, 20, 21, 22, 23,
				24, 25, 26, 27, 28, 29, 30>, 
				248, 249, 250, 251, 252, 253, 254	// just 7 entries here, not 8!!!
			>::Type ZeroToMaximumMinusOne =
				MakeIntegerSequence<Elysium::Core::Template::System::uint8_t, 255>();
			
		}
	};
}
