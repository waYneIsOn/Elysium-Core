#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/TypeTraits.hpp"
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core::Template;

namespace UnitTests::Core::Template
{
	void SomeFunction() { }

	enum class EnumerationClass
	{
		Unknown = -1,
		A = 0,
		B = 1,
	};

	enum Colour 
	{
		Red,
		Green,
		Blue
	};

	TEST_CLASS(TypeTraitTest)
	{
	public:
		TEST_METHOD(CompareToSTL)
		{
			Assert::AreEqual(std::is_null_pointer<Elysium::Core::uint8_t>::value, Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t>::Value);
			Assert::AreEqual(std::is_null_pointer<const Elysium::Core::uint8_t>::value, Elysium::Core::Template::IsNullPointer<const Elysium::Core::uint8_t>::Value);
			Assert::AreEqual(std::is_null_pointer<std::nullptr_t>::value, Elysium::Core::Template::IsNullPointer<std::nullptr_t>::Value);
			Assert::AreEqual(std::is_null_pointer<const nullptr_t>::value, Elysium::Core::Template::IsNullPointer<const std::nullptr_t>::Value);
		}

		TEST_METHOD(IsAnyOf)
		{
			Assert::IsTrue(Elysium::Core::Template::IsAnyOfValue<int64_t, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);
			Assert::IsTrue(Elysium::Core::Template::IsAnyOfValue<char*, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);
			Assert::IsTrue(Elysium::Core::Template::IsAnyOfValue<bool&, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);
			Assert::IsFalse(Elysium::Core::Template::IsAnyOfValue<char, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);
		}

		TEST_METHOD(IsArray)
		{
			Assert::IsFalse(Elysium::Core::Template::IsArray<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsArray<char*>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsArray<char&>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsArray<char[]>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsArray<char[2]>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsArray<Elysium::Core::Collections::Template::Array<char>>::Value);
		}
		
		TEST_METHOD(IsClass)
		{
			Assert::IsFalse(Elysium::Core::Template::IsClass<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsClass<EnumerationClass>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsClass<Colour>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsClass<TypeTraitTest>::Value);			
		}

		TEST_METHOD(IsEnumeration)
		{
			Assert::IsFalse(Elysium::Core::Template::IsEnumeration<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsEnumeration<TypeTraitTest>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsEnumeration<EnumerationClass>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsEnumeration<Colour>::Value);
		}

		TEST_METHOD(IsFunction)
		{
			TypeTraitTest Instance = TypeTraitTest();

			Assert::IsFalse(Elysium::Core::Template::IsFunction<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsFunction<UnitTests::Core::Template::TypeTraitTest>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsFunction<decltype(&UnitTests::Core::Template::TypeTraitTest::IsFunction)>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsFunction<decltype(&UnitTests::Core::Template::TypeTraitTest::StaticMethod)>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsFunction<decltype(&UnitTests::Core::Template::TypeTraitTest::OtherStaticMethod)>::Value);
			Assert::IsFalse(Elysium::Core::Template::IsFunction<decltype(&UnitTests::Core::Template::TypeTraitTest::InstanceMethod)>::Value);
			//Assert::IsFalse(Elysium::Core::Template::IsFunction<decltype(&Instance.InstanceMethod)>::Value);

			//Assert::IsFalse(Elysium::Core::Template::IsFunction<decltype(UnitTests::Core::Template::TypeTraitTest::IsFunction)>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsFunction<decltype(UnitTests::Core::Template::TypeTraitTest::StaticMethod)>::Value);
			Assert::IsTrue(Elysium::Core::Template::IsFunction<decltype(UnitTests::Core::Template::TypeTraitTest::OtherStaticMethod)>::Value);
			//Assert::IsTrue(Elysium::Core::Template::IsFunction<decltype(UnitTests::Core::Template::TypeTraitTest::InstanceMethod)>::Value);

			Assert::IsTrue(Elysium::Core::Template::IsFunction<decltype(UnitTests::Core::Template::SomeFunction)>::Value);
		}

		TEST_METHOD(IsNullPointer)
		{
			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::IsNullPointer<Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::IsNullPointer<std::nullptr_t>());
			Assert::IsTrue(Elysium::Core::Template::IsNullPointer<const std::nullptr_t>());
		}

		TEST_METHOD(IsPointer)
		{
			Assert::IsFalse(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::IsPointer<Elysium::Core::uint8_t*>());
			Assert::IsTrue(Elysium::Core::Template::IsPointer<const Elysium::Core::uint8_t*>());
			Assert::IsTrue(Elysium::Core::Template::IsPointer<volatile Elysium::Core::uint8_t*>());
			Assert::IsTrue(Elysium::Core::Template::IsPointer<const volatile Elysium::Core::uint8_t*>());
		}

		TEST_METHOD(IsReference)
		{
			Assert::IsFalse(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::IsReference<volatile Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::IsReference<const volatile Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::IsReference<volatile Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::IsReference<const volatile Elysium::Core::uint8_t*>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<volatile Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<const volatile Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<const Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<volatile Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::IsReference<const volatile Elysium::Core::uint8_t&&>());
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

		static void StaticMethod()
		{ }

		static int OtherStaticMethod()
		{
			return 0;
		}

		void InstanceMethod()
		{ }
	};
}
