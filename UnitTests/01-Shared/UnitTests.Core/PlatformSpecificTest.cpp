#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/System.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PlatformSpecificTest)
	{
	public:
		TEST_METHOD(CheckActualEndianness)
		{
			uint32_t SomeI32 = 0x01000002;
			uint8_t* SomeI8Pointer = (uint8_t*)&SomeI32;

#if defined ELYSIUM_CORE_LITTLEENDIAN
			Assert::AreEqual(0x02_ui8, SomeI8Pointer[0]);
			Assert::AreEqual(0x01_ui8, SomeI8Pointer[3]);
#else
			Assert::AreEqual(0x01_ui8, SomeI8Pointer[0]);
			Assert::AreEqual(0x02_ui8, SomeI8Pointer[3]);
#endif
		}
	};
}
