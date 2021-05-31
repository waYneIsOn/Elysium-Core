#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/TypeTraits.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core::Template;

namespace UnitTests::Core::Template
{
	TEST_CLASS(TypeTraitTest)
	{
	public:
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

			Assert::IsFalse(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t*>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t&>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t&>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t&&>());
		}
	};
}
