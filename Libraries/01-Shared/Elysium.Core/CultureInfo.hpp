/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#define ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium::Core::Globalization
{
	class ELYSIUM_CORE_API CultureInfo
	{
	public:
		CultureInfo();
		CultureInfo(int Culture);
		CultureInfo(const CultureInfo& Source);
		CultureInfo(CultureInfo&& Right) noexcept;
		~CultureInfo();

		CultureInfo& operator=(const CultureInfo& Source);
		CultureInfo& operator=(CultureInfo&& Right) noexcept;

		void GetName(String* Output) const;
		int GetLCID() const;
	private:
		int _LCID;	// locale id
	};
}
#endif
