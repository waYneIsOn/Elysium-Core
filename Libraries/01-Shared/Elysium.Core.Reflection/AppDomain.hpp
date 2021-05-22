/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_APPDOMAIN
#define ELYSIUM_CORE_REFLECTION_APPDOMAIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API AppDomain final
	{
		friend class Assembly;
	public:
		AppDomain() = delete;
		AppDomain(const AppDomain& Source) = delete;
		AppDomain(AppDomain&& Right) noexcept = delete;
		~AppDomain() = delete;

		AppDomain& operator=(const AppDomain& Source) = delete;
		AppDomain& operator=(AppDomain&& Right) noexcept = delete;

		static void Add(const Elysium::Core::Reflection::Assembly& Assembly);

		static const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Assembly*> GetAssemblies();
	private:
		inline const static Assembly ReflectedAssembly = Assembly(AssemblyName(u8"Elysium::Core", u8"Codebase", Version(0, 1)));

		inline static Elysium::Core::Collections::Template::List<const Assembly*> _RegisteredAssemblies = { &ReflectedAssembly };
	};
}
#endif
