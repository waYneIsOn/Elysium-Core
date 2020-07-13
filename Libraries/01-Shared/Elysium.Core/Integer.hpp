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

		Integer& operator+(const Integer& Value);
		Integer& operator+(const T Value);

		Integer& operator-(const Integer& Value);
		Integer& operator-(const T Value);

		Integer& operator*(const Integer& Value);
		Integer& operator*(const T Value);

		Integer& operator+=(const Integer& Value);
		Integer& operator+=(const T Value);

		Integer& operator-=(const Integer& Value);
		Integer& operator-=(const T Value);

		Integer& operator*=(const Integer& Value);
		Integer& operator*=(const T Value);
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
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator+(const Integer & Value)
	{
		if (this != &Value)
		{
			if (Value._Value > 0 && _Value > GetMaxValue() - Value._Value)
			{
				throw OverflowException();
			}
			if (Value._Value < 0 && _Value < GetMinValue() - Value._Value)
			{
				throw OverflowException();
			}

			_Value += Value._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator+(const T Value)
	{
		if (Value > 0 && _Value > GetMaxValue() - Value)
		{
			throw OverflowException();
		}
		if (Value < 0 && _Value < GetMinValue() - Value)
		{
			throw OverflowException();
		}

		_Value += Value;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator-(const Integer & Value)
	{
		if (this != &Value)
		{
			if (Value._Value < 0 && _Value > GetMaxValue() + Value._Value)
			{
				throw OverflowException();
			}
			if (Value._Value > 0 && _Value < GetMinValue() + Value._Value)
			{
				throw OverflowException();
			}

			_Value -= Value._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator-(const T Value)
	{
		if (Value < 0 && _Value > GetMaxValue() + Value)
		{
			throw OverflowException();
		}
		if (Value > 0 && _Value < GetMinValue() + Value)
		{
			throw OverflowException();
		}

		_Value -= Value;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator*(const Integer & Value)
	{
		if (this != &Value)
		{
			if (_Value == -1 && Value._Value == GetMinValue())
			{
				throw OverflowException();
			}
			if (Value._Value == -1 && _Value == GetMinValue())
			{
				throw OverflowException();
			}
			if (_Value > GetMaxValue() / Value._Value)
			{
				throw OverflowException();
			}
			if (_Value < GetMinValue() / Value._Value)
			{
				throw OverflowException();
			}

			_Value *= Value._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator*(const T Value)
	{
		if (_Value == -1 && Value == GetMinValue())
		{
			throw OverflowException();
		}
		if (Value == -1 && _Value == GetMinValue())
		{
			throw OverflowException();
		}
		if (_Value > GetMaxValue() / Value)
		{
			throw OverflowException();
		}
		if (_Value < GetMinValue() / Value)
		{
			throw OverflowException();
		}
		
		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator+=(const Integer & Value)
	{
		if (this != &Value)
		{
			if (Value._Value > 0 && _Value > GetMaxValue() - Value._Value)
			{
				throw OverflowException();
			}
			if (Value._Value < 0 && _Value < GetMinValue() - Value._Value)
			{
				throw OverflowException();
			}

			_Value += Value._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator+=(const T Value)
	{
		if (Value > 0 && _Value > GetMaxValue() - Value)
		{
			throw OverflowException();
		}
		if (Value < 0 && _Value < GetMinValue() - Value)
		{
			throw OverflowException();
		}

		_Value += Value;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator-=(const Integer & Value)
	{
		if (this != &Value)
		{
			if (Value._Value < 0 && _Value > GetMaxValue() + Value._Value)
			{
				throw OverflowException();
			}
			if (Value._Value > 0 && _Value < GetMinValue() + Value._Value)
			{
				throw OverflowException();
			}

			_Value -= Value._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator-=(const T Value)
	{
		if (Value < 0 && _Value > GetMaxValue() + Value)
		{
			throw OverflowException();
		}
		if (Value > 0 && _Value < GetMinValue() + Value)
		{
			throw OverflowException();
		}

		_Value -= Value;

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator*=(const Integer & Value)
	{
		if (this != &Value)
		{
			if (_Value == -1 && Value._Value == GetMinValue())
			{
				throw OverflowException();
			}
			if (Value._Value == -1 && _Value == GetMinValue())
			{
				throw OverflowException();
			}
			if (_Value > GetMaxValue() / Value._Value)
			{
				throw OverflowException();
			}
			if (_Value < GetMinValue() / Value._Value)
			{
				throw OverflowException();
			}

			_Value *= Value._Value;
		}

		return *this;
	}

	template<class T, typename Enabled>
	inline Integer<T, Enabled> & Integer<T, Enabled>::operator*=(const T Value)
	{
		if (_Value == -1 && Value == GetMinValue())
		{
			throw OverflowException();
		}
		if (Value == -1 && _Value == GetMinValue())
		{
			throw OverflowException();
		}
		if (_Value > GetMaxValue() / Value)
		{
			throw OverflowException();
		}
		if (_Value < GetMinValue() / Value)
		{
			throw OverflowException();
		}

		return *this;
	}

	// integral type integer specialization
	template<class T>
	class Integer<T, std::enable_if<std::is_integral<T>::value, T>>
	{ };

	// simple integer aliases
	typedef char int8_t;
	typedef short int16_t;
	typedef int int32_t;
	typedef long long int64_t;

	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;
	typedef unsigned long long uint64_t;

	// safe integer aliases
	//typedef Integer<int8_t> Byte;
	//typedef Integer<uint8_t> SByte;
	typedef Integer<int16_t> Int16;
	typedef Integer<uint16_t> UInt16;
	typedef Integer<int32_t> Int32;
	typedef Integer<uint32_t> UInt32;
	typedef Integer<int64_t> Int64;
	typedef Integer<uint64_t> UInt64;
}
#endif
