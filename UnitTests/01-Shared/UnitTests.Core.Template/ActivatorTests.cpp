#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/AppDomain.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Activator.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Reflection;
using namespace Elysium::Core::Template::Memory;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Memory
{
	class MyClass
	{
		friend class Activator;
	private:
		MyClass()
			: Value(5448)
		{ }
	public:
		MyClass(const Elysium::Core::size InputValue)
			: Value(InputValue)
		{ }

		~MyClass()
		{ }
	public:
		Elysium::Core::size Value;
	};

	TEST_CLASS(ActivatorTests)
	{
	public:
		TEST_METHOD(MyClassTests)
		{
			MyClass PubliclyConstructed = Activator::CreateInstance<MyClass, size>(27);
			Assert::AreEqual(27_ui64, PubliclyConstructed.Value);

			MyClass PrivatelyConstructed = Activator::CreateInstance<MyClass>();
			Assert::AreEqual(5448_ui64, PrivatelyConstructed.Value);
		}

		TEST_METHOD(StringTests)
		{
			String EmptyString = Activator::CreateInstance<String>();
			Assert::AreEqual(0_ui64, EmptyString.GetLength());

			String CharString = Activator::CreateInstance<String, String::ConstCharacterPointer>(u8"bla");
			Assert::AreEqual(3_ui64, CharString.GetLength());

			String LengthString = Activator::CreateInstance<String, const Elysium::Core::size>(27);
			Assert::AreEqual(27_ui64, LengthString.GetLength());
		}
	};
}