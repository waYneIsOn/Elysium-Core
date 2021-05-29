#include "CppUnitTest.h"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/AppDomain.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/Assembly.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/Module.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/Type.hpp"

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
			const AppDomain& CurrentAppDomain = AppDomain::GetCurrentDomain();
			const Array<const Assembly*> Assemblies = CurrentAppDomain.GetAssemblies();
			for (size_t a = 0; a < Assemblies.GetLength(); a++)
			{
				const Assembly& CurrentAssembly = *Assemblies[a];
				const String& AssemblyFullName = CurrentAssembly.GetFullName();

				const Array<const Module*> Modules = CurrentAssembly.GetModules();
				for (size_t m = 0; m < Modules.GetLength(); m++)
				{
					const Module& CurrentModule = *Modules[m];
					const String& ModuleName = CurrentModule.GetName();

					const Array<const Type*> Types = CurrentModule.GetTypes();
					for (size_t t = 0; t < Types.GetLength(); t++)
					{
						const Type& CurrentType = *Types[t];
						const String& TypeName = CurrentType.GetName();
					}
				}
			}
			Assert::AreEqual(static_cast<size_t>(2), Assemblies.GetLength());
		}
	};
}
