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

#ifndef _LIMITS_
#include <limits>
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_OVERFLOWEXCEPTION
#include "OverflowException.hpp"
#endif

#ifndef ELYSIUM_CORE_DIVIDEBYZEROEXCEPTION
#include "DivideByZeroException.hpp"
#endif

namespace Elysium::Core
{
	template<class T, typename Enabled = void>
	class Numeric
	{
	public:
		Numeric();
		Numeric(const T Value);
		Numeric(const Numeric& Source);
		Numeric(Numeric&& Right) noexcept;
		~Numeric();

		Numeric& operator=(const Numeric& Source);
		Numeric& operator=(const T Value);
		Numeric& operator=(Numeric&& Right) noexcept;

		static constexpr const T GetMinValue() noexcept;
		static constexpr const T GetMaxValue() noexcept;

		static constexpr const bool GetIsSigned() noexcept;

		explicit operator T();

		bool operator==(const Numeric& Other) const;
		bool operator!=(const Numeric& Other) const;
		bool operator<(const Numeric& Other) const;
		bool operator>(const Numeric& Other) const;
		bool operator<=(const Numeric& Other) const;
		bool operator>=(const Numeric& Other) const;

		Numeric& operator++();
		Numeric operator++(int);

		Numeric& operator--();
		Numeric operator--(int);

		Numeric& operator+=(const Numeric& Other);
		Numeric& operator+=(const T Other);

		Numeric& operator-=(const Numeric& Other);
		Numeric& operator-=(const T Other);

		Numeric& operator*=(const Numeric& Other);
		Numeric& operator*=(const T Other);

		Numeric& operator/=(const Numeric& Other);
		Numeric& operator/=(const T Other);

		Numeric& operator%=(const Numeric& Other);
		Numeric& operator%=(const T Other);

		Numeric& operator<<=(const Numeric& Other);
		Numeric& operator<<=(const T Other);

		Numeric& operator>>=(const Numeric& Other);
		Numeric& operator>>=(const T Other);

		Numeric& operator&=(const Numeric& Other);
		Numeric& operator&=(const T Other);

		Numeric& operator|=(const Numeric& Other);
		Numeric& operator|=(const T Other);

		Numeric& operator^=(const Numeric& Other);
		Numeric& operator^=(const T Other);

		Numeric operator+(const Numeric& Other);
		Numeric operator+(const T Other);

		Numeric operator-(const Numeric& Other);
		Numeric operator-(const T Other);

		Numeric operator*(const Numeric& Other);
		Numeric operator*(const T Other);

		Numeric operator/(const Numeric& Other);
		Numeric operator/(const T Other);

		Numeric operator%(const Numeric& Other);
		Numeric operator%(const T VOtheralue);

		Numeric operator<<(const Numeric& Other);
		Numeric operator<<(const T Other);

		Numeric operator>>(const Numeric& Other);
		Numeric operator>>(const T Other);

		Numeric operator&(const Numeric& Other);
		Numeric operator&(const T Other);

		Numeric operator|(const Numeric& Other);
		Numeric operator|(const T Other);

		Numeric operator^(const Numeric& Other);
		Numeric operator^(const T Other);
	private:
		T _Value;
	};

	template<class T, typename Enabled>
	inline Numeric<T, Enabled>::Numeric()
		: _Value(0)
	{ }

	template<class T, typename Enabled>
	inline Numeric<T, Enabled>::Numeric(const T Value)
		: _Value(Value)
	{ }

	template<class T, typename Enabled>
	inline Numeric<T, Enabled>::Numeric(const Numeric & Source)
		: _Value(Source._Value)
	{ }

