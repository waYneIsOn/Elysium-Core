/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#define ELYSIUM_CORE_REFLECTION_ASSEMBLY

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME
#include "AssemblyName.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API Assembly
			{
			public:
				Assembly(const Assembly& Source);
				Assembly(Assembly&& Right);
				virtual ~Assembly();

				Assembly& operator=(const Assembly& Source);
				Assembly& operator=(Assembly&& Right);
				
				static Assembly GetEntryAssembly();
				//static Assembly GetExecutingAssembly();

				//const AssemblyName& FullName() const;
			protected:
				Assembly();

				//static std::map<x, y> _RegisteredAssemblies;
			private:
				const AssemblyName _AssemblyName;
				const String _Location;
			};
		}
	}
}
#endif
