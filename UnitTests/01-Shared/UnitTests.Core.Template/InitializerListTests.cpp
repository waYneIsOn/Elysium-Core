#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/InitializerList.hpp"

using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(InitializerListTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			InitializerList<int32_t> Instance = { 02, 03, 01, 02 };
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.size());
		}
	};
}