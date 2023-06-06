/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#define ELYSIUM_CORE_REFLECTION_MODULE

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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class Assembly;
	class Type;

	class ELYSIUM_CORE_API Module final
	{
		friend class Type;
	public:
		constexpr Module(const Assembly& Assembly, const Utf8String& Name);

		constexpr Module(const Module& Source) = delete;

		constexpr Module(Module&& Right) noexcept = delete;

		constexpr ~Module();
	public:
		constexpr Module& operator=(const Module& Source) = delete;

		constexpr Module& operator=(Module&& Right) noexcept = delete;

		const bool operator==(const Module& Other) const;
	public:
		const Assembly& GetAssembly() const;

		const Elysium::Core::Utf8String& GetName() const;

		const Elysium::Core::Template::Container::Vector<const Elysium::Core::Reflection::Type*> GetTypes() const;
	public:
		const Elysium::Core::size GetHashCode() const;
	private:
		const Assembly& _Assembly;
		const Utf8String _Name;

		Elysium::Core::Template::Container::Vector<const Type*> _Types;

		constexpr void Add(const Elysium::Core::Reflection::Type& Type);
		constexpr void Remove(const Elysium::Core::Reflection::Type& Type);
	};
}
#endif

