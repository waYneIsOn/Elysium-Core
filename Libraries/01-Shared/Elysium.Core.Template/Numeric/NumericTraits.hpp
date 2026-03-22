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
#include "../Concepts/Arithmetic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_BITCAST
#include "../Functional/BitCast.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "../Math/Absolute.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_POWER
#include "../Math/Power.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_TRUNCATE
#include "../Math/Truncate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "../System/Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNED
#include "../TypeTraits/IsSigned.hpp"
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
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		inline static constexpr const bool IsPositive(ConstValue Value) noexcept
		{
			return Value > 0;
		}

	};
	
	template <Elysium::Core::Template::Concepts::Integer T>
	class _NumericTraitsBaseInteger
		: public _NumericTraitsBase<T>
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		static constexpr _NumericTraitsBase<T>::ConstValue Minimum = _NumericTraitsBase<T>::IsSigned ? 
			static_cast<_NumericTraitsBase<T>::ConstValue>(1_ui64 << (_NumericTraitsBase<T>::ByteLength * 8 - 1)) :
			0;

		/// <summary>
		/// 
		/// </summary>
		static constexpr _NumericTraitsBase<T>::ConstValue Maximum = _NumericTraitsBase<T>::IsSigned ? 
			static_cast<_NumericTraitsBase<T>::ConstValue>(((1_ui64 << (_NumericTraitsBase<T>::ByteLength * 8 - 1)) + 1) * -1) : 
			-1;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		inline static constexpr const bool IsPrimeNumber(_NumericTraitsBase<T>::ConstValue Input) noexcept
		{
			if (Input < 0x02)
			{
				return false;
			}

			for (T i = 2; i <= Input / 2; i++)
			{
				if (Input % i == 0)
				{
					return false;
				}
			}

			return true;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		inline static constexpr System::uint8_t GetDigitCount(_NumericTraitsBase<T>::Value Value) noexcept
		{
			System::uint8_t Result = 0;
			while (Value > 0)
			{
				Value /= 10;
				Result++;
			}

			return Result;
		}

	};

	template <Elysium::Core::Template::Concepts::FloatingPoint T>
	class _NumericTraitsBaseFloatingPoint
		: public _NumericTraitsBase<T>
	{
	public:
		static constexpr auto Test0 = 1_ui32 << 23;

		static constexpr auto Test1 = 1_ui64 << 52;
	public:
#pragma warning(push)
#pragma warning(disable: 4244)	// cast works correctly
		/// <summary>
		/// Sign:		0 ie. positive
		/// Exponent:	1 ie. smallest non-zero exponent
		/// Mantissa:	all zeroes
		/// </summary>
		static constexpr _NumericTraitsBase<T>::ConstValue Minimum = _NumericTraitsBase<T>::ByteLength == 4_ui8 ?
			Elysium::Core::Template::Functional::BitCast<const float>(1_ui32 << 23) :
			Elysium::Core::Template::Functional::BitCast<const double>(1_ui64 << 52);
		
		/// <summary>
		/// Sign:		0 ie. positive
		/// Exponent:	all ones except last bit (all ones ie. max is reserverd for infinite/NaN)
		/// Mantissa:	all ones
		/// </summary>
		static constexpr _NumericTraitsBase<T>::ConstValue Maximum = _NumericTraitsBase<T>::ByteLength == 4_ui8 ?
			Elysium::Core::Template::Functional::BitCast<const float>((254_ui32 << 23) | (1_ui32 << 23) - 1) :
			Elysium::Core::Template::Functional::BitCast<const double>((2046_ui64 << 52) | ((1_ui64 << 52) - 1));
#pragma warning(pop)
	};
	
	// ------------------------------------------------------------------------------------------------------------------------------

	template <Elysium::Core::Template::Concepts::Arithmetic T>
	class NumericTraits
	{ };
	
	template <>
	class NumericTraits<System::uint8_t>
		: public _NumericTraitsBaseInteger<System::uint8_t>
	{ };

	template <>
	class NumericTraits<System::uint16_t>
		: public _NumericTraitsBaseInteger<System::uint16_t>
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
		: public _NumericTraitsBaseInteger<System::uint32_t>
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
		: public _NumericTraitsBaseInteger<System::uint64_t>
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
		: public _NumericTraitsBaseInteger<System::int8_t>
	{ };

	template <>
	class NumericTraits<System::int16_t>
		: public _NumericTraitsBaseInteger<System::int16_t>
	{
	/*
	public:
		static constexpr const System::uint8_t GetHigh(ConstValue Value);

		static constexpr const System::uint8_t GetLow(ConstValue Value);
	*/
	};

	template <>
	class NumericTraits<System::int32_t>
		: public _NumericTraitsBaseInteger<System::int32_t>
	{
		/*
		public:
			static constexpr const System::uint16_t GetHigh(ConstValue Value);

			static constexpr const System::uint16_t GetLow(ConstValue Value);
		*/
	};

	template <>
	class NumericTraits<System::int64_t>
		: public _NumericTraitsBaseInteger<System::int64_t>
	{
		/*
		public:
			static constexpr const System::int32_t GetHigh(ConstValue Value);

			static constexpr const System::int32_t GetLow(ConstValue Value);
		*/
	};
	
	template <>
	struct NumericTraits<float>
		: public _NumericTraitsBaseFloatingPoint<float>
	{
	public:
		inline static constexpr const bool IsNaN(ConstValue Value) noexcept
		{
			return Value != Value;
		}

		inline static constexpr const Elysium::Core::Template::System::int64_t GetValuePreDecimalPoint(ConstValue Value) noexcept
		{
			return static_cast<Elysium::Core::Template::System::int64_t>(Value);
		}

		inline static constexpr const Elysium::Core::Template::System::uint64_t GetValuePostDecimalPoint(ConstValue Value,
			const Elysium::Core::Template::System::uint8_t NumberOfDigits) noexcept
		{
			const Elysium::Core::Template::System::int64_t TruncatedValue =
				Elysium::Core::Template::Math::Truncate<float, Elysium::Core::Template::System::int64_t>(Value);
			const double FractionalValue = Elysium::Core::Template::Math::Absolute(Value - TruncatedValue);
			const double Factor = Elysium::Core::Template::Math::Power(10.0, NumberOfDigits);

			return static_cast<Elysium::Core::Template::System::uint64_t>(FractionalValue * Factor);
		}
	};

	template <>
	struct NumericTraits<double>
		: public _NumericTraitsBaseFloatingPoint<double>
	{
	public:
		inline static constexpr const bool IsNaN(ConstValue Value) noexcept
		{
			return Value != Value;
		}

		inline static constexpr const Elysium::Core::Template::System::int64_t GetValuePreDecimalPoint(ConstValue Value) noexcept
		{
			return static_cast<Elysium::Core::Template::System::int64_t>(Value);
		}

		inline static constexpr const Elysium::Core::Template::System::uint64_t GetValuePostDecimalPoint(ConstValue Value,
			const Elysium::Core::Template::System::uint8_t NumberOfDigits) noexcept
		{
			const Elysium::Core::Template::System::int64_t TruncatedValue =
				Elysium::Core::Template::Math::Truncate<double, Elysium::Core::Template::System::int64_t>(Value);
			const double FractionalValue = Elysium::Core::Template::Math::Absolute(Value - TruncatedValue);
			const double Factor = Elysium::Core::Template::Math::Power(10.0, NumberOfDigits);

			return static_cast<Elysium::Core::Template::System::uint64_t>(FractionalValue * Factor);
		}
	};
	
	/*
	template <>
	struct NumericTraits<long double>
		: public _NumericTraitsBaseFloatingPoint<long double>
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
