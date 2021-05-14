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
		Decimal(const float Value);
		Decimal(const double Value);
		Decimal(const long double Value);
		Decimal(const Elysium::Core::int64_t HighPart, const Elysium::Core::uint64_t LowPart);
		Decimal(const Decimal& Source);
		Decimal(Decimal&& Right) noexcept;
		~Decimal();

		Decimal& operator=(const Decimal& Source);
		Decimal& operator=(Decimal&& Right) noexcept;

		const bool operator==(const Elysium::Core::Decimal& Other) const;
		const bool operator!=(const Elysium::Core::Decimal& Other) const;
		const bool operator<(const Elysium::Core::Decimal& Other) const;
		const bool operator>(const Elysium::Core::Decimal& Other) const;
		const bool operator<=(const Elysium::Core::Decimal& Other) const;
		const bool operator>=(const Elysium::Core::Decimal& Other) const;

		const Elysium::Core::int64_t& GetHighPart() const;
		const Elysium::Core::uint64_t& GetLowPart() const;
	private:
		Elysium::Core::int64_t _HighPart;
		Elysium::Core::uint64_t _LowPart;
	};
	/*
	constexpr Elysium::Core::Decimal operator "" _M(const long double Value)
	{
		// ToDo: assert & implementation
		return Elysium::Core::Decimal(Value);
	}
	*/
}
#endif
