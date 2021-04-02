/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#define ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_IFORMATPROVIDER
#include "IFormatProvider.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_CALENDAR
#include "Calendar.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTURETYPES
#include "CultureTypes.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#include "NumberFormatInfo.hpp"
#endif

namespace Elysium::Core::Globalization
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_API CultureInfo final : public IFormatProvider
	{
	public:
		CultureInfo();
		CultureInfo(const Elysium::Core::int32_t Culture, const bool UseUserOverride);
		CultureInfo(const Elysium::Core::String Name, const bool UseUserOverride);
		CultureInfo(const CultureInfo& Source);
		CultureInfo(CultureInfo&& Right) noexcept;
		virtual ~CultureInfo();

		CultureInfo& operator=(const CultureInfo& Source);
		CultureInfo& operator=(CultureInfo&& Right) noexcept;

		static const CultureInfo GetInvariantCulture();
		static const Elysium::Core::Collections::Template::Array<CultureInfo> GetCultures(const CultureTypes& Types);

		const Elysium::Core::String GetDisplayName() const;
		const Elysium::Core::String GetEnglishName() const;
		const Elysium::Core::String GetName() const;
		const Elysium::Core::int32_t& GetLCID() const;
		NumberFormatInfo GetNumberFormatInfo() const;
	private:
		Elysium::Core::int32_t _LCID;
		bool _UseUserOverride;

		static Elysium::Core::Collections::Template::List<Elysium::Core::int32_t> _LocaleIds;

		static Elysium::Core::int32_t GetLocaleIdFromName(const Elysium::Core::String& Name);

		static Elysium::Core::int32_t EnumerateLocalesExCallback(wchar_t* Name, unsigned long Flags, Elysium::Core::int64_t Parameters);
	};
}
#endif
