#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/TypeTraits.hpp"
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core::Template;

namespace UnitTests::Core::Template
{
	TEST_CLASS(TypeTraitTest)
	{
	public:
		TEST_METHOD(CompareToSTL)
		{
			Assert::AreEqual(std::is_null_pointer<Elysium::Core::uint8_t>::value, Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t>::Value);
			//Assert::AreEqual(std::is_null_pointer<const Elysium::Core::uint8_t>::value, Elysium::Core::Template::IsNullPointer<const Elysium::Core::uint8_t>::Value);
			Assert::AreEqual(std::is_null_pointer<nullptr_t>::value, Elysium::Core::Template::IsNullPointer<nullptr_t>::Value);
			//Assert::AreEqual(std::is_null_pointer<const nullptr_t>::value, Elysium::Core::Template::IsNullPointer<const nullptr_t>::Value);
		}

		TEST_METHOD(IsAnyOf)
		{
			Assert::Fail();
		}

		TEST_METHOD(IsNullPointer)
		{
			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t>());

			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t*>());

			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t&>());

			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::IsNullPointer<nullptr_t>());

			//Assert::IsTrue(Elysium::Core::Template::IsNullPointer<const nullptr_t>());
		}

		TEST_METHOD(IsPointer)
		{
			Assert::IsFalse(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t>());
			
			Assert::IsFalse(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t&>());
			
			Assert::IsFalse(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t*>());

			Assert::IsTrue(Elysium::Core::Template::IsPointer<const Elysium::Core::uint8_t*>());
		}

		TEST_METHOD(IsReference)
		{
			Assert::IsFalse(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t>());

			Assert::IsFalse(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t>());

			Assert::IsFalse(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t*>());

			Assert::IsFalse(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t*>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t&>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t&>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t&&>());
		}

		TEST_METHOD(IsSame)
		{
			Assert::IsFalse(Elysium::Core::Template::IsSame<Elysium::Core::uint8_t, char>());

			Assert::IsTrue(Elysium::Core::Template::IsSame<Elysium::Core::uint8_t, unsigned char>());

			Assert::IsTrue(Elysium::Core::Template::IsSame<void, void>());
		}

		TEST_METHOD(IsVoid)
		{
			Assert::IsFalse(Elysium::Core::Template::IsVoid<Elysium::Core::uint8_t>());

			Assert::IsFalse(Elysium::Core::Template::IsVoid<Elysium::Core::uint8_t*>());

			Assert::IsFalse(Elysium::Core::Template::IsVoid<Elysium::Core::uint8_t&>());

			Assert::IsFalse(Elysium::Core::Template::IsVoid<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::IsVoid<void>());
		}
	};
}
