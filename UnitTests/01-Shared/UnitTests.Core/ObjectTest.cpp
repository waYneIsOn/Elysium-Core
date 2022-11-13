#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Object.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(ObjectTest)
	{
	public:
		TEST_METHOD(ToStringTests)
		{
			AssertExtended::AreEqual(u8"-28", Object::ToString(-28_i8));
			AssertExtended::AreEqual(u8"-28", Object::ToString(-28_i16));
			AssertExtended::AreEqual(u8"-28", Object::ToString(-28_i32));
			AssertExtended::AreEqual(u8"-28", Object::ToString(-28_i64));
			AssertExtended::AreEqual(u8"28", Object::ToString(28_ui8));
			AssertExtended::AreEqual(u8"28", Object::ToString(28_ui16));
			AssertExtended::AreEqual(u8"28", Object::ToString(28_ui32));
			AssertExtended::AreEqual(u8"28", Object::ToString(28_ui64));

			// ToDo: not right!
			AssertExtended::AreEqual(u8"24.379999", Object::ToString(24.38f));
			AssertExtended::AreEqual(u8"24.380000", Object::ToString(24.38));
		}
	};
}
