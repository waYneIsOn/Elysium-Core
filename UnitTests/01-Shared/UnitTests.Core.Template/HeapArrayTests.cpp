#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/HeapArray.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"

using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(HeapArrayTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			// Default constructor without elements

			// InitializerList

			// Default constructor with elements

			// Copy constructor

			// Move constructor


			Assert::Fail();
		}

		TEST_METHOD(Iterations)
		{
			Assert::Fail();
		}
	};
}