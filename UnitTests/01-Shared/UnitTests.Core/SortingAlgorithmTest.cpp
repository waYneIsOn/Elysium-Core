#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Algorithm.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template
{
	TEST_CLASS(SortingAlgorithmTest)
	{
	public:
		TEST_METHOD(TestBubbleSort)
		{
			byte UnsortedData[3];

			// test function with signature "const T First, const size_t Count"
			std::memcpy(&UnsortedData[0], &_UnsortedData[0], 3);
			BubbleSort(&UnsortedData[0], 3);

			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[2]);
			
			// test function with signature "const T First, const T Last"
			std::memcpy(&UnsortedData[0], &_UnsortedData[0], 3);
			BubbleSort(&UnsortedData[0], &UnsortedData[2]);
			
			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[2]);
		}
	private:
		byte _UnsortedData[3] = { 3, 1, 2 };
	};
}
