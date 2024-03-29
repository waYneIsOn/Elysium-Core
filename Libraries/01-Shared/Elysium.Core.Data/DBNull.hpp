/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_DBNULL
#define ELYSIUM_CORE_DATA_DBNULL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

namespace Elysium::Core::Data
{
	class ELYSIUM_CORE_DATA_API DBNull final
	{
	private:
		DBNull();
	public:
		DBNull(const DBNull& Source) = delete;

		DBNull(DBNull&& Right) noexcept = delete;

		~DBNull();
	public:
		DBNull& operator=(const DBNull& Source) = delete;

		DBNull& operator=(DBNull&& Right) noexcept = delete;
	public:
		static const DBNull& GetValue();
	private:
		static const DBNull _Value;
	};
}
#endif
