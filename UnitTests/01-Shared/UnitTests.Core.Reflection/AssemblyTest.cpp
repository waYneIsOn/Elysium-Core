#include "CppUnitTest.h"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/AppDomain.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/Assembly.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Reflection;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Reflection
{
	TEST_CLASS(AssemblyTests)
	{
	public:

		TEST_METHOD(GetLoadedAssemblies)
		{
			const Array<const Assembly*> Assemblies = AppDomain::GetAssemblies();
			for (size_t i = 0; i < Assemblies.GetLength(); i++)
			{
				const Assembly* CurrentAssembly = Assemblies[i];
				const String& FullName = CurrentAssembly->GetFullName();
			}			
		}
	};
}
