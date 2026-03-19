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

		Numeric(const T Value);

		Numeric(const Numeric& Source);

		Numeric(Numeric&& Right) noexcept;

		constexpr ~Numeric() = default;
	public:
		Numeric& operator=(const Numeric& Source);

		Numeric& operator=(const T Value);

		Numeric& operator=(Numeric&& Right) noexcept;
	public:
		static constexpr const T GetMinValue() noexcept;

		static constexpr const T GetMaxValue() noexcept;

		static constexpr const bool GetIsSigned() noexcept;
	public:
		explicit operator T();
	public:
		bool operator==(const Numeric& Other) const;

		bool operator!=(const Numeric& Other) const;

		bool operator<(const Numeric& Other) const;

		bool operator>(const Numeric& Other) const;

		bool operator<=(const Numeric& Other) const;

		bool operator>=(const Numeric& Other) const;
	public:
		bool operator==(const T Other) const;

		bool operator!=(const T Other) const;

		bool operator<(const T Other) const;

		bool operator>(const T Other) const;

		bool operator<=(const T Other) const;

		bool operator>=(const T Other) const;
	public:
		Numeric& operator++();

		Numeric operator++(int);

		Numeric& operator--();

		Numeric operator--(int);
	public:
		Numeric& operator+=(const Numeric& Other);
		Numeric& operator+=(const T Other);

		Numeric& operator-=(const Numeric& Other);
		Numeric& operator-=(const T Other);

		Numeric& operator*=(const Numeric& Other);
		Numeric& operator*=(const T Other);

		Numeric& operator/=(const Numeric& Other);
		Numeric& operator/=(const T Other);
		/*
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
		*/
	public:
		Numeric operator+(const Numeric& Other);
		Numeric operator+(const T Other);

		Numeric operator-(const Numeric& Other);
		Numeric operator-(const T Other);

		Numeric operator*(const Numeric& Other);
		Numeric operator*(const T Other);

		Numeric operator/(const Numeric& Other);
		Numeric operator/(const T Other);
		/*
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
		*/
	private:
		T _Value;
	};

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T>::Numeric(const T Value)
		: _Value(Value)
	{}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T>::Numeric(const Numeric & Source)
		: _Value(Source._Value)
	{ }

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T>::Numeric(Numeric && Right) noexcept
		: _Value(0)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator=(const Numeric & Source)
	{
		if (this != &Source)
		{
			_Value = Source._Value;
		}

		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator=(const T Value)
	{
		_Value = Value;

		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator=(Numeric && Right) noexcept
	{
		if (this != &Right)
		{
			_Value = Elysium::Core::Template::Functional::Move(Right._Value);
		}

		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline constexpr const T Numeric<T>::GetMinValue() noexcept
	{
		return Elysium::Core::Template::Numeric::NumericTraits<T>::Minimum;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline constexpr const T Numeric<T>::GetMaxValue() noexcept
	{
		return Elysium::Core::Template::Numeric::NumericTraits<T>::Maximum;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline constexpr const bool Numeric<T>::GetIsSigned() noexcept
	{
		return Elysium::Core::Template::Numeric::NumericTraits<T>::IsSigned;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T>::operator T()
	{
		return _Value;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator==(const Numeric & Other) const
	{
		return _Value == Other._Value;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator!=(const Numeric & Other) const
	{
		return _Value != Other._Value;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator<(const Numeric & Other) const
	{
		return _Value < Other._Value;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator>(const Numeric & Other) const
	{
		return _Value > Other._Value;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator<=(const Numeric & Other) const
	{
		return _Value <= Other._Value;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator>=(const Numeric & Other) const
	{
		return _Value >= Other._Value;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator==(const T Other) const
	{
		return _Value == Other;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator!=(const T Other) const
	{
		return _Value != Other;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator<(const T Other) const
	{
		return _Value < Other;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator>(const T Other) const
	{
		return _Value > Other;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator<=(const T Other) const
	{
		return _Value <= Other;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline bool Numeric<T>::operator>=(const T Other) const
	{
		return _Value >= Other;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator++()
	{
		if (_Value == GetMaxValue())
		{
			throw OverflowException();
		}

		_Value++;

		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator++(int)
	{
		Numeric<T> Result = Numeric<T>(*this);
		++(*this);
		return Result;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator--()
	{
		if (_Value == GetMinValue())
		{
			throw OverflowException();
		}

		_Value--;

		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator--(int)
	{
		Numeric<T> Result = Numeric<T>(*this);
		--(*this);
		return Result;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator+=(const Numeric & Other)
	{
		return this->operator+=(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator+=(const T Other)
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

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator-=(const Numeric & Other)
	{
		return this->operator-=(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator-=(const T Other)
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

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator*=(const Numeric & Other)
	{
		return this->operator*=(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator*=(const T Other)
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

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator/=(const Numeric & Other)
	{
		return this->operator/=(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator/=(const T Other)
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
	/*
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator%=(const Numeric & Other)
	{
		return this->operator%=(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator%=(const T Other)
	{
		_Value %= Other;

		return *this;
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator<<=(const Numeric & Other)
	{
		return this->operator<<=(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator<<=(const T Other)
	{
		_Value <<= Other;

		return *this;
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator>>=(const Numeric & Other)
	{
		return this->operator>>=(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator>>=(const T Other)
	{
		_Value >>= Other;

		return *this;
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator&=(const Numeric & Other)
	{
		return this->operator&=(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator&=(const T Other)
	{
		_Value &= Other;

		return *this;
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator|=(const Numeric & Other)
	{
		return this->operator|=(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator|=(const T Other)
	{
		_Value |= Other;

		return *this;
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator^=(const Numeric & Other)
	{
		return this->operator^=(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> & Numeric<T>::operator^=(const T Other)
	{
		_Value ^= Other;

		return *this;
	}
	*/
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator+(const Numeric & Other)
	{
		return this->operator+(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator+(const T Other)
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

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator-(const Numeric & Other)
	{
		return this->operator-(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator-(const T Other)
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

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator*(const Numeric & Other)
	{
		return this->operator*(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator*(const T Other)
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

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator/(const Numeric & Other)
	{
		return this->operator/(Other._Value);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator/(const T Other)
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
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator%(const Numeric & Other)
	{
		return this->operator%(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator%(const T Other)
	{
		return Numeric(_Value % Other);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator<<(const Numeric & Other)
	{
		return this->operator<<(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator<<(const T Other)
	{
		return Numeric(_Value << Other);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator>>(const Numeric & Other)
	{
		return this->operator>>(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator>>(const T Other)
	{
		return Numeric(_Value >> Other);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator&(const Numeric & Other)
	{
		return this->operator&(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator&(const T Other)
	{
		return Numeric(_Value & Other);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator|(const Numeric & Other)
	{
		return this->operator|(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator|(const T Other)
	{
		return Numeric(_Value | Other);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator^(const Numeric & Other)
	{
		return this->operator^(Other._Value);
	}
	
	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline Numeric<T> Numeric<T>::operator^(const T Other)
	{
		return Numeric(_Value ^ Other);
	}
	*/
}
#endif