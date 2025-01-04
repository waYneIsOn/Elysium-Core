#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IsSame.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IsScopedEnumeration.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/UnderlyingType.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/RunTimeTypeInformation/Enumeration.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::TypeTraits;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

enum GlobalEnum
{
	A = -1,
	Sunday = 0,
	B = 1,
};

enum class GlobalSomeEnumClass
{
	A = -1,
	B = 1,
};

namespace UnitTests::Core::Template::Reflection
{
	enum SomeEnum
	{
		A = -1,
		Sunday = 0,
		B = 1,
	};
	
	enum class SomeEnumClass
	{
		A = -1,
		B = 1,
	};

	enum class SomeUInt8EnumClass : ::Template::System::uint8_t
	{
		A = -1,
		B = 1
	};

	enum class SomeEmtpyUInt8EnumClass : ::Template::System::uint8_t
	{ };

	enum class SomeInt8EnumClass : ::Template::System::int8_t
	{
		A = -1,
		B = 1
	};

	enum class SomeInt16EnumClass : ::Template::System::int16_t
	{
		A = 345,
		B = 465,
		C = -21,
		D = 23904
	};

	enum struct SomeInt32EnumStruct : ::Template::System::int32_t
	{
		A = 345,
		B = 465,
		C = -21,
		D = 23904
	};

