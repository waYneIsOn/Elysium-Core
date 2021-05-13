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
		constexpr Decimal();
		constexpr Decimal(const float Value);
		constexpr Decimal(const double Value);
		constexpr Decimal(const long double Value);
		constexpr Decimal(const Elysium::Core::int64_t HighPart, const Elysium::Core::uint64_t LowPart);
		constexpr Decimal(const Decimal& Source);
		constexpr Decimal(Decimal&& Right) noexcept;
		constexpr ~Decimal();

		constexpr Decimal& operator=(const Decimal& Source);
		constexpr Decimal& operator=(Decimal&& Right) noexcept;

		constexpr const bool operator==(const Elysium::Core::Decimal& Other) const;
		constexpr const bool operator!=(const Elysium::Core::Decimal& Other) const;
		constexpr const bool operator<(const Elysium::Core::Decimal& Other) const;
		constexpr const bool operator>(const Elysium::Core::Decimal& Other) const;
		constexpr const bool operator<=(const Elysium::Core::Decimal& Other) const;
		constexpr const bool operator>=(const Elysium::Core::Decimal& Other) const;

		constexpr const Elysium::Core::int64_t& GetHighPart() const;
		constexpr const Elysium::Core::uint64_t& GetLowPart() const;
	private:
		Elysium::Core::int64_t _HighPart;
		Elysium::Core::uint64_t _LowPart;
	};
	
	constexpr Elysium::Core::Decimal operator "" _M(const long double Value)
	{
		// ToDo: assert & implementation
		return Elysium::Core::Decimal(Value);
	}
}
#endif
