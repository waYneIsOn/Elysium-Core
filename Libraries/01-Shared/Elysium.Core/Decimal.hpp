/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DECIMAL
#define ELYSIUM_CORE_DECIMAL

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef _STDINT_H
#include <cstdint>
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

		const int64_t* GetHighPart() const;
		const int64_t* GetLowPart() const;
	private:
		byte _Data[16];
	};
}
#endif
