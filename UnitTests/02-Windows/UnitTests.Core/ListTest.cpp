#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/List.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Guid.hpp"

#include <vector>

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Generic;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_List)
	{
	public:
		TEST_METHOD(Constructor_Int)
		{
			List<int> TestList1;
			List<int> TestList2(10);
		}
		TEST_METHOD(Constructor_Guid)
		{
			List<Guid> TestList1;
			List<Guid> TestList2(10);
		}
	};
}
