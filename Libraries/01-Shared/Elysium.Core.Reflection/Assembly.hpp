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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class Module;

	class ELYSIUM_CORE_API Assembly final
	{
		friend class Module;
	public:
		constexpr Assembly(const Elysium::Core::Reflection::AssemblyName& AssemblyName);

		constexpr Assembly(const Assembly& Source) = delete;

		constexpr Assembly(Assembly&& Right) noexcept = delete;

		constexpr ~Assembly();
	public:
		constexpr Assembly& operator=(const Assembly& Source) = delete;

		constexpr Assembly& operator=(Assembly&& Right) noexcept = delete;

		bool operator==(const Assembly& Other) const;

		bool operator!=(const Assembly& Other) const;

		bool operator<(const Assembly& Other) const;

		bool operator>(const Assembly& Other) const;

		bool operator<=(const Assembly& Other) const;

		bool operator>=(const Assembly& Other) const;
	public:
		const Elysium::Core::Utf8String& GetFullName() const;
	public:
		const Elysium::Core::Template::Container::Vector<const Elysium::Core::Reflection::Module*> GetModules() const;
	private:
		Elysium::Core::Reflection::AssemblyName _AssemblyName;

		Elysium::Core::Template::Container::Vector<const Module*> _Modules;

		constexpr void Add(Elysium::Core::Reflection::Module& Module);

		constexpr void Remove(Elysium::Core::Reflection::Module& Module);
	};
}
#endif
