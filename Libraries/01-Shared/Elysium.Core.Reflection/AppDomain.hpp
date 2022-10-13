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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_HASHTABLE
#include "../Elysium.Core.Template/HashTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class Assembly;

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
	/*
	public:
		template <class T>
		static const Type& GetTypeOf();
	*/
	private:
		static Elysium::Core::Reflection::AppDomain _CurrentDomain;
	private:
		Elysium::Core::Template::Container::Vector<const Assembly*> _RegisteredAssemblies;
		//Elysium::Core::Template::Container::HashTable<Module*, Assembly*> _ModuleAssemblyMap;
		//Elysium::Core::Template::Container::HashTable<Type*, Module*> _TypeModuleTable;
		//Elysium::Core::Template::Container::HashTable<Elysium::Core::uint64_t*, Type*> _TypeIdTypeTable;

		void Add(const Elysium::Core::Reflection::Assembly& Assembly);

		void Remove(const Elysium::Core::Reflection::Assembly& Assembly);
	};
}
#endif
