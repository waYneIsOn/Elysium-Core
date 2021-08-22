#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Dictionary.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;

namespace UnitTests::Core::Collections::Template
{
	TEST_CLASS(DictionaryTest)
	{
	public:
		TEST_METHOD(PointerPointer)
		{
			Assert::Fail();
		}

		TEST_METHOD(PointerValue)
		{
			Assert::Fail();
		}

		TEST_METHOD(ValuePointer)
		{
			Assert::Fail();
		}

		TEST_METHOD(ValueValue)
		{
			Dictionary<String, String> FileExtensionProgramMap = Dictionary<String, String>(4_ui64);

			const int32_t Hash1 = String(u8"txt").GetHashCode();
			const int32_t Hash2 = String(u8"bmp").GetHashCode();
			const int32_t Hash3 = String(u8"dib").GetHashCode();
			const int32_t Hash4 = String(u8"rtf").GetHashCode();

			FileExtensionProgramMap.Add(u8"txt", u8"notepad.exe");
			FileExtensionProgramMap.Add(u8"bmp", u8"paint.exe");
			FileExtensionProgramMap.Add(u8"dib", u8"paint.exe");
			FileExtensionProgramMap.Add(u8"rtf", u8"wordpad.exe");

			// add a fifth value to force a collision as well as a resize
			//FileExtensionProgramMap.Add(u8"tys", u8"collision.exe");

			const String& Value = FileExtensionProgramMap[u8"txt"];

			AssertExtended::AreEqual(u8"notepad.exe", FileExtensionProgramMap[u8"txt"]);
		}
	};
}
