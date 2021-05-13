#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Object.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(ObjectTest)
	{
	public:
		TEST_METHOD(GetHashCodeTest)
		{
			Assert::AreEqual(-28, Object::GetHashCode(-28_i8));
			Assert::AreEqual(-28, Object::GetHashCode(-28_i16));
			Assert::AreEqual(-28, Object::GetHashCode(-28_i32));
			Assert::AreEqual(-28, Object::GetHashCode(-28_i64));
			Assert::AreEqual(228, Object::GetHashCode(228_ui8));
			Assert::AreEqual(228, Object::GetHashCode(228_ui16));
			Assert::AreEqual(228, Object::GetHashCode(228_ui32));
			Assert::AreEqual(228, Object::GetHashCode(228_ui64));
			Assert::AreEqual(532, Object::GetHashCode(Elysium::Core::String(u8"hello")));
		}

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
			AssertExtended::AreEqual(u8"", Object::ToString(24.38f));
			AssertExtended::AreEqual(u8"", Object::ToString(24.38));
			AssertExtended::AreEqual(u8"hello", Object::ToString(Elysium::Core::String(u8"hello")));
		}
	};
}
