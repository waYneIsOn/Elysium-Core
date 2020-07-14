/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_INTEGER
#define ELYSIUM_CORE_INTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
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

namespace Elysium::Core
{
	typedef char int8_t;
	typedef short int16_t;
	typedef int int32_t;
	typedef long long int64_t;

	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;
	typedef unsigned long long uint64_t;

	template<class T, typename Enabled = void>
	class Integer
	{
	public:
		Integer();
		Integer(const T Value);
		Integer(const Integer& Source);
		Integer(Integer&& Right) noexcept;
		~Integer();

		Integer& operator=(const Integer& Source);
		Integer& operator=(const T Source);
		Integer& operator=(Integer&& Right) noexcept;
		Integer& operator=(T&& Right) noexcept;

		static constexpr const T GetMinValue() noexcept;
		static constexpr const T GetMaxValue() noexcept;

		static constexpr const bool GetIsSigned() noexcept;

		explicit operator T();

		bool operator==(const Integer& Other) const;
		bool operator!=(const Integer& Other) const;
		bool operator<(const Integer& Other) const;
		bool operator>(const Integer& Other) const;
		bool operator<=(const Integer& Other) const;
		bool operator>=(const Integer& Other) const;
		


		Integer& operator+=(const Integer& Other);
		Integer& operator+=(const T Other);

		Integer& operator-=(const Integer& Other);
		Integer& operator-=(const T Other);

		Integer& operator*=(const Integer& Other);
		Integer& operator*=(const T Other);

		//FloatingPoint& operator/=(const Integer& Other);
		//FloatingPoint& operator/=(const T Other);

		Integer& operator%=(const Integer& Other);
		Integer& operator%=(const T Other);



		Integer operator+(const Integer& Other);
		Integer operator+(const T Other);

		Integer operator-(const Integer& Other);
		Integer operator-(const T Other);

		Integer operator*(const Integer& Other);
		Integer operator*(const T Other);

		//FloatingPoint operator/(const Integer& Other);
		//FloatingPoint operator/(const T Other);

		Integer operator%(const Integer& Other);
		Integer operator%(const T VOtheralue);
		


		Integer& operator++();
		Integer& operator++(int);

		Integer& operator--();
		Integer& operator--(int);
	private:
		T _Value;
	};

	template<class T, typename Enabled>
	inline Integer<T, Enabled>::Integer()
		: _Value(0)
	{ }
	template<class T, typename Enabled>
	inline Integer<T, Enabled>::Integer(const T Value)
		: _Value(Value)
	{ }
	template<class T, typename Enabled>
	inline Integer<T, Enabled>::Integer(const Integer & Source)
		: _Value(Source._Value)
	{ }
	template<class T, typename Enabled>
	inline Integer<T, Enabled>::Integer(Integer && Right) noexcept
		: _Value(0)
	{
		*this = std::move(Right);
	}
	template<class T, typename Enabled>
	inline Integer<T, Enabled>::~Integer()
	{ }

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator=(const Integer & Source)
	{
		if (this != &Source)
		{
			_Value = Source._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator=(const T Source)
	{
		_Value = Source;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator=(Integer && Right) noexcept
	{
		if (this != &Right)
		{
			_Value = std::move(Right._Value);
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator=(T && Right) noexcept
	{
		_Value = std::move(Right);

		return *this;
	}

	template<class T, typename Enabled>
	inline constexpr const T Integer<T, Enabled>::GetMinValue() noexcept
	{
		return (std::numeric_limits<T>::min)();
	}

	template<class T, typename Enabled>
	inline constexpr const T Integer<T, Enabled>::GetMaxValue() noexcept
	{
		return (std::numeric_limits<T>::max)();
	}

	template<class T, typename Enabled>
	inline constexpr const bool Integer<T, Enabled>::GetIsSigned() noexcept
	{
		return std::is_signed<T>();
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled>::operator T()
	{
		return _Value;
	}

	template<class T, typename Enabled>
	inline bool Integer<T, Enabled>::operator==(const Integer & Other) const
	{
		return _Value == Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Integer<T, Enabled>::operator!=(const Integer & Other) const
	{
		return _Value != Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Integer<T, Enabled>::operator<(const Integer & Other) const
	{
		return _Value < Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Integer<T, Enabled>::operator>(const Integer & Other) const
	{
		return _Value > Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Integer<T, Enabled>::operator<=(const Integer & Other) const
	{
		return _Value <= Other._Value;
	}

	template<class T, typename Enabled>
	inline bool Integer<T, Enabled>::operator>=(const Integer & Other) const
	{
		return _Value >= Other._Value;
	}
	
	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator+=(const Integer & Other)
	{
		return this->operator+=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator+=(const T Other)
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
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator-=(const Integer & Other)
	{
		return this->operator-=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator-=(const T Other)
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
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator*=(const Integer & Other)
	{
		return this->operator*=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator*=(const T Other)
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
		
		_Value *= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator%=(const Integer & Other)
	{
		return this->operator%=(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator%=(const T Other)
	{
		_Value %= Other;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator+(const Integer & Other)
	{
		return this->operator+(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator+(const T Other)
	{
		if (Other > 0 && _Value > GetMaxValue() - Other)
		{
			throw OverflowException();
		}
		if (Other < 0 && _Value < GetMinValue() - Other)
		{
			throw OverflowException();
		}

		return Integer(_Value + Other);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator-(const Integer & Other)
	{
		return this->operator-(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator-(const T Other)
	{
		if (Other < 0 && _Value > GetMaxValue() + Other)
		{
			throw OverflowException();
		}
		if (Other > 0 && _Value < GetMinValue() + Other)
		{
			throw OverflowException();
		}

		return Integer(_Value - Other);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator*(const Integer & Other)
	{
		return this->operator*(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator*(const T Other)
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

		return Integer(_Value * Other);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator%(const Integer & Other)
	{
		return this->operator%(Other._Value);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> Integer<T, Enabled>::operator%(const T Other)
	{
		return Integer(_Value % Other);
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator++()
	{
		if (_Value == GetMaxValue())
		{
			throw OverflowException();
		}

		_Value++;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator++(int)
	{
		Integer<T, Enabled> Result = Integer<T, Enabled>(*this);
		++(*this);
		return Result;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator--()
	{
		if (_Value == GetMinValue())
		{
			throw OverflowException();
		}

		_Value--;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator--(int)
	{
		Integer<T, Enabled> Result = Integer<T, Enabled>(*this);
		--(*this);
		return Result;
	}

	// integral type integer specialization
	template<class T>
	class Integer<T, std::enable_if<std::is_integral<T>::value, T>>
	{ };

	// safe integer aliases
	typedef Integer<int16_t> Int16;
	typedef Integer<uint16_t> UInt16;
	typedef Integer<int32_t> Int32;
	typedef Integer<uint32_t> UInt32;
	typedef Integer<int64_t> Int64;
	typedef Integer<uint64_t> UInt64;
}
#endif
