/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NUMERIC
#define ELYSIUM_CORE_NUMERIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_OVERFLOWEXCEPTION
#include "OverflowException.hpp"
#endif

#ifndef ELYSIUM_CORE_DIVIDEBYZEROEXCEPTION
#include "DivideByZeroException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ARITHMETIC
#include "../Elysium.Core.Template/Concepts/Arithmetic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGRAL
#include "../Elysium.Core.Template/Concepts/Integral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../Elysium.Core.Template/Numeric/NumericTraits.hpp"
#endif

namespace Elysium::Core
{
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	class Numeric
	{
	public:
		constexpr Numeric() = default;

		inline constexpr Numeric(const T Value)
			: _Value(Value)
		{ }

		inline constexpr Numeric(const Numeric& Source)
			: _Value(Source._Value)
		{ }

		inline constexpr Numeric(Numeric&& Right) noexcept
			: _Value(0)
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~Numeric() = default;
	public:
		inline constexpr Numeric& operator=(const Numeric& Source)
		{
			if (this != &Source)
			{
				_Value = Source._Value;
			}

			return *this;
		}

		inline constexpr Numeric& operator=(const T Value)
		{
			_Value = Value;

			return *this;
		}

		inline constexpr Numeric& operator=(Numeric&& Right) noexcept
		{
			if (this != &Right)
			{
				_Value = Elysium::Core::Template::Functional::Move(Right._Value);
			}

			return *this;
		}
	public:
		inline static constexpr const T GetMinValue() noexcept
		{
			return Elysium::Core::Template::Numeric::NumericTraits<T>::Minimum;
		}

		inline static constexpr const T GetMaxValue() noexcept
		{
			return Elysium::Core::Template::Numeric::NumericTraits<T>::Maximum;
		}

		inline static constexpr const bool GetIsSigned() noexcept
		{
			return Elysium::Core::Template::Numeric::NumericTraits<T>::IsSigned;
		}
	public:
		inline explicit constexpr operator T() const
		{
			return _Value;
		}
	public:
		inline constexpr const bool operator==(const Numeric& Other) const
		{
			return _Value == Other._Value;
		}

		inline constexpr const bool operator!=(const Numeric& Other) const
		{
			return _Value != Other._Value;
		}

		inline constexpr const bool operator<(const Numeric& Other) const
		{
			return _Value < Other._Value;
		}

		inline constexpr const bool operator>(const Numeric& Other) const
		{
			return _Value > Other._Value;
		}

		inline constexpr const bool operator<=(const Numeric& Other) const
		{
			return _Value <= Other._Value;
		}

		inline constexpr const bool operator>=(const Numeric& Other) const
		{
			return _Value >= Other._Value;
		}
	public:
		inline constexpr const bool operator==(const T Other) const
		{
			return _Value == Other;
		}

		inline constexpr const bool operator!=(const T Other) const
		{
			return _Value != Other;
		}

		inline constexpr const bool operator<(const T Other) const
		{
			return _Value < Other;
		}

		inline constexpr const bool operator>(const T Other) const
		{
			return _Value > Other;
		}

		inline constexpr const bool operator<=(const T Other) const
		{
			return _Value <= Other;
		}

		inline constexpr const bool operator>=(const T Other) const
		{
			return _Value >= Other;
		}
	public:
		inline constexpr Numeric& operator++()
		{
			if (_Value == GetMaxValue())
			{
				throw OverflowException();
			}

			_Value++;

			return *this;
		}

		inline constexpr Numeric operator++(int)
		{
			Numeric<T> Result = Numeric<T>(*this);
			++(*this);
			return Result;
		}

		inline constexpr Numeric& operator--()
		{
			if (_Value == GetMinValue())
			{
				throw OverflowException();
			}

			_Value--;

			return *this;
		}

		inline constexpr Numeric operator--(int)
		{
			Numeric<T> Result = Numeric<T>(*this);
			--(*this);
			return Result;
		}
	public:
		inline Numeric& operator+=(const Numeric& Other)
		{
			return this->operator+=(Other._Value);
		}

		inline Numeric& operator+=(const T Other)
		{
			if (Other > 0 && _Value > GetMaxValue() - Other)
			{
				throw OverflowException();
			}
			if (Other < 0 && _Value < GetMinValue() - Other)
			{
				throw OverflowException();
			}

			_Value += Other;

			return *this;
		}

		inline Numeric& operator-=(const Numeric& Other)
		{
			return this->operator-=(Other._Value);
		}

		inline Numeric& operator-=(const T Other)
		{
			if (Other < 0 && _Value > GetMaxValue() + Other)
			{
				throw OverflowException();
			}
			if (Other > 0 && _Value < GetMinValue() + Other)
			{
				throw OverflowException();
			}

			_Value -= Other;

			return *this;
		}

		inline Numeric& operator*=(const Numeric& Other)
		{
			return this->operator*=(Other._Value);
		}

		inline Numeric& operator*=(const T Other)
		{
			if (_Value == -1 && Other == GetMinValue())
			{
				throw OverflowException();
			}
			if (Other == -1 && _Value == GetMinValue())
			{
				throw OverflowException();
			}
			if (_Value > 0 && (_Value > GetMaxValue() / Other))
			{
				throw OverflowException();
			}
			if (_Value > 0 && (_Value < GetMinValue() / Other))
			{
				throw OverflowException();
			}

			_Value *= Other;

			return *this;
		}

		inline Numeric& operator/=(const Numeric& Other)
		{
			return this->operator/=(Other._Value);
		}

		inline Numeric& operator/=(const T Other)
		{
			if (_Value == GetMinValue() && Other == -1)
			{
				throw OverflowException();
			}
			if (_Value == -1 && Other == GetMinValue())
			{
				throw OverflowException();
			}
			if (Other == 0)
			{
				throw DivideByZeroException();
			}

			_Value /= Other;

			return *this;
		}
	public:
		inline Numeric& operator%=(const Numeric& Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return this->operator%=(Other._Value);
		}

		inline Numeric& operator%=(const T Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			_Value %= Other;

			return *this;
		}

		inline Numeric& operator<<=(const Numeric& Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return this->operator<<=(Other._Value);
		}

		inline Numeric& operator<<=(const T Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			_Value <<= Other;

			return *this;
		}

		inline Numeric& operator>>=(const Numeric& Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return this->operator>>=(Other._Value);
		}

		inline Numeric& operator>>=(const T Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			_Value >>= Other;

			return *this;
		}

		inline Numeric& operator&=(const Numeric& Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return this->operator&=(Other._Value);
		}

		inline Numeric& operator&=(const T Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			_Value &= Other;

			return *this;
		}

		inline Numeric& operator|=(const Numeric& Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return this->operator|=(Other._Value);
		}

		inline Numeric& operator|=(const T Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			_Value |= Other;

			return *this;
		}

		inline Numeric& operator^=(const Numeric& Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return this->operator^=(Other._Value);
		}

		inline Numeric& operator^=(const T Other)
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			_Value ^= Other;

			return *this;
		}
	public:
		inline Numeric operator+(const Numeric& Other) const
		{
			return this->operator+(Other._Value);
		}

