/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#define ELYSIUM_CORE_REFLECTION_ASSEMBLY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME
#include "AssemblyName.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API Assembly final
	{
	public:
		Assembly(const Elysium::Core::Reflection::AssemblyName& AssemblyName);
		Assembly(const Assembly& Source) = delete;
		Assembly(Assembly&& Right) noexcept = delete;
		~Assembly();

		Assembly& operator=(const Assembly& Source) = delete;
		Assembly& operator=(Assembly&& Right) noexcept = delete;

		bool operator==(const Assembly& Other) const;
		bool operator!=(const Assembly& Other) const;
		bool operator<(const Assembly& Other) const;
		bool operator>(const Assembly& Other) const;
		bool operator<=(const Assembly& Other) const;
		bool operator>=(const Assembly& Other) const;
				
		//static const Assembly& GetEntryAssembly();
		//static Assembly& GetExecutingAssembly();

		//const AssemblyName& FullName() const;
	private:
		Elysium::Core::Reflection::AssemblyName _AssemblyName;
	};

	inline const static Assembly ReflectedAssembly = Assembly(AssemblyName(u8"Elysium::Core", u8"Codebase", Version(0, 1)));

	inline const static Elysium::Core::Collections::Template::List<const Assembly*> _RegisteredAssemblies = { &ReflectedAssembly };
	/*
	class RegisteredAssemblies final
	{
	public:
		RegisteredAssemblies() = delete;
		RegisteredAssemblies(const RegisteredAssemblies& Source) = delete;
		RegisteredAssemblies(RegisteredAssemblies&& Right) noexcept = delete;
		~RegisteredAssemblies() = delete;

		RegisteredAssemblies& operator=(const RegisteredAssemblies& Source) = delete;
		RegisteredAssemblies& operator=(RegisteredAssemblies&& Right) noexcept = delete;

		inline const static Assembly ReflectedAssembly = Assembly(AssemblyName(u8"Elysium::Core", u8"Codebase", Version(0, 1)));

		inline const static Elysium::Core::Collections::Template::List<const Assembly*> _RegisteredAssemblies = { &ReflectedAssembly };
	};
	*/
}
#endif
