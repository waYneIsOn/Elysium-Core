/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#define ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ARITHMETIC
#include "Arithmetic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "Absolute.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_POWER
#include "Power.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_TRUNCATE
#include "Truncate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNED
#include "IsSigned.hpp"
#endif

namespace Elysium::Core::Template::Numeric
{
	template <Elysium::Core::Template::Concepts::Arithmetic T>
	class _NumericTraitsBase
	{
	public:
		using Value = T;
		using ConstValue = const T;
	public:
		/// <summary>
		/// Returns the number of bytes required to represent this integer-type.
		/// </summary>
		static constexpr const System::uint8_t ByteLength = sizeof(T);

		/// <summary>
		/// 
		/// </summary>
		static constexpr const bool IsSigned = Elysium::Core::Template::TypeTraits::IsSignedValue<T>;

		/// <summary>
		/// 
		/// </summary>
		static constexpr ConstValue Minimum = IsSigned ? static_cast<ConstValue>(1_ui64 << (ByteLength * 8 - 1)) : 0;

		/// <summary>
		/// 
		/// </summary>
		static constexpr ConstValue Maximum = IsSigned ? static_cast<ConstValue>(((1_ui64 << (ByteLength * 8 - 1)) + 1) * -1) : -1;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsPositive(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsPrimeNumber(ConstValue Value) noexcept;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr System::uint8_t GetDigitCount(Value Value) noexcept;
	};

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline constexpr const bool _NumericTraitsBase<T>::IsPositive(ConstValue Value) noexcept
	{
		return Value > 0;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline constexpr const bool _NumericTraitsBase<T>::IsPrimeNumber(ConstValue Input) noexcept
	{
		if (Input < 0x02)
		{
			return false;
		}

		for (Value i = 2; i <= Input / 2; i++)
		{
			if (Input % i == 0)
			{
				return false;
			}
		}

		return true;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic T>
	inline constexpr System::uint8_t _NumericTraitsBase<T>::GetDigitCount(Value Value) noexcept
	{
		System::uint8_t Result = 0;
		while (Value > 0)
		{
			Value /= 10;
			Result++;
		}

		return Result;
	}

	template <Elysium::Core::Template::Concepts::Arithmetic T>
	class NumericTraits
	{ };

	template <>
	class NumericTraits<System::uint8_t>
		: public _NumericTraitsBase<System::uint8_t>
	{ };

	template <>
	class NumericTraits<System::uint16_t>
		: public _NumericTraitsBase<System::uint16_t>
	{
	public:
		static constexpr const System::uint8_t GetHigh(ConstValue Value) noexcept;

		static constexpr const System::uint8_t GetLow(ConstValue Value) noexcept;
	};

	inline constexpr const System::uint8_t NumericTraits<System::uint16_t>::GetHigh(ConstValue Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value >> 8 & 0xFF;
		//return ((System::uint8_t*)&Value)[1];	// doesn't allow for constexpr
#else
		return Value & 0xFF;
#endif
	}

	inline constexpr const System::uint8_t NumericTraits<System::uint16_t>::GetLow(ConstValue Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value & 0xFF;
		//return ((System::uint8_t*)&Value)[0];	// doesn't allow for constexpr
#else
		return Value >> 8 & 0xFF;
#endif
	}
	
	template <>
	class NumericTraits<System::uint32_t>
		: public _NumericTraitsBase<System::uint32_t>
	{
	public:
		static constexpr const System::uint16_t GetHigh(ConstValue Value) noexcept;

		static constexpr const System::uint16_t GetLow(ConstValue Value) noexcept;
	};

	inline constexpr const System::uint16_t NumericTraits<System::uint32_t>::GetHigh(ConstValue Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value >> 16 & 0xFFFF;
#else
		return Value & 0xFFFF;
#endif
	}

	inline constexpr const System::uint16_t NumericTraits<System::uint32_t>::GetLow(ConstValue Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value & 0xFFFF;
#else
		return Value >> 16 & 0xFFFF;
#endif
	}
	
	template <>
	class NumericTraits<System::uint64_t>
		: public _NumericTraitsBase<System::uint64_t>
	{
	public:
		static constexpr const System::uint32_t GetHigh(ConstValue Value) noexcept;

		static constexpr const System::uint32_t GetLow(ConstValue Value) noexcept;
	};

	inline constexpr const System::uint32_t NumericTraits<System::uint64_t>::GetHigh(ConstValue Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value >> 32 & 0xFFFFFFFF;
#else
		return Value & 0xFFFFFFFF;
#endif
	}

	inline constexpr const System::uint32_t NumericTraits<System::uint64_t>::GetLow(ConstValue Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value & 0xFFFFFFFF;
#else
		return Value >> 32 & 0xFFFFFFFF;
#endif
	}

	template <>
	class NumericTraits<System::int8_t>
		: public _NumericTraitsBase<System::int8_t>
	{ };

	template <>
	class NumericTraits<System::int16_t>
		: public _NumericTraitsBase<System::int16_t>
	{
	/*
	public:
		static constexpr const System::uint8_t GetHigh(ConstValue Value);

		static constexpr const System::uint8_t GetLow(ConstValue Value);
	*/
	};

	template <>
	class NumericTraits<System::int32_t>
		: public _NumericTraitsBase<System::int32_t>
	{
		/*
		public:
			static constexpr const System::uint16_t GetHigh(ConstValue Value);

			static constexpr const System::uint16_t GetLow(ConstValue Value);
		*/
	};

	template <>
	class NumericTraits<System::int64_t>
		: public _NumericTraitsBase<System::int64_t>
	{
		/*
		public:
			static constexpr const System::int32_t GetHigh(ConstValue Value);

			static constexpr const System::int32_t GetLow(ConstValue Value);
		*/
	};

	template <>
	struct NumericTraits<float>
		: public _NumericTraitsBase<float>
	{
	public:
		static constexpr const bool IsNaN(ConstValue Value) noexcept;

		static constexpr const Elysium::Core::Template::System::int64_t GetValuePreDecimalPoint(ConstValue Value) noexcept;

		static constexpr const Elysium::Core::Template::System::uint64_t GetValuePostDecimalPoint(ConstValue Value,
			const Elysium::Core::Template::System::uint8_t NumberOfDigits) noexcept;
	};

	inline constexpr const bool NumericTraits<float>::IsNaN(ConstValue Value) noexcept
	{
		return Value != Value;
	}

	inline constexpr const Elysium::Core::Template::System::int64_t NumericTraits<float>::GetValuePreDecimalPoint(ConstValue Value) noexcept
	{
		return static_cast<Elysium::Core::Template::System::int64_t>(Value);
	}

	inline constexpr const Elysium::Core::Template::System::uint64_t NumericTraits<float>::GetValuePostDecimalPoint(ConstValue Value, const Elysium::Core::Template::System::uint8_t NumberOfDigits) noexcept
	{
		const Elysium::Core::Template::System::int64_t TruncatedValue =
			Elysium::Core::Template::Math::Truncate<float, Elysium::Core::Template::System::int64_t>(Value);
		const double FractionalValue = Elysium::Core::Template::Math::Absolute(Value - TruncatedValue);
		const double Factor = Elysium::Core::Template::Math::Power(10.0, NumberOfDigits);

		return static_cast<Elysium::Core::Template::System::uint64_t>(FractionalValue * Factor);
	}

	template <>
	struct NumericTraits<double>
		: public _NumericTraitsBase<double>
	{
	public:
		static constexpr const bool IsNaN(ConstValue Value) noexcept;

		static constexpr const Elysium::Core::Template::System::int64_t GetValuePreDecimalPoint(ConstValue Value) noexcept;

		static constexpr const Elysium::Core::Template::System::uint64_t GetValuePostDecimalPoint(ConstValue Value,
			const Elysium::Core::Template::System::uint8_t NumberOfDigits) noexcept;
	};
	
	inline constexpr const bool NumericTraits<double>::IsNaN(ConstValue Value) noexcept
	{
		return Value != Value;
	}

	inline constexpr const Elysium::Core::Template::System::int64_t NumericTraits<double>::GetValuePreDecimalPoint(ConstValue Value) noexcept
	{
		return static_cast<Elysium::Core::Template::System::int64_t>(Value);
	}

	inline constexpr const Elysium::Core::Template::System::uint64_t NumericTraits<double>::GetValuePostDecimalPoint(ConstValue Value, const Elysium::Core::Template::System::uint8_t NumberOfDigits) noexcept
	{
		const Elysium::Core::Template::System::int64_t TruncatedValue = 
			Elysium::Core::Template::Math::Truncate<double, Elysium::Core::Template::System::int64_t>(Value);
		const double FractionalValue = Elysium::Core::Template::Math::Absolute(Value - TruncatedValue);
		const double Factor = Elysium::Core::Template::Math::Power(10.0, NumberOfDigits);

		return static_cast<Elysium::Core::Template::System::uint64_t>(FractionalValue * Factor);
	}
	
	/*
	template <>
	struct NumericTraits<long double>
		: public _NumericTraitsBase<long double>
	{
	public:
		static constexpr const bool IsNaN(ConstValue Value) noexcept;

		static constexpr const Elysium::Core::Template::System::int64_t GetPreDecimalPoint(ConstValue Value) noexcept;

		static constexpr const Elysium::Core::Template::System::uint64_t GetPostDecimalPoint(ConstValue Value,
			const Elysium::Core::Template::System::uint8_t NumberOfDigits) noexcept;
	};
	*/
}
#endif
