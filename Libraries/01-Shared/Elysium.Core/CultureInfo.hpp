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

#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#include "NumberFormatInfo.hpp"
#endif

namespace Elysium::Core::Globalization
{
	class ELYSIUM_CORE_API CultureInfo final : public IFormatProvider
	{
	public:
		CultureInfo(const Elysium::Core::int32_t Culture, const bool UseUserOverride);
		CultureInfo(const Elysium::Core::String Name, const bool UseUserOverride);
		CultureInfo(const CultureInfo& Source);
		CultureInfo(CultureInfo&& Right) noexcept;
		virtual ~CultureInfo();

		CultureInfo& operator=(const CultureInfo& Source);
		CultureInfo& operator=(CultureInfo&& Right) noexcept;

		static const CultureInfo GetInvariantCulture();

		const Elysium::Core::String GetDisplayName() const;
		const Elysium::Core::String GetEnglishName() const;
		const Elysium::Core::String GetName() const;
		const Elysium::Core::int32_t& GetLCID() const;
		const NumberFormatInfo GetNumberFormatInfo() const;
	private:
		Elysium::Core::int32_t _LCID;
		bool _UseUserOverride;
	};
}
#endif
