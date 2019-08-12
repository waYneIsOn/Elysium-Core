#include "CppUnitTest.h"

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "../../../Libraries/01-Shared/Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_LINQ_EXTENSION
#include "../../../Libraries/01-Shared/Elysium.Core.Linq/Extension.hpp"
#endif

using namespace Elysium::Core::Linq;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCoreLinq
{
	TEST_CLASS(LinqTest)
	{
	public:
		TEST_METHOD(Core_Linq_Any)
		{
			std::vector<int> PopulatedVector = { 1, 2, 3 };
			Assert::IsTrue(PopulatedVector >> Any());

			int PopulatedArray[] = { 3, 2, 1 };
			Assert::IsTrue(PopulatedArray >> Any());

			std::vector<int> EmptyVector = std::vector<int>();
			Assert::IsFalse(EmptyVector >> Any());
		}

		TEST_METHOD(Core_Linq_Contains)
		{
			std::vector<int> PopulatedVector = { 1, 2, 3 };
			Assert::IsTrue(PopulatedVector >> Contains(2));
			Assert::IsFalse(PopulatedVector >> Contains(4));

			int PopulatedArray[] = { 3, 2, 1 };
			Assert::IsTrue(PopulatedArray >> Contains(2));
			Assert::IsFalse(PopulatedArray >> Contains(4));

			std::vector<int> EmptyVector = std::vector<int>();
			Assert::IsFalse(EmptyVector >> Contains(2));
			Assert::IsFalse(EmptyVector >> Contains(4));
		}

		TEST_METHOD(Core_Linq_Count)
		{
			std::vector<int> PopulatedVector = { 1, 2, 3 };
			Assert::AreEqual((size_t)3, PopulatedVector >> Count());

			int PopulatedArray[] = { 3, 2, 1 };
			Assert::AreEqual((size_t)3, PopulatedArray >> Count());

			std::vector<int> EmptyVector = std::vector<int>();
			Assert::AreEqual((size_t)0, EmptyVector >> Count());
		}
	};
}