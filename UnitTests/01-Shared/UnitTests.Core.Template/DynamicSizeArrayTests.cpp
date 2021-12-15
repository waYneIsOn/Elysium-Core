#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/DynamicSizeArray.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"

using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(DynamicSizeArrayTests)
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

		TEST_METHOD(IterationsThroughEmpty)
		{
			Assert::Fail();
		}

		TEST_METHOD(IterationsThroughPopulated)
		{
			Assert::Fail();
		}

		TEST_METHOD(Accessing)
		{
			Assert::Fail();
		}
	};
}