#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/TypeTraits.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/FixedSizeHeapArray.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core::Template::TypeTraits;

namespace UnitTests::Core::Template::TypeTraits
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

	TEST_CLASS(TypeTraitTests)
	{
	public:
		TEST_METHOD(CompareToSTL)
		{
			Assert::AreEqual(std::is_null_pointer<Elysium::Core::uint8_t>::value, Elysium::Core::Template::TypeTraits::IsNullPointer<Elysium::Core::uint8_t>::Value);
			Assert::AreEqual(std::is_null_pointer<const Elysium::Core::uint8_t>::value, Elysium::Core::Template::TypeTraits::IsNullPointer<const Elysium::Core::uint8_t>::Value);
			Assert::AreEqual(std::is_null_pointer<std::nullptr_t>::value, Elysium::Core::Template::TypeTraits::IsNullPointer<std::nullptr_t>::Value);
			Assert::AreEqual(std::is_null_pointer<const nullptr_t>::value, Elysium::Core::Template::TypeTraits::IsNullPointer<const std::nullptr_t>::Value);
		}

		TEST_METHOD(IsAnyOf)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsAnyOfValue<char, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsAnyOfValue<int64_t, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsAnyOfValue<char*, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsAnyOfValue<bool&, unsigned char, bool&, uint8_t, int32_t, char*, int64_t>);
		}

		TEST_METHOD(IsArray)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsArray<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsArray<char*>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsArray<char&>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsArray<EnumerationClass>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsArray<Colour>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsArray<TypeTraitTests>::Value);

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsArray<char[]>::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsArray<char[2]>::Value);
			//Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsArray<Elysium::Core::Template::Collections::FixedSizeHeapArray<char, 3>>::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsArray<Elysium::Core::Collections::Template::Array<char>>::Value);
		}

		TEST_METHOD(IsClass)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsClass<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsClass<char*>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsClass<char&>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsClass<EnumerationClass>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsClass<Colour>::Value);

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsClass<TypeTraitTests>::Value);
		}

		TEST_METHOD(IsEnumeration)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsEnumeration<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsEnumeration<char*>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsEnumeration<char&>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsEnumeration<TypeTraitTests>::Value);

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsEnumeration<EnumerationClass>::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsEnumeration<Colour>::Value);
		}

		TEST_METHOD(IsFunction)
		{
			TypeTraitTests Instance = TypeTraitTests();

			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<char>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<UnitTests::Core::Template::TypeTraits::TypeTraitTests>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<decltype(&UnitTests::Core::Template::TypeTraits::TypeTraitTests::IsFunction)>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<decltype(&UnitTests::Core::Template::TypeTraits::TypeTraitTests::StaticMethod)>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<decltype(&UnitTests::Core::Template::TypeTraits::TypeTraitTests::OtherStaticMethod)>::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<decltype(&UnitTests::Core::Template::TypeTraits::TypeTraitTests::InstanceMethod)>::Value);
			//Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<decltype(&Instance.InstanceMethod)>::Value);

			//Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsFunction<decltype(UnitTests::Core::Template::TypeTraits::TypeTraitTests::IsFunction)>::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsFunction<decltype(UnitTests::Core::Template::TypeTraits::TypeTraitTests::StaticMethod)>::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsFunction<decltype(UnitTests::Core::Template::TypeTraits::TypeTraitTests::OtherStaticMethod)>::Value);
			//Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsFunction<decltype(UnitTests::Core::Template::TypeTraits::TypeTraitTests::InstanceMethod)>::Value);

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsFunction<decltype(UnitTests::Core::Template::TypeTraits::SomeFunction)>::Value);
		}

		TEST_METHOD(IsNullPointer)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsNullPointer<Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsNullPointer<Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsNullPointer<Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsNullPointer<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsNullPointer<std::nullptr_t>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsNullPointer<const std::nullptr_t>());
		}

		TEST_METHOD(IsPointer)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsPointer<Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsPointer<Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsPointer<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsPointer<Elysium::Core::uint8_t*>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsPointer<const Elysium::Core::uint8_t*>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsPointer<volatile Elysium::Core::uint8_t*>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsPointer<const volatile Elysium::Core::uint8_t*>());
		}

		TEST_METHOD(IsReference)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<const Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<volatile Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<const volatile Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<const Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<volatile Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsReference<const volatile Elysium::Core::uint8_t*>());

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<const Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<volatile Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<const volatile Elysium::Core::uint8_t&>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<const Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<volatile Elysium::Core::uint8_t&&>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsReference<const volatile Elysium::Core::uint8_t&&>());
		}

		TEST_METHOD(IsSame)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsSame<Elysium::Core::uint8_t, char>());

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsSame<Elysium::Core::uint8_t, unsigned char>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsSame<void, void>());
		}

		TEST_METHOD(IsVoid)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsVoid<Elysium::Core::uint8_t>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsVoid<Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsVoid<Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsVoid<Elysium::Core::uint8_t&&>());

			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsVoid<void>());
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
