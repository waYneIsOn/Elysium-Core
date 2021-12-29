/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_INTERNAL_FALLBACK_LOCALEREPOSITORY
#define ELYSIUM_CORE_GLOBALIZATION_INTERNAL_FALLBACK_LOCALEREPOSITORY

#ifdef _MSC_VER
#pragma once
#endif

#if defined ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION
#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_INTERNAL_FALLBACK_LOCALEINFO
#include "LocaleInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_HASHTABLE
#include "../Elysium.Core.Template/HashTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

namespace Elysium::Core::Globalization::Internal::Fallback
{
	class LocaleRepository final
	{
	public:
		LocaleRepository() = delete;
		LocaleRepository(const LocaleRepository& Source) = delete;
		LocaleRepository(LocaleRepository&& Right) noexcept = delete;
		~LocaleRepository() = delete;
		
		LocaleRepository& operator=(const LocaleRepository& Source) = delete;
		LocaleRepository& operator=(LocaleRepository&& Right) noexcept = delete;

		static const Elysium::Core::int32_t GetIdFromName(const Elysium::Core::Utf8String& Name);

		static const Elysium::Core::Utf8String GetNameFromId(const Elysium::Core::int32_t Name);
	private:
		inline static const LocaleInfo _CultureInvariantInfo = LocaleInfo(Template::Functional::Move(127), 
			Template::Functional::Move(u8"Invariant Language (Invariant Country)"));
		/*
		inline static const Template::Container::HashTable<Elysium::Core::size, LocaleInfo*> _IdInfoMap =
		{
			{ 127_ui64, &_CultureInvariantInfo }
		};
		*/
	};
}
#endif
#endif
