#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/List.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Template_List)
	{
	public:
		TEST_METHOD(Value)
		{
			int Value1 = 1;
			int Value2 = 2;
			int Value3 = 3;
			int Value4 = 4;

			List<int> TestList;
			TestList.Add(Value1);
			TestList.Add(Value2);
			TestList.Add(Value3);
			TestList.Add(Value4);
			TestList.Add(Value1);

			Assert::AreEqual(1, TestList[0]);
			Assert::AreEqual(2, TestList[1]);
			Assert::AreEqual(3, TestList[2]);
			Assert::AreEqual(4, TestList[3]);
			Assert::AreEqual(1, TestList[4]);

			Assert::AreNotEqual(&Value1, &TestList[0]);
			Assert::AreNotEqual(&Value2, &TestList[1]);
			Assert::AreNotEqual(&Value3, &TestList[2]);
			Assert::AreNotEqual(&Value4, &TestList[3]);
			Assert::AreNotEqual(&Value1, &TestList[4]);
		}
		TEST_METHOD(Pointer)
		{
			int Value1 = 1;
			int Value2 = 2;
			int Value3 = 3;
			int Value4 = 4;

			List<int*> TestList;
			TestList.Add(&Value1);
			TestList.Add(&Value2);
			TestList.Add(&Value3);
			TestList.Add(&Value4);
			TestList.Add(&Value1);

			Assert::AreEqual(&Value1, TestList[0]);
			Assert::AreEqual(&Value2, TestList[1]);
			Assert::AreEqual(&Value3, TestList[2]);
			Assert::AreEqual(&Value4, TestList[3]);
			Assert::AreEqual(&Value1, TestList[4]);

			Assert::AreEqual(Value1, *TestList[0]);
			Assert::AreEqual(Value2, *TestList[1]);
			Assert::AreEqual(Value3, *TestList[2]);
			Assert::AreEqual(Value4, *TestList[3]);
			Assert::AreEqual(Value1, *TestList[4]);
		}
	};
}
