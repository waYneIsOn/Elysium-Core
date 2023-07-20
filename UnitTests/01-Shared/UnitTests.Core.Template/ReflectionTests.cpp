#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IsSame.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/UnderlyingType.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/RunTimeTypeInformation/Enumeration.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::TypeTraits;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

	enum class SomeInt8EnumClass : ::Template::System::int8_t
	{
		A = -1,
		B = 1
	};

	TEST_CLASS(RunTimeTypeInformation)
	{
	public:
		TEST_METHOD(ReflectEnumTests)
		{
			Assert::IsTrue(IsSameValue<::Template::System::int32_t, UnderlyingTypeType<SomeEnum>>);
			Assert::IsTrue(IsSameValue<::Template::System::int32_t, UnderlyingTypeType<SomeEnumClass>>);

			Assert::IsTrue(IsSameValue<::Template::System::uint8_t, UnderlyingTypeType<SomeUInt8EnumClass>>);
			Assert::IsTrue(IsSameValue<::Template::System::int8_t, UnderlyingTypeType<SomeInt8EnumClass>>);

			Elysium::Core::Template::Text::String<char8_t> EnumFullName =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::ToString();
			Elysium::Core::Template::Text::String<char8_t> EnumValue =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::GetName<SomeEnum::Sunday>();
			Elysium::Core::Template::Text::String<char8_t> EnumValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeEnum>::GetValues();

			Elysium::Core::Template::Text::String<char8_t> EnumClassFullName =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::ToString();
			Elysium::Core::Template::Text::String<char8_t> EnumClassValue =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::GetName<SomeUInt8EnumClass::A>();
			Elysium::Core::Template::Text::String<char8_t> EnumClassValues =
				Elysium::Core::Template::RunTimeTypeInformation::Enumeration<SomeUInt8EnumClass>::GetValues();

			bool bla = false;
		}
	};
}
