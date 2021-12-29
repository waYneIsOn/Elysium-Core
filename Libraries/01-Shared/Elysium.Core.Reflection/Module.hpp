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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class Assembly;
	class Type;

	class ELYSIUM_CORE_API Module final
	{
		friend class Type;
	public:
		Module(const Assembly& Assembly, const Utf8String& Name);

		Module(const Module& Source) = delete;

		Module(Module&& Right) noexcept = delete;

		~Module();
	public:
		Module& operator=(const Module& Source) = delete;

		Module& operator=(Module&& Right) noexcept = delete;

		const bool operator==(const Module& Other) const;
	public:
		const Assembly& GetAssembly() const;

		const Elysium::Core::Utf8String& GetName() const;

		const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Type*> GetTypes() const;
	public:
		const Elysium::Core::size GetHashCode() const;
	private:
		const Assembly& _Assembly;
		const Utf8String _Name;

		Elysium::Core::Collections::Template::List<const Type*> _Types;

		void Add(const Elysium::Core::Reflection::Type& Type);
		void Remove(const Elysium::Core::Reflection::Type& Type);
	};
}
#endif

