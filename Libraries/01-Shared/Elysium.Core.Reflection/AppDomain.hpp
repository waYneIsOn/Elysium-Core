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

#ifndef ELYSIUM_CORE_REFLECTION_CONTAINER_VECTOROFASSEMBLYPOINTER
#include "Container/VectorOfAssemblyPointer.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class Assembly;

	class ELYSIUM_CORE_API AppDomain final
	{
		friend class Assembly;
	public:
		constexpr AppDomain();

		constexpr AppDomain(const AppDomain& Source) = delete;

		constexpr AppDomain(AppDomain&& Right) noexcept = delete;

		constexpr ~AppDomain();
	public:
		constexpr AppDomain& operator=(const AppDomain& Source) = delete;

		constexpr AppDomain& operator=(AppDomain&& Right) noexcept = delete;
	public:
		const Container::VectorOfConstAssemblyPointer GetAssemblies() const;
	public:
		static AppDomain& GetCurrentDomain();
	/*
	public:
		template <class T>
		static const Type& GetTypeOf();
	*/
	private:
		Container::VectorOfConstAssemblyPointer _RegisteredAssemblies;
		//Elysium::Core::Template::Container::HashTable<Module*, Assembly*> _ModuleAssemblyMap;
		//Elysium::Core::Template::Container::HashTable<Type*, Module*> _TypeModuleTable;
		//Elysium::Core::Template::Container::HashTable<Elysium::Core::uint64_t*, Type*> _TypeIdTypeTable;

		constexpr void Add(const Elysium::Core::Reflection::Assembly& Assembly);

		constexpr void Remove(const Elysium::Core::Reflection::Assembly& Assembly);
	};
}
#endif
