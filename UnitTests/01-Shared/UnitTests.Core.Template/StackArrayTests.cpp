#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/StackArray.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(StackArrayTests)
	{
	public:
		TEST_METHOD(StringTest)
		{
			StackArray<String, 5> Instance = StackArray<String, 5>();
			Assert::AreEqual(static_cast<size>(5), Instance.GetSize());
			Instance[0] = u8"0\r\n";
			Instance[1] = u8"1\r\n";
			Instance[2] = u8"2\r\n";
			Instance[3] = u8"3\r\n";
			Instance[4] = u8"4\r\n";
			Assert::IsTrue(Instance.Contains(u8"2\r\n"));
			Assert::IsFalse(Instance.Contains(u8"5\r\n"));

			Elysium::Core::size Index = 0;
			for (StackArray<String, 5>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				String& Item = *Iterator;
				Logger::WriteMessage((char*)&Item[0]);
				Index++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Index);
			Logger::WriteMessage("\r\n");

			Index = 0;
			for (StackArray<String, 5>::ReverseIterator Iterator = Instance.GetReverseBegin(); Iterator != Instance.GetReverseEnd(); --Iterator)
			{
				String& Item = *Iterator;
				Logger::WriteMessage((char*)&Item[0]);
				Index++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Index);
			Logger::WriteMessage("\r\n");

			Index = 0;
			const StackArray<String, 5>& ConstInstance = Instance;
			for (StackArray<String, 5>::ConstIterator Iterator = ConstInstance.GetBegin(); Iterator != ConstInstance.GetEnd(); ++Iterator)
			{
				const String& Item = *Iterator;
				Logger::WriteMessage((char*)&Item[0]);
				Index++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Index);
			Logger::WriteMessage("\r\n");

			Index = 0;
			for (StackArray<String, 5>::ConstReverseIterator Iterator = ConstInstance.GetReverseBegin(); Iterator != ConstInstance.GetReverseEnd(); --Iterator)
			{
				const String& Item = *Iterator;
				Logger::WriteMessage((char*)&Item[0]);
				Index++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Index);

			Assert::AreEqual(static_cast<Elysium::Core::size>(2), Instance.IndexOf(u8"2\r\n"));
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), Instance.LastIndexOf(u8"2\r\n"));
		}
	};
}