/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core::Globalization
{
	class ELYSIUM_CORE_API CultureInfo
	{
	public:
		CultureInfo();
		CultureInfo(const Elysium::Core::int32_t Culture);
		CultureInfo(const CultureInfo& Source);
		CultureInfo(CultureInfo&& Right) noexcept;
		~CultureInfo();

		CultureInfo& operator=(const CultureInfo& Source);
		CultureInfo& operator=(CultureInfo&& Right) noexcept;

		void GetName(String* Output) const;
		const Elysium::Core::int32_t GetLCID() const;
	private:
		Elysium::Core::int32_t _LCID;	// locale id
	};
}
#endif
