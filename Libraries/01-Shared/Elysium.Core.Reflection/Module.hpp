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

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "Type.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class Assembly;

	class ELYSIUM_CORE_API Module final
	{
		friend class Type;
	public:
		Module(const Assembly& Assembly, const String& Name);
		Module(const Module& Source) = delete;
		Module(Module&& Right) noexcept = delete;
		~Module();

		Module& operator=(const Module& Source) = delete;
		Module& operator=(Module&& Right) noexcept = delete;

		const Assembly& GetAssembly() const;

		const Elysium::Core::String& GetName() const;

		const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Type*> GetTypes() const;
	private:
		const Assembly& _Assembly;
		const String _Name;

		Elysium::Core::Collections::Template::List<const Type*> _Types = Elysium::Core::Collections::Template::List<const Type*>();

		void Add(const Elysium::Core::Reflection::Type& Type);
		void Remove(const Elysium::Core::Reflection::Type& Type);
	};
}
#endif

