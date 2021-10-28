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
			for (Elysium::Core::size a = 0; a < Assemblies.GetLength(); a++)
			{
				const Assembly& CurrentAssembly = *Assemblies[a];
				const String& AssemblyFullName = CurrentAssembly.GetFullName();
				Logger::WriteMessage("Assembly: ");
				Logger::WriteMessage((char*)&AssemblyFullName[0]);
				Logger::WriteMessage("\r\n");

				const Array<const Module*> Modules = CurrentAssembly.GetModules();
				for (Elysium::Core::size m = 0; m < Modules.GetLength(); m++)
				{
					const Module& CurrentModule = *Modules[m];
					const String& ModuleName = CurrentModule.GetName();
					Logger::WriteMessage("\tModule: ");
					Logger::WriteMessage((char*)&ModuleName[0]);
					Logger::WriteMessage("\r\n");

					const Array<const Type*> Types = CurrentModule.GetTypes();
					for (Elysium::Core::size t = 0; t < Types.GetLength(); t++)
					{
						const Type& CurrentType = *Types[t];
						const String& TypeName = CurrentType.GetName();
						Logger::WriteMessage("\t\tType: ");
						Logger::WriteMessage((char*)&TypeName[0]);
						Logger::WriteMessage("\r\n");
					}
				}
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), Assemblies.GetLength());
		}
	};
}
