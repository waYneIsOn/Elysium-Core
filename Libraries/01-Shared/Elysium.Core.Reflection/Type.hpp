/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#define ELYSIUM_CORE_REFLECTION_TYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#include "Module.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API Type final
	{
	public:
		Type(const Module& Module, const Elysium::Core::uint64_t Id, const String& Name);

		Type(const Type& Source) = delete;

		Type(Type&& Right) noexcept = delete;

		~Type();
	public:
		Type& operator=(const Type& Source) = delete;

		Type& operator=(Type&& Right) noexcept = delete;
	public:
		const Elysium::Core::String GetFullName() const;

		const Elysium::Core::String& GetName() const;
	private:
		const Module& _Module;
		const Elysium::Core::uint64_t _Id;
		const String _Name;
		//std::type_info
	};
}
#endif