	TEST_CLASS(RunTimeTypeInformation)
	{
	public:
		TEST_METHOD(EnumUnderlyingType)
		{
			Assert::IsTrue(IsSameValue<::Template::System::int32_t, UnderlyingTypeType<GlobalEnum>>);
			Assert::IsTrue(IsSameValue<::Template::System::int32_t, UnderlyingTypeType<GlobalSomeEnumClass>>);
			Assert::IsTrue(IsSameValue<::Template::System::int32_t, UnderlyingTypeType<SomeEnum>>);
			Assert::IsTrue(IsSameValue<::Template::System::int32_t, UnderlyingTypeType<SomeEnumClass>>);
			Assert::IsTrue(IsSameValue<::Template::System::uint8_t, UnderlyingTypeType<SomeUInt8EnumClass>>);
			Assert::IsTrue(IsSameValue<::Template::System::int8_t, UnderlyingTypeType<SomeInt8EnumClass>>);
			Assert::IsTrue(IsSameValue<::Template::System::int16_t, UnderlyingTypeType<SomeInt16EnumClass>>);
			Assert::IsTrue(IsSameValue<::Template::System::int32_t, UnderlyingTypeType<SomeInt32EnumStruct>>);
		}

		TEST_METHOD(EnumIsScoped)
		{
			Assert::IsFalse(IsScopedEnumeration<GlobalEnum>::Value);
			Assert::IsTrue(IsScopedEnumeration<GlobalSomeEnumClass>::Value);
			Assert::IsFalse(IsScopedEnumeration<SomeEnum>::Value);
			Assert::IsTrue(IsScopedEnumeration<SomeEnumClass>::Value);
			Assert::IsTrue(IsScopedEnumeration<SomeUInt8EnumClass>::Value);
			Assert::IsTrue(IsScopedEnumeration<SomeInt8EnumClass>::Value);
			Assert::IsTrue(IsScopedEnumeration<SomeInt16EnumClass>::Value);
			Assert::IsTrue(IsScopedEnumeration<SomeInt32EnumStruct>::Value);
		}

		TEST_METHOD(EnumIsFlag)
		{
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalEnum>::IsFlag());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalSomeEnumClass>::IsFlag());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::IsFlag());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnumClass>::IsFlag());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::IsFlag());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::IsFlag());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt16EnumClass>::IsFlag());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt32EnumStruct>::IsFlag());
		}

		TEST_METHOD(EnumGetFullNames)
		{
			AssertExtended::AreEqual(u8"GlobalEnum",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalEnum>::GetFullName()[0]);
			AssertExtended::AreEqual(u8"GlobalSomeEnumClass",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalSomeEnumClass>::GetFullName()[0]);
			AssertExtended::AreEqual(u8"UnitTests::Core::Template::Reflection::SomeEnum",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::GetFullName()[0]);
			AssertExtended::AreEqual(u8"UnitTests::Core::Template::Reflection::SomeEnumClass",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnumClass>::GetFullName()[0]);
			
			AssertExtended::AreEqual(u8"UnitTests::Core::Template::Reflection::SomeUInt8EnumClass",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::GetFullName()[0]);
			AssertExtended::AreEqual(u8"UnitTests::Core::Template::Reflection::SomeInt8EnumClass",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::GetFullName()[0]);
			AssertExtended::AreEqual(u8"UnitTests::Core::Template::Reflection::SomeInt16EnumClass",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt16EnumClass>::GetFullName()[0]);
			
			AssertExtended::AreEqual(u8"UnitTests::Core::Template::Reflection::SomeInt32EnumStruct",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt32EnumStruct>::GetFullName()[0]);
		}

		TEST_METHOD(EnumIsDefinedValue)
		{
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalEnum>::IsDefinedValue<GlobalEnum::A>());
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalSomeEnumClass>::IsDefinedValue<GlobalSomeEnumClass::A>());
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::IsDefinedValue<SomeEnum::A>());
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnumClass>::IsDefinedValue<SomeEnumClass::A>());
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::IsDefinedValue<SomeUInt8EnumClass::A>());
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::IsDefinedValue<SomeInt8EnumClass::A>());
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt16EnumClass>::IsDefinedValue<SomeInt16EnumClass::A>());
			Assert::IsTrue(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt32EnumStruct>::IsDefinedValue<SomeInt32EnumStruct::A>());

			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalEnum>::IsDefinedValue<static_cast<GlobalEnum>(123)>());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalSomeEnumClass>::IsDefinedValue<static_cast<GlobalSomeEnumClass>(123)>());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::IsDefinedValue<static_cast<SomeEnum>(123)>());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnumClass>::IsDefinedValue<static_cast<SomeEnumClass>(123)>());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::IsDefinedValue<static_cast<SomeUInt8EnumClass>(123)>());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::IsDefinedValue<static_cast<SomeInt8EnumClass>(123)>());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt16EnumClass>::IsDefinedValue<static_cast<SomeInt16EnumClass>(123)>());
			Assert::IsFalse(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt32EnumStruct>::IsDefinedValue<static_cast<SomeInt32EnumStruct>(123)>());
		}

		TEST_METHOD(EnumGetNameValues)
		{
			AssertExtended::AreEqual(u8"0x7b",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalEnum>::GetNamedValue<static_cast<GlobalEnum>(123)>()[0]);
			AssertExtended::AreEqual(u8"0x7b",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalSomeEnumClass>::GetNamedValue<static_cast<GlobalSomeEnumClass>(123)>()[0]);
			AssertExtended::AreEqual(u8"0x7b",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::GetNamedValue<static_cast<SomeEnum>(123)>()[0]);
			AssertExtended::AreEqual(u8"0x7b",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnumClass>::GetNamedValue<static_cast<SomeEnumClass>(123)>()[0]);

			AssertExtended::AreEqual(u8"Sunday",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalEnum>::GetNamedValue<GlobalEnum::Sunday>()[0]);
			AssertExtended::AreEqual(u8"A",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<GlobalSomeEnumClass>::GetNamedValue<GlobalSomeEnumClass::A>()[0]);
			AssertExtended::AreEqual(u8"Sunday",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::GetNamedValue<SomeEnum::Sunday>()[0]);
			AssertExtended::AreEqual(u8"B",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnumClass>::GetNamedValue<SomeEnumClass::B>()[0]);
			
			AssertExtended::AreEqual(u8"B",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::GetNamedValue<SomeUInt8EnumClass::B>()[0]);
			AssertExtended::AreEqual(u8"B",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::GetNamedValue<SomeInt8EnumClass::B>()[0]);
			AssertExtended::AreEqual(u8"B",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt16EnumClass>::GetNamedValue<SomeInt16EnumClass::B>()[0]);
			
			AssertExtended::AreEqual(u8"B",
				&Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt32EnumStruct>::GetNamedValue<SomeInt32EnumStruct::B>()[0]);
		}

		TEST_METHOD(EnumGetDefinedValues)
		{
			// GlobalEnum (int32_t doesn't currently work - too large)
			// GlobalSomeEnumClass (int32_t doesn't currently work - too large)
			// SomeEnum (int32_t doesn't currently work - too large)
			// SomeEnumClass (int32_t doesn't currently work - too large)
			
			// SomeUInt8EnumClass
			const ::Template::Container::Vector<SomeUInt8EnumClass> SomeUInt8EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::GetDefinedValues();
			Assert::AreEqual(2_ui64, SomeUInt8EnumClassValues.GetLength());

			Assert::AreEqual(static_cast<::Template::System::uint8_t>(SomeUInt8EnumClass::B), 
				static_cast<::Template::System::uint8_t>(SomeUInt8EnumClassValues[0]));
			Assert::AreEqual(static_cast<::Template::System::uint8_t>(SomeUInt8EnumClass::A),
				static_cast<::Template::System::uint8_t>(SomeUInt8EnumClassValues[1]));
			
			// SomeEmtpyUInt8EnumClass
			const ::Template::Container::Vector<SomeEmtpyUInt8EnumClass> SomeEmtpyUint8EnumValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEmtpyUInt8EnumClass>::GetDefinedValues();
			Assert::AreEqual(0_ui64, SomeEmtpyUint8EnumValues.GetLength());
						
			// SomeInt8EnumClass
			const ::Template::Container::Vector<SomeInt8EnumClass> SomeInt8EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::GetDefinedValues();
			Assert::AreEqual(2_ui64, SomeInt8EnumClassValues.GetLength());

			Assert::AreEqual(static_cast<::Template::System::int8_t>(SomeInt8EnumClass::B),
				static_cast<::Template::System::int8_t>(SomeInt8EnumClassValues[0]));
			Assert::AreEqual(static_cast<::Template::System::int8_t>(SomeInt8EnumClass::A),
				static_cast<::Template::System::int8_t>(SomeInt8EnumClassValues[1]));
			
			/*
			// SomeInt16EnumClass
			const ::Template::Container::Vector<SomeInt16EnumClass> SomeInt16EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt16EnumClass>::GetDefinedValues();
			Assert::AreEqual(4_ui64, SomeInt16EnumClassValues.GetLength());
			*/
			// SomeInt32EnumStruct (int32_t doesn't currently work - too large)
		}

		TEST_METHOD(EnumGetUnderlyingValues)
		{
			// GlobalEnum (int32_t doesn't currently work - too large)
			// GlobalSomeEnumClass (int32_t doesn't currently work - too large)
			// SomeEnum (int32_t doesn't currently work - too large)
			// SomeEnumClass (int32_t doesn't currently work - too large)

			// SomeUInt8EnumClass
			const ::Template::Container::Vector<::Template::System::uint8_t> SomeUInt8EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::GetUnderlyingValues();
			Assert::AreEqual(2_ui64, SomeUInt8EnumClassValues.GetLength());
			
			Assert::AreEqual(static_cast<::Template::System::uint8_t>(SomeUInt8EnumClass::B),
				static_cast<::Template::System::uint8_t>(SomeUInt8EnumClassValues[0]));
			Assert::AreEqual(static_cast<::Template::System::uint8_t>(SomeUInt8EnumClass::A),
				static_cast<::Template::System::uint8_t>(SomeUInt8EnumClassValues[1]));

			// SomeEmtpyUInt8EnumClass
			const ::Template::Container::Vector<::Template::System::uint8_t> SomeEmtpyUint8EnumValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEmtpyUInt8EnumClass>::GetUnderlyingValues();
			Assert::AreEqual(0_ui64, SomeEmtpyUint8EnumValues.GetLength());

			// SomeInt8EnumClass
			const ::Template::Container::Vector<::Template::System::int8_t> SomeInt8EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::GetUnderlyingValues();
			Assert::AreEqual(2_ui64, SomeInt8EnumClassValues.GetLength());

			Assert::AreEqual(static_cast<::Template::System::int8_t>(SomeInt8EnumClass::B),
				static_cast<::Template::System::int8_t>(SomeInt8EnumClassValues[0]));
			Assert::AreEqual(static_cast<::Template::System::int8_t>(SomeInt8EnumClass::A),
				static_cast<::Template::System::int8_t>(SomeInt8EnumClassValues[1]));

			// SomeInt16EnumClass (int16_t doesn't currently work - too large)
			// SomeInt32EnumStruct (int32_t doesn't currently work - too large)
		}

		TEST_METHOD(EnumGetNamedValues)
		{
			// GlobalEnum (int32_t doesn't currently work - too large)
			// GlobalSomeEnumClass (int32_t doesn't currently work - too large)
			// SomeEnum (int32_t doesn't currently work - too large)
			// SomeEnumClass (int32_t doesn't currently work - too large)

			// SomeUInt8EnumClass
			const ::Template::Container::Vector<::Template::Text::String<char8_t>> SomeUInt8EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::GetNamedValues();
			Assert::AreEqual(2_ui64, SomeUInt8EnumClassValues.GetLength());
			/*
			Assert::AreEqual(static_cast<::Template::System::uint8_t>(SomeUInt8EnumClass::B),
				static_cast<::Template::System::uint8_t>(SomeUInt8EnumClassValues[0]));
			Assert::AreEqual(static_cast<::Template::System::uint8_t>(SomeUInt8EnumClass::A),
				static_cast<::Template::System::uint8_t>(SomeUInt8EnumClassValues[1]));
			*/
			// SomeEmtpyUInt8EnumClass
			const ::Template::Container::Vector<::Template::Text::String<char8_t>> SomeEmtpyUint8EnumValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEmtpyUInt8EnumClass>::GetNamedValues();
			Assert::AreEqual(0_ui64, SomeEmtpyUint8EnumValues.GetLength());

			// SomeInt8EnumClass
			const ::Template::Container::Vector<::Template::Text::String<char8_t>> SomeInt8EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeInt8EnumClass>::GetNamedValues();
			Assert::AreEqual(2_ui64, SomeInt8EnumClassValues.GetLength());
			/*
			Assert::AreEqual(static_cast<::Template::System::int8_t>(SomeInt8EnumClass::B),
				static_cast<::Template::System::int8_t>(SomeInt8EnumClassValues[0]));
			Assert::AreEqual(static_cast<::Template::System::int8_t>(SomeInt8EnumClass::A),
				static_cast<::Template::System::int8_t>(SomeInt8EnumClassValues[1]));
			*/
			// SomeInt16EnumClass (int16_t doesn't currently work - too large)
			// SomeInt32EnumStruct (int32_t doesn't currently work - too large)
		}
	};
}
