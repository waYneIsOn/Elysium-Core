/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME
#define ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API AssemblyName final
			{
			public:
				AssemblyName();
				AssemblyName(const String& AssemblyName);
				AssemblyName(const AssemblyName& Source);
				AssemblyName(AssemblyName&& Right);
				~AssemblyName();

				AssemblyName& operator=(const AssemblyName& Source);
				AssemblyName& operator=(AssemblyName&& Right);
				/*
				const String Name() const;
				const Version Version() const;
				const CultureInfo CultureInfo() const;
				const String FullName() const;
				*/
			private:
				const String _AssemblyName;
			};
		}
	}
}
#endif
