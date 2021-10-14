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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

namespace Elysium::Core
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_API Decimal final
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		Decimal();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		Decimal(const float Value);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		Decimal(const double Value);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		Decimal(const long double Value);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="HighPart"></param>
		/// <param name="LowPart"></param>
		Decimal(const Elysium::Core::int64_t HighPart, const Elysium::Core::uint64_t LowPart);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		Decimal(const Decimal& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Decimal(Decimal&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		~Decimal();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		Decimal& operator=(const Decimal& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Decimal& operator=(Decimal&& Right) noexcept;

		const bool operator==(const Elysium::Core::Decimal& Other) const;
		const bool operator!=(const Elysium::Core::Decimal& Other) const;
		const bool operator<(const Elysium::Core::Decimal& Other) const;
		const bool operator>(const Elysium::Core::Decimal& Other) const;
		const bool operator<=(const Elysium::Core::Decimal& Other) const;
		const bool operator>=(const Elysium::Core::Decimal& Other) const;

		const bool operator==(const Elysium::Core::int32_t& Other) const;
		const bool operator!=(const Elysium::Core::int32_t& Other) const;
		const bool operator<(const Elysium::Core::int32_t& Other) const;
		const bool operator>(const Elysium::Core::int32_t& Other) const;
		const bool operator<=(const Elysium::Core::int32_t& Other) const;
		const bool operator>=(const Elysium::Core::int32_t& Other) const;
		
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::int64_t& GetHighPart() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
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
