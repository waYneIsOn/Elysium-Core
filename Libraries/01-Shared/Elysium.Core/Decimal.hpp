/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DECIMAL
#define ELYSIUM_CORE_DECIMAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Decimal final
	{
	public:
		Decimal();
		Decimal(const float& Value);
		Decimal(const double& Value);
		Decimal(const int64_t& HighPart, const int64_t& LowPart);
		Decimal(const Decimal& Source);
		Decimal(Decimal&& Right) noexcept;
		~Decimal();

		Decimal& operator=(const Decimal& Source);
		Decimal& operator=(Decimal&& Right) noexcept;

		const int64_t GetHighPart() const;
		const int64_t GetLowPart() const;
	private:
		byte _Data[16];
	};
}
#endif