	template<class T, typename Enabled>
	inline Numeric<T, Enabled>::Numeric(Numeric && Right) noexcept
		: _Value(0)
	{
		*this = std::move(Right);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled>::~Numeric()
	{ }

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator=(const Numeric & Source)
	{
		if (this != &Source)
		{
			_Value = Source._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator=(const T Value)
	{
		_Value = Value;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator=(Numeric && Right) noexcept
	{
		if (this != &Right)
		{
			_Value = std::move(Right._Value);
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline constexpr const T Numeric<T, Enabled>::GetMinValue() noexcept
	{
		return (std::numeric_limits<T>::min)();
	}

	template<class T, typename Enabled>
	inline constexpr const T Numeric<T, Enabled>::GetMaxValue() noexcept
	{
		return (std::numeric_limits<T>::max)();
	}

	template<class T, typename Enabled>
	inline constexpr const bool Numeric<T, Enabled>::GetIsSigned() noexcept
	{
		return std::is_signed<T>();
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled>::operator T()
	{
		return _Value;
	}

	template<class T, typename Enabled>
	inline bool Numeric<T, Enabled>::operator==(const Numeric & Other) const
	{
		return _Value == Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Numeric<T, Enabled>::operator!=(const Numeric & Other) const
	{
		return _Value != Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Numeric<T, Enabled>::operator<(const Numeric & Other) const
	{
		return _Value < Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Numeric<T, Enabled>::operator>(const Numeric & Other) const
	{
		return _Value > Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Numeric<T, Enabled>::operator<=(const Numeric & Other) const
	{
		return _Value <= Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Numeric<T, Enabled>::operator>=(const Numeric & Other) const
	{
		return _Value >= Other._Value;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator++()
	{
		if (_Value == GetMaxValue())
		{
			throw OverflowException();
		}

		_Value++;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator++(int)
	{
		Numeric<T, Enabled> Result = Numeric<T, Enabled>(*this);
		++(*this);
		return Result;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator--()
	{
		if (_Value == GetMinValue())
		{
			throw OverflowException();
		}

		_Value--;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator--(int)
	{
		Numeric<T, Enabled> Result = Numeric<T, Enabled>(*this);
		--(*this);
		return Result;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator+=(const Numeric & Other)
	{
		return this->operator+=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator+=(const T Other)
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

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator-=(const Numeric & Other)
	{
		return this->operator-=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator-=(const T Other)
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

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator*=(const Numeric & Other)
	{
		return this->operator*=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator*=(const T Other)
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

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator/=(const Numeric & Other)
	{
		return this->operator/=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator/=(const T Other)
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

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator%=(const Numeric & Other)
	{
		return this->operator%=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator%=(const T Other)
	{
		_Value %= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator<<=(const Numeric & Other)
	{
		return this->operator<<=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator<<=(const T Other)
	{
		_Value <<= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator>>=(const Numeric & Other)
	{
		return this->operator>>=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator>>=(const T Other)
	{
		_Value >>= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator&=(const Numeric & Other)
	{
		return this->operator&=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator&=(const T Other)
	{
		_Value &= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator|=(const Numeric & Other)
	{
		return this->operator|=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator|=(const T Other)
	{
		_Value |= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator^=(const Numeric & Other)
	{
		return this->operator^=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> & Numeric<T, Enabled>::operator^=(const T Other)
	{
		_Value ^= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator+(const Numeric & Other)
	{
		return this->operator+(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator+(const T Other)
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

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator-(const Numeric & Other)
	{
		return this->operator-(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator-(const T Other)
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

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator*(const Numeric & Other)
	{
		return this->operator*(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator*(const T Other)
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

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator/(const Numeric & Other)
	{
		return this->operator/(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator/(const T Other)
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
	/*
	template<class T>
	inline Numeric<T, std::enable_if<std::is_signed<T>::value, T>> Numeric<T, std::enable_if<std::is_signed<T>::value, T>>::operator/(const T Other)
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
	*/
	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator%(const Numeric & Other)
	{
		return this->operator%(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator%(const T Other)
	{
		return Numeric(_Value % Other);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator<<(const Numeric & Other)
	{
		return this->operator<<(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator<<(const T Other)
	{
		return Numeric(_Value << Other);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator>>(const Numeric & Other)
	{
		return this->operator>>(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator>>(const T Other)
	{
		return Numeric(_Value >> Other);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator&(const Numeric & Other)
	{
		return this->operator&(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator&(const T Other)
	{
		return Numeric(_Value & Other);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator|(const Numeric & Other)
	{
		return this->operator|(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator|(const T Other)
	{
		return Numeric(_Value | Other);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator^(const Numeric & Other)
	{
		return this->operator^(Other._Value);
	}

	template<class T, typename Enabled>
	inline Numeric<T, Enabled> Numeric<T, Enabled>::operator^(const T Other)
	{
		return Numeric(_Value ^ Other);
	}
}
#endif