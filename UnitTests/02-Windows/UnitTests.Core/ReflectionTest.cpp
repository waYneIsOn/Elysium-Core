#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../../../Libraries/01-Shared/Elysium.Core.Reflection/Assembly.hpp"

namespace UnitTestsCore
{
	TEST_CLASS(Core_Reflection)
	{
	public:
		TEST_METHOD(ReflectStringAtRuntime)
		{
			/*
			const Elysium::Core::Reflection::Assembly& CoreAssembly = Elysium::Core::Reflection::Assembly::_RegisteredAssemblies[0];
			size_t bla = Elysium::Core::Reflection::Assembly::_RegisteredAssemblies.GetCount();
			Assert::AreEqual(0, (int)bla);
			*/
		}
	};
}
