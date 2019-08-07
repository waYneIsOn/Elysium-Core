#include "CppUnitTest.h"

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef ELYSIUM_CORE_LINQ_ANY
#include "../../../Libraries/01-Shared/Elysium.Core.Linq/Any.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCoreLinq
{
	TEST_CLASS(Linq)
	{
	public:
		TEST_METHOD(Core_Linq_Any)
		{
			std::vector<int> PopulatedVector = { 1, 2, 3 };
			Assert::IsTrue(Elysium::Core::Linq::Any(PopulatedVector));

			int PopulatedArray[] = { 3, 2, 1 };
			Assert::IsTrue(Elysium::Core::Linq::Any(PopulatedArray));

			std::vector<int> EmptyVector = std::vector<int>();
			Assert::IsFalse(Elysium::Core::Linq::Any(EmptyVector));
		}
	};
}