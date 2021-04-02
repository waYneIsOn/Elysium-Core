/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_REGIONINFO
#define ELYSIUM_CORE_GLOBALIZATION_REGIONINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium::Core::Globalization
{
	class ELYSIUM_CORE_API RegionInfo final
	{
	public:
		RegionInfo(const Elysium::Core::int32_t Culture);
		RegionInfo(const Elysium::Core::String Name);
		RegionInfo(const RegionInfo& Source);
		RegionInfo(RegionInfo&& Right) noexcept;
		~RegionInfo();

		RegionInfo& operator=(const RegionInfo& Source);
		RegionInfo& operator=(RegionInfo&& Right) noexcept;

		const Elysium::Core::String GetDisplayName() const;
		const Elysium::Core::String GetEnglishName() const;
		const bool GetIsMetric() const;
		const Elysium::Core::String GetNativeName() const;
		const Elysium::Core::String GetThreeLetterISORegionName() const;
		const Elysium::Core::String GetTwoLetterISORegionName() const;
	private:
		Elysium::Core::int32_t _LCID;

		static Elysium::Core::int32_t GetLocaleIdFromName(const Elysium::Core::String& Name);
	};
}
#endif
