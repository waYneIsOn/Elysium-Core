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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME
#include "AssemblyName.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#include "Module.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API Assembly final
	{
		friend class Module;
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
		
		const Elysium::Core::String& GetFullName() const;

		const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Module*> GetModules() const;
	private:
		Elysium::Core::Reflection::AssemblyName _AssemblyName;

		Elysium::Core::Collections::Template::List<const Module*> _Modules = Elysium::Core::Collections::Template::List<const Module*>();

		void Add(const Elysium::Core::Reflection::Module& Module);
		void Remove(const Elysium::Core::Reflection::Module& Module);
	};
}
#endif
