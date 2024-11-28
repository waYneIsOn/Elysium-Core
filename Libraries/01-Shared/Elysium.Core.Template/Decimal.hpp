/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_DECIMAL
#define ELYSIUM_CORE_TEMPLATE_MATH_DECIMAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	class Decimal
	{
	public:
		constexpr Decimal() noexcept;

		constexpr Decimal(const Elysium::Core::Template::System::uint32_t Value) noexcept;

		constexpr Decimal(const float Value) noexcept;

		constexpr Decimal(const double Value) noexcept;

		constexpr Decimal(const Elysium::Core::Template::System::int64_t HighPart, const Elysium::Core::Template::System::uint64_t LowPart) noexcept;

		Decimal(const Decimal& Source) noexcept;

		Decimal(Decimal&& Right) noexcept;

		~Decimal() noexcept;
	public:
		Decimal& operator=(const Decimal& Source) noexcept;

		Decimal& operator=(Decimal&& Right) noexcept;
	public:
		constexpr const bool operator==(const Elysium::Core::Template::Math::Decimal& Other) const noexcept;

		constexpr const bool operator!=(const Elysium::Core::Template::Math::Decimal& Other) const noexcept;

		constexpr const bool operator<(const Elysium::Core::Template::Math::Decimal& Other) const noexcept;

		constexpr const bool operator>(const Elysium::Core::Template::Math::Decimal& Other) const noexcept;

		constexpr const bool operator<=(const Elysium::Core::Template::Math::Decimal& Other) const noexcept;

		constexpr const bool operator>=(const Elysium::Core::Template::Math::Decimal& Other) const noexcept;

		constexpr const bool operator==(const Elysium::Core::Template::System::int32_t& Other) const noexcept;

		constexpr const bool operator!=(const Elysium::Core::Template::System::int32_t& Other) const noexcept;

		constexpr const bool operator<(const Elysium::Core::Template::System::int32_t& Other) const noexcept;

		constexpr const bool operator>(const Elysium::Core::Template::System::int32_t& Other) const noexcept;

		constexpr const bool operator<=(const Elysium::Core::Template::System::int32_t& Other) const noexcept;

		constexpr const bool operator>=(const Elysium::Core::Template::System::int32_t& Other) const noexcept;
	public:
		constexpr const Elysium::Core::Template::System::int64_t GetHighPart() const noexcept;

		constexpr const Elysium::Core::Template::System::uint64_t GetLowPart() const noexcept;
	private:
		Elysium::Core::Template::System::int64_t _HighPart;
		Elysium::Core::Template::System::uint64_t _LowPart;
	};

	inline constexpr Decimal::Decimal() noexcept
		: _HighPart(0_i64), _LowPart(0_ui64)
	{ }

	inline constexpr Decimal::Decimal(const Elysium::Core::Template::System::uint32_t Value) noexcept
		: _HighPart(Value), _LowPart(0)
	{ }

	inline constexpr Decimal::Decimal(const float Value) noexcept
		: _HighPart(Elysium::Core::Template::Numeric::NumericTraits<float>::GetValuePreDecimalPoint(Value)),
		_LowPart(Elysium::Core::Template::Numeric::NumericTraits<float>::GetValuePostDecimalPoint(Value, 3))
	{ }

	inline constexpr Decimal::Decimal(const double Value) noexcept
		: _HighPart(Elysium::Core::Template::Numeric::NumericTraits<double>::GetValuePreDecimalPoint(Value)),
		_LowPart(Elysium::Core::Template::Numeric::NumericTraits<double>::GetValuePostDecimalPoint(Value, 3))
	{ }

	inline constexpr Decimal::Decimal(const Elysium::Core::Template::System::int64_t HighPart, const Elysium::Core::Template::System::uint64_t LowPart) noexcept
		: _HighPart(HighPart), _LowPart(LowPart)
	{ }

	inline Decimal::Decimal(const Decimal& Source) noexcept
		: _HighPart(Source._HighPart), _LowPart(Source._LowPart)
	{ }

	inline Decimal::Decimal(Decimal&& Right) noexcept
		: _HighPart(0), _LowPart(0)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	inline Decimal::~Decimal() noexcept
	{ }

	inline Decimal& Decimal::operator=(const Decimal& Source) noexcept
	{
		if (this != &Source)
		{
			_HighPart = Source._HighPart;
			_LowPart = Source._LowPart;
		}
		return *this;
	}

	inline Decimal& Decimal::operator=(Decimal&& Right) noexcept
	{
		if (this != &Right)
		{
			_HighPart = Elysium::Core::Template::Functional::Move(Right._HighPart);
			_LowPart = Elysium::Core::Template::Functional::Move(Right._LowPart);

			Right._HighPart = 0;
			Right._LowPart = 0;
		}
		return *this;
	}

	inline constexpr const bool Decimal::operator==(const Elysium::Core::Template::Math::Decimal& Other) const noexcept
	{
		return _HighPart == Other._HighPart && _LowPart == Other._LowPart;
	}

	inline constexpr const bool Decimal::operator!=(const Elysium::Core::Template::Math::Decimal& Other) const noexcept
	{
		return _HighPart != Other._HighPart || _LowPart != Other._LowPart;
	}

	inline constexpr const bool Decimal::operator<(const Elysium::Core::Template::Math::Decimal& Other) const noexcept
	{
		return _HighPart <= Other._HighPart && _LowPart < Other._LowPart;
	}

	inline constexpr const bool Decimal::operator>(const Elysium::Core::Template::Math::Decimal& Other) const noexcept
	{
		return _HighPart >= Other._HighPart && _LowPart > Other._LowPart;
	}

	inline constexpr const bool Decimal::operator<=(const Elysium::Core::Template::Math::Decimal& Other) const noexcept
	{
		return _HighPart <= Other._HighPart && _LowPart <= Other._LowPart;
	}

	inline constexpr const bool Decimal::operator>=(const Elysium::Core::Template::Math::Decimal& Other) const noexcept
	{
		return _HighPart >= Other._HighPart && _LowPart >= Other._LowPart;
	}

	inline constexpr const bool Decimal::operator==(const Elysium::Core::Template::System::int32_t& Other) const noexcept
	{
		return _LowPart == 0 && _HighPart == Other;
	}

	inline constexpr const bool Decimal::operator!=(const Elysium::Core::Template::System::int32_t& Other) const noexcept
	{
		return _LowPart != 0 || _HighPart != Other;
	}

	inline constexpr const bool Decimal::operator<(const Elysium::Core::Template::System::int32_t& Other) const noexcept
	{
		return _HighPart < Other;
	}

	inline constexpr const bool Decimal::operator>(const Elysium::Core::Template::System::int32_t& Other) const noexcept
	{
		return _HighPart > Other || (_HighPart == Other && _LowPart > 0);
	}

	inline constexpr const bool Decimal::operator<=(const Elysium::Core::Template::System::int32_t& Other) const noexcept
	{
		return _HighPart < Other || (_HighPart == Other && _LowPart == 0);
	}

	inline constexpr const bool Decimal::operator>=(const Elysium::Core::Template::System::int32_t& Other) const noexcept
	{
		return _HighPart > Other || (_HighPart == Other && _LowPart > 0);
	}

	inline constexpr const Elysium::Core::Template::System::int64_t Decimal::GetHighPart() const noexcept
	{
		return _HighPart;
	}

	inline constexpr const Elysium::Core::Template::System::uint64_t Decimal::GetLowPart() const noexcept
	{
		return _LowPart;
	}
}
#endif
