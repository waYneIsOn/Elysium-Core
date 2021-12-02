#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/AddLeftValueReference.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Object.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/String.hpp"

using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Elysium::Core::Template::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(ObjectTests)
	{
	public:
		TEST_METHOD(GetHashCodes)
		{
			constexpr const Elysium::Core::uint8_t KeyUInt8 = 25_ui8;
			constexpr const Elysium::Core::uint16_t KeyUInt16 = 439_ui8;
			constexpr const Elysium::Core::uint32_t KeyUInt32 = 53728_ui8;
			constexpr const Elysium::Core::uint64_t KeyUInt64 = 51671904_ui8;

			constexpr const Elysium::Core::int8_t KeyInt8 = -25_i8;
			constexpr const Elysium::Core::int16_t KeyInt16 = -439_i8;
			constexpr const Elysium::Core::int32_t KeyInt32 = -53728_i8;
			constexpr const Elysium::Core::int64_t KeyInt64 = -51671904_i8;

			const String KeyString = "bla";
			const WideString KeyWideString = L"bla";
			const Utf8String KeyUtf8String = u8"bla";
			const Utf16String KeyUtf16String = u"bla";
			const Utf32String KeyUtf32String = U"bla";
			
			// specialization: unsigned integer
			constexpr Elysium::Core::size HashCodeUInt8 = Object::GetHashCode(KeyUInt8);
			constexpr Elysium::Core::size HashCodeUInt16 = Object::GetHashCode(KeyUInt16);
			constexpr Elysium::Core::size HashCodeUInt32 = Object::GetHashCode(KeyUInt32);
			constexpr Elysium::Core::size HashCodeUInt64 = Object::GetHashCode(KeyUInt64);

			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt8), HashCodeUInt8);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt16), HashCodeUInt16);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt32), HashCodeUInt32);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt64), HashCodeUInt64);
			
			// specialization: signed integer
			constexpr Elysium::Core::size HashCodeInt8 = Object::GetHashCode(KeyInt8);
			constexpr Elysium::Core::size HashCodeInt16 = Object::GetHashCode(KeyInt16);
			constexpr Elysium::Core::size HashCodeInt32 = Object::GetHashCode(KeyInt32);
			constexpr Elysium::Core::size HashCodeInt64 = Object::GetHashCode(KeyInt64);

			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt8), HashCodeInt8);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt16), HashCodeInt16);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt32), HashCodeInt32);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt64), HashCodeInt64);
			
			// specialization: has method "Elysium::Core::size GetHashCode()"
			Elysium::Core::size HashCodeString = Object::GetHashCode(KeyString);
			Elysium::Core::size HashCodeWideString = Object::GetHashCode(KeyWideString);
			Elysium::Core::size HashCodeUtf8String = Object::GetHashCode(KeyUtf8String);
			Elysium::Core::size HashCodeUtf16String = Object::GetHashCode(KeyUtf16String);
			Elysium::Core::size HashCodeUtf32String = Object::GetHashCode(KeyUtf32String);

			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeString);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeWideString);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeUtf8String);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeUtf16String);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeUtf32String);

			// specialization: pointer
			Elysium::Core::size HashCodeStringP = Object::GetHashCode(&KeyString);
			Elysium::Core::size HashCodeWideStringP = Object::GetHashCode(&KeyWideString);
			Elysium::Core::size HashCodeUtf8StringP = Object::GetHashCode(&KeyUtf8String);
			Elysium::Core::size HashCodeUtf16StringP = Object::GetHashCode(&KeyUtf16String);
			Elysium::Core::size HashCodeUtf32StringP = Object::GetHashCode(&KeyUtf32String);
			
			Elysium::Core::size HashCodePUInt8 = Object::GetHashCode(&KeyUInt8);
			Elysium::Core::size HashCodePUInt16 = Object::GetHashCode(&KeyUInt16);
			Elysium::Core::size HashCodePUInt32 = Object::GetHashCode(&KeyUInt32);
			Elysium::Core::size HashCodePUInt64 = Object::GetHashCode(&KeyUInt64);

			Elysium::Core::size HashCodePInt8 = Object::GetHashCode(&KeyInt8);
			Elysium::Core::size HashCodePInt16 = Object::GetHashCode(&KeyInt16);
			Elysium::Core::size HashCodePInt32 = Object::GetHashCode(&KeyInt32);
			Elysium::Core::size HashCodePInt64 = Object::GetHashCode(&KeyInt64);

			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeStringP);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeWideStringP);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeUtf8StringP);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeUtf16StringP);
			Assert::AreEqual(static_cast<Elysium::Core::size>(20863340834690462), HashCodeUtf32StringP);

			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt8), HashCodePUInt8);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt16), HashCodePUInt16);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt32), HashCodePUInt32);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyUInt64), HashCodePUInt64);

			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt8), HashCodePInt8);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt16), HashCodePInt16);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt32), HashCodePInt32);
			Assert::AreEqual(static_cast<Elysium::Core::size>(KeyInt64), HashCodePInt64);
		}
	};
}
