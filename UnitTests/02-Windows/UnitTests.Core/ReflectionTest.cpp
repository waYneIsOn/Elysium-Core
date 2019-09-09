#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#include "../../../Libraries/01-Shared/Elysium.Core.Reflection/AssemblyName.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Reflection/Assembly.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Reflection/AssemblyBuilder.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Reflection/TypeBuilder.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core::Reflection::Emit;
using namespace Elysium::Core::Reflection;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Reflection)
	{
	public:
		TEST_METHOD(ReflectStringAtRuntime)
		{
			AssemblyName CoreName = AssemblyName(L"Elysium::Core");	// L"Elysium.Core.dll"
			AssemblyBuilder CoreAssembly = AssemblyBuilder();

			// some "standard" types
			TypeBuilder SizeTType = CoreAssembly.DefineType<size_t>(L"size_t", TypeAttributes::Public);
			TypeBuilder WCharType = CoreAssembly.DefineType<wchar_t>(L"wchar_t", TypeAttributes::Public);
			TypeBuilder WCharPointerType = CoreAssembly.DefineType<wchar_t*>(L"wchar_t*", TypeAttributes::Public);
			TypeBuilder CharType = CoreAssembly.DefineType<char>(L"char", TypeAttributes::Public);
			TypeBuilder CharPointerType = CoreAssembly.DefineType<char*>(L"char*", TypeAttributes::Public);

			// String type
			TypeBuilder StringType = CoreAssembly.DefineType<Elysium::Core::String>(L"Elysium::Core::String", TypeAttributes::Public);
			//FieldBuilder StringFieldLength = StringType.DefineField<&Elysium::Core::String::_Length>(L"_Length", SizeTType, FieldAttributes::Private);	// typeof(size_t)
			//FieldBuilder StringFieldData = StringType.DefineField<&Elysium::Core::String::_Data>(L"_Data", ElysiumCharType, FieldAttributes::Private);	// typeof(ElysiumChar*)

			//struct MyStruct { MyStruct() {}; void func(double) {}; int data; };
			//auto bla = &MyStruct::data;
			int x = 345;
		}
	};
}