		inline Numeric operator+(const T Other) const
		{
			if (Other > 0 && _Value > GetMaxValue() - Other)
			{
				throw OverflowException();
			}
			if (Other < 0 && _Value < GetMinValue() - Other)
			{
				throw OverflowException();
			}

			return Numeric(_Value + Other);
		}

		inline Numeric operator-(const Numeric& Other) const
		{
			return this->operator-(Other._Value);
		}

		inline Numeric operator-(const T Other) const
		{
			if (Other < 0 && _Value > GetMaxValue() + Other)
			{
				throw OverflowException();
			}
			if (Other > 0 && _Value < GetMinValue() + Other)
			{
				throw OverflowException();
			}

			return Numeric(_Value - Other);
		}

		inline Numeric operator*(const Numeric& Other) const
		{
			return this->operator*(Other._Value);
		}

		inline Numeric operator*(const T Other) const
		{
			if (_Value == -1 && Other == GetMinValue())
			{
				throw OverflowException();
			}
			if (Other == -1 && _Value == GetMinValue())
			{
				throw OverflowException();
			}
			if (_Value > -1 && (_Value > GetMaxValue() / Other))
			{
				throw OverflowException();
			}
			if (_Value > -1 && (_Value < GetMinValue() / Other))
			{
				throw OverflowException();
			}

			return Numeric(_Value * Other);
		}

		inline Numeric operator/(const Numeric& Other) const
		{
			return this->operator/(Other._Value);
		}

		inline Numeric operator/(const T Other) const
		{
			if (_Value == GetMinValue() && Other == -1)
			{
				throw OverflowException();
			}
			if (_Value == -1 && Other == GetMinValue())
			{
				throw OverflowException();
			}
			if (Other == 0)
			{
				throw DivideByZeroException();
			}

			return Numeric(_Value / Other);
		}
	public:
		inline constexpr Numeric operator%(const Numeric& Other) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value % Other._Value);
		}

		inline constexpr Numeric operator%(const T Value) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value % Value);
		}

		inline constexpr Numeric operator<<(const Numeric& Other) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value << Other._Value);
		}

		inline constexpr Numeric operator<<(const T Value) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value << Value);
		}

		inline constexpr Numeric operator>>(const Numeric& Other) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value >> Other._Value);
		}

		inline constexpr Numeric operator>>(const T Value) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value >> Value);
		}
		
		inline constexpr Numeric operator&(const Numeric& Other) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value & Other._Value);
		}

		inline constexpr Numeric operator&(const T Value) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value & Value);
		}

		inline constexpr Numeric operator|(const Numeric& Other) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value | Other._Value);
		}

		inline constexpr Numeric operator|(const T Value) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value | Value);
		}

		inline constexpr Numeric operator^(const Numeric& Other) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value ^ Other._Value);
		}

		inline constexpr Numeric operator^(const T Value) const
			requires Elysium::Core::Template::Concepts::Integral<T>
		{
			return Numeric(_Value ^ Value);
		}
	private:
		T _Value;
	};
}
#endif