#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Tuple.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(TupleTests)
	{
	public:
		/*
		TEST_METHOD(ConstTupleTest)
		{
			constexpr const Tuple<int, bool, char, uint16_t> Instance = Tuple<int, bool, char, uint16_t>
				(21, false, 'x', 47);

			//int& FirstItem = Instance.GetFirst();

			// @ToDo: left values, right values etc.
			Assert::Fail();
		}
		*/
		TEST_METHOD(Tuple1Test)
		{
			Tuple<int> Instance = Tuple<int>(13);
			
			int& Item1 = Instance.GetFirst();

			Assert::AreEqual(13, Item1);

			Item1 = 27;
			Assert::AreEqual(27, Item1);
		}

		TEST_METHOD(Tuple2Test)
		{
			Tuple<int, int> Instance = Tuple<int, int>(13, 25);
			
			int& Item1 = Instance.GetFirst();
			int& Item2 = Instance.GetAt<1>();

			Assert::AreEqual(13, Item1);
			Assert::AreEqual(25, Item2);

			Item1 = 27;
			Assert::AreEqual(27, Item1);
		}

		TEST_METHOD(Tuple3Test)
		{
			Tuple<int, int, int> Instance = Tuple<int, int, int>(13, 25, -5);
			
			int& Item1 = Instance.GetFirst();
			int& Item2 = Instance.GetAt<1>();
			int& Item3 = Instance.GetAt<2>();

			Assert::AreEqual(13, Item1);
			Assert::AreEqual(25, Item2);
			Assert::AreEqual(-5, Item3);

			Item1 = 27;
			Assert::AreEqual(27, Item1);
		}
	};
}
