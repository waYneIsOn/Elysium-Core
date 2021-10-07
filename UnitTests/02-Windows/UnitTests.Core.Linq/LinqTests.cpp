#include "CppUnitTest.h"

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../Libraries/01-Shared/Elysium.Core/Array.hpp"
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
		TEST_METHOD(Combined)
		{
			std::vector<int> PopulatedVector = { 1, 2, 3 };

			const size_t WhereCountResult = PopulatedVector >> Where([](const int& x) -> bool { return x > 1; }) >> Count();
			Assert::AreEqual((const size_t)2, WhereCountResult);

			const bool WhereContainsResult = PopulatedVector >> Where([](const int& x) -> bool { return x > 1; }) >> Contains(23);
			Assert::AreEqual(false, WhereContainsResult);

			const std::vector<int> WhereWhereResult = PopulatedVector >> Where([](const int x) -> bool { return x > 1; }) >> Where([](const int x) -> bool { return x < 3; });
			Assert::AreEqual((size_t)1, WhereWhereResult.size());
		}

		TEST_METHOD(Core_Linq_Any)
		{
			std::vector<int> PopulatedVector = { 1, 2, 3 };
			Assert::IsTrue(PopulatedVector >> Any());

			int PopulatedArray[] = { 3, 2, 1 };
			Assert::IsTrue(PopulatedArray >> Any());

			std::vector<int> EmptyVector = std::vector<int>();
			Assert::IsFalse(EmptyVector >> Any());

			//Elysium::Core::Collections::Template::Array<int> Array = { 1, 2, 3 };
			Elysium::Core::Collections::Template::Array<int> Array = Elysium::Core::Collections::Template::Array<int>(0);
			Assert::IsFalse(Array >> Any());
			/*
			Elysium::Core::Linq::AnyContainer bla = Elysium::Core::Linq::AnyContainer();
			bool istrue = bla.operator()(std::forward<Elysium::Core::Collections::Template::Array<int>>(Array));
			*/
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

		TEST_METHOD(Core_Linq_Where)
		{
			std::vector<int> PopulatedVector = { 1, 2, 3 };
			std::vector<int> Result = PopulatedVector >> Where([](const int x) -> bool { return x > 1; });

			Assert::AreEqual((size_t)2, Result.size());
			Assert::AreEqual(2, Result[0]);
			Assert::AreEqual(3, Result[1]);
		}
	};
}