#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
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
			Utf8String EmptyString = Activator::CreateInstance<Utf8String>();
			Assert::AreEqual(0_ui64, EmptyString.GetLength());
			Assert::AreEqual(23_ui64, EmptyString.GetCapacity());

			Utf8String CharString = Activator::CreateInstance<Utf8String, Utf8String::ConstCharacterPointer>(u8"bla");
			Assert::AreEqual(3_ui64, CharString.GetLength());
			Assert::AreEqual(23_ui64, CharString.GetCapacity());

			Utf8String LengthString = Activator::CreateInstance<Utf8String, const Elysium::Core::size>(27);
			const Elysium::Core::size bla = LengthString.GetLength();
			const Elysium::Core::size bla1 = LengthString.GetCapacity();
			Assert::AreEqual(27_ui64, LengthString.GetLength());
			Assert::AreEqual(27_ui64, LengthString.GetCapacity());
		}
	};
}