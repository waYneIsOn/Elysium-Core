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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_HASHTABLE
#include "../Elysium.Core.Template/HashTable.hpp"
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
		AppDomain();

		AppDomain(const AppDomain& Source) = delete;

		AppDomain(AppDomain&& Right) noexcept = delete;

		~AppDomain();
	public:
		AppDomain& operator=(const AppDomain& Source) = delete;

		AppDomain& operator=(AppDomain&& Right) noexcept = delete;
	public:
		const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Assembly*> GetAssemblies() const;
	public:
		static AppDomain& GetCurrentDomain();
	private:
		Elysium::Core::Collections::Template::List<const Assembly*> _RegisteredAssemblies;
		//Elysium::Core::Collections::Template::Dictionary<const Module*, const Assembly*> _ModuleAssemblyMap
		//Elysium::Core::Collections::Template::Dictionary<const Type*, const Module*> _TypeModuleTable
		//Elysium::Core::Collections::Template::Dictionary<const Elysium::Core::uint64_t*, const Type*> _TypeIdTypeTable

		void Add(const Elysium::Core::Reflection::Assembly& Assembly);

		void Remove(const Elysium::Core::Reflection::Assembly& Assembly);
	};

	// ToDo: "hide"
	inline static Elysium::Core::Reflection::AppDomain _CurrentDomain = Elysium::Core::Reflection::AppDomain();
}
#endif
