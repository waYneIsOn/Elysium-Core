#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/TypeTraits.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/FixedSizeHeapArray.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core::Template::TypeTraits;

namespace UnitTests::Core::Template::TypeTraits
{
	void SomeFunction() { }

	int SomeOtherFunction()
	{
		return 0;
	}

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

	struct SomeStruct
	{ };

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

		TEST_METHOD(InvokeResult)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::InvokeResult<TypeTraitTests>::IsInvokable::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::InvokeResult<EnumerationClass>::IsInvokable::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::InvokeResult<Colour>::IsInvokable::Value);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::InvokeResult<SomeStruct>::IsInvokable::Value);
			/*
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::InvokeResult<decltype(SomeFunction())>::IsInvokable::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::InvokeResult<decltype(SomeOtherFunction())>::IsInvokable::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::InvokeResult<decltype(TypeTraitTests::StaticMethod())>::IsInvokable::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::InvokeResult<decltype(TypeTraitTests::OtherStaticMethod())>::IsInvokable::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::InvokeResult<decltype(TypeTraitTests::InstanceMethod())>::IsInvokable::Value);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::InvokeResult<decltype(TypeTraitTests::InstanceMethodReturningInt())>::IsInvokable::Value);
			*/





			constexpr const bool xxxxxxxxxxxxxxx1 = std::invoke_result<TypeTraitTests>::_Is_invocable::value;
			constexpr const bool xxxxxxxxxxxxxxx3 = std::invoke_result<TypeTraitTests>::_Is_nothrow_invocable::value;





			/*
			decltype(TypeTraitTests::InstanceMethodReturningInt()) Test;
			Test = 25;1
			*/
			/*
			constexpr const bool StaticMethodReturnTypeInteger = Elysium::Core::Template::TypeTraits::IsSameValue<int,
				Elysium::Core::Template::TypeTraits::InvokeResultType<decltype(TypeTraitTests::OtherStaticMethod())>>;
			constexpr const bool StaticMethodReturnTypeVoid = Elysium::Core::Template::TypeTraits::IsSameValue<void,
				Elysium::Core::Template::TypeTraits::InvokeResultType<decltype(TypeTraitTests::StaticMethod())>>;
			constexpr const bool InstanceMethodReturnTypeInteger = Elysium::Core::Template::TypeTraits::IsSameValue<int,
				Elysium::Core::Template::TypeTraits::InvokeResultType<decltype(TypeTraitTests::InstanceMethodReturningInt())>>;
			constexpr const bool InstanceMethodReturnTypeVoid = Elysium::Core::Template::TypeTraits::IsSameValue<void,
				Elysium::Core::Template::TypeTraits::InvokeResultType<decltype(TypeTraitTests::InstanceMethod())>>;
			constexpr const bool FunctionReturnTypeInteger = Elysium::Core::Template::TypeTraits::IsSameValue<int,
				Elysium::Core::Template::TypeTraits::InvokeResultType<decltype(SomeOtherFunction())>>;
			constexpr const bool FunctionReturnTypeVoid = Elysium::Core::Template::TypeTraits::IsSameValue<void,
				Elysium::Core::Template::TypeTraits::InvokeResultType<decltype(SomeFunction())>>;

			Assert::IsTrue(StaticMethodReturnTypeInteger);
			Assert::IsTrue(StaticMethodReturnTypeVoid);
			Assert::IsTrue(InstanceMethodReturnTypeInteger);
			Assert::IsTrue(InstanceMethodReturnTypeVoid);
			Assert::IsTrue(FunctionReturnTypeInteger);
			Assert::IsTrue(FunctionReturnTypeVoid);
			*/





			/*
			constexpr const bool InstanceMethodReturnTypeInteger2 = Elysium::Core::Template::TypeTraits::IsSameValue<int,
				Elysium::Core::Template::TypeTraits::InvokeResultType<decltype(TypeTraitTests::InstanceMethodReturningGivenInt), int>>;
			Assert::IsTrue(InstanceMethodReturnTypeInteger2);
			*/
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
			//Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsArray<Elysium::Core::Collections::Template::Array<char>>::Value);
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

		TEST_METHOD(IsMemberFunctionPointer)
		{
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<TypeTraitTests>);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<decltype(SomeFunction)>);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<decltype(&SomeFunction)>);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<decltype(StaticMethod)>);
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<decltype(&StaticMethod)>);

			//Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<&TypeTraitTests::InstanceMethod>);
			//Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<decltype(TypeTraitTests::InstanceMethod)>);
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsMemberFunctionPointerValue<decltype(&TypeTraitTests::InstanceMethod)>);
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

		TEST_METHOD(IsValue)
		{
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsValue<Elysium::Core::uint8_t>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsValue<const Elysium::Core::uint8_t>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsValue<volatile Elysium::Core::uint8_t>());
			Assert::IsTrue(Elysium::Core::Template::TypeTraits::IsValue<const volatile Elysium::Core::uint8_t>());

			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<const Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<volatile Elysium::Core::uint8_t&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<const volatile Elysium::Core::uint8_t&>());

			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<Elysium::Core::uint8_t&&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<const Elysium::Core::uint8_t&&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<volatile Elysium::Core::uint8_t&&>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<const volatile Elysium::Core::uint8_t&&>());

			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<const Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<volatile Elysium::Core::uint8_t*>());
			Assert::IsFalse(Elysium::Core::Template::TypeTraits::IsValue<const volatile Elysium::Core::uint8_t*>());
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

		int InstanceMethodReturningInt()
		{
			return 0;
		}

		int InstanceMethodReturningGivenInt(int Input)
		{
			return Input;
		}
	};
}
