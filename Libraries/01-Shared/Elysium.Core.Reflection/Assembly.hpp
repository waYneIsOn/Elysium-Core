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

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME
#include "AssemblyName.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API Assembly
	{
		friend class Elysium::Core::Collections::Template::List<Elysium::Core::Reflection::Assembly>;
	public:
		Assembly(const Assembly& Source) = delete;
		Assembly(Assembly&& Right) noexcept = delete;
		virtual ~Assembly();

		Assembly& operator=(const Assembly& Source) = delete;
		Assembly& operator=(Assembly&& Right) noexcept = delete;

		bool operator==(const Assembly& Other) const;
		bool operator!=(const Assembly& Other) const;
		bool operator<(const Assembly& Other) const;
		bool operator>(const Assembly& Other) const;
		bool operator<=(const Assembly& Other) const;
		bool operator>=(const Assembly& Other) const;
				
		static Assembly& GetEntryAssembly();
		//static Assembly& GetExecutingAssembly();

		//const AssemblyName& FullName() const;

		//static Elysium::Core::Collections::Generic::List<Elysium::Core::Reflection::Assembly> _RegisteredAssemblies;
		//static std::map<Elysium::Core::Reflection::AssemblyName, Elysium::Core::Reflection::Assembly> _Bla;
	protected:
		Assembly();
	private:
		AssemblyName _AssemblyName;
	};
}
#endif
