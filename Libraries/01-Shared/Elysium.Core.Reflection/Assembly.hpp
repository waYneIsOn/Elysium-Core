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
		
		const Elysium::Core::String& GetFullName() const;
	private:
		Elysium::Core::Reflection::AssemblyName _AssemblyName;
	};
}
#endif
