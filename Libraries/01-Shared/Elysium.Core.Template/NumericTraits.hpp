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
	template <class T>
	struct NumericTraitsBase
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
		static constexpr const bool IsPositive(ConstValue Value);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsPrimeNumber(ConstValue Value);
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr System::uint8_t GetDigitCount(Value Value);
	};

	template <class T>
	struct NumericTraits
	{ };

	template <>
	struct NumericTraits<System::uint8_t> : public NumericTraitsBase<System::uint8_t>
	{ };

	template <>
	struct NumericTraits<System::uint16_t> : public NumericTraitsBase<System::uint16_t>
	{
	public:
		static constexpr const System::uint8_t GetHigh(ConstValue Value);

		static constexpr const System::uint8_t GetLow(ConstValue Value);
	};

	template <>
	struct NumericTraits<System::uint32_t> : public NumericTraitsBase<System::uint32_t>
	{
	public:
		static constexpr const System::uint16_t GetHigh(ConstValue Value);

		static constexpr const System::uint16_t GetLow(ConstValue Value);
	};

	template <>
	struct NumericTraits<System::uint64_t> : public NumericTraitsBase<System::uint64_t>
	{
	public:
		static constexpr const System::uint32_t GetHigh(ConstValue Value);

		static constexpr const System::uint32_t GetLow(ConstValue Value);
	};

	template <>
	struct NumericTraits<System::int8_t> : public NumericTraitsBase<System::int8_t>
	{ };

	template <>
	struct NumericTraits<System::int16_t> : public NumericTraitsBase<System::int16_t>
	{
	/*
	public:
		static constexpr const System::uint8_t GetHigh(ConstValue Value);

		static constexpr const System::uint8_t GetLow(ConstValue Value);
	*/
	};

	template <>
	struct NumericTraits<System::int32_t> : public NumericTraitsBase<System::int32_t>
	{
		/*
		public:
			static constexpr const System::uint16_t GetHigh(ConstValue Value);

			static constexpr const System::uint16_t GetLow(ConstValue Value);
		*/
	};

	template <>
	struct NumericTraits<System::int64_t> : public NumericTraitsBase<System::int64_t>
	{
		/*
		public:
			static constexpr const System::int32_t GetHigh(ConstValue Value);

			static constexpr const System::int32_t GetLow(ConstValue Value);
		*/
	};

	template<class T>
	inline constexpr const bool NumericTraitsBase<T>::IsPositive(ConstValue Value)
	{
		return Value > 0;
	}

	template<class T>
	inline constexpr const bool NumericTraitsBase<T>::IsPrimeNumber(ConstValue Input)
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

	template<class T>
	inline constexpr System::uint8_t NumericTraitsBase<T>::GetDigitCount(Value Value)
	{
		System::uint8_t Result = 0;
		while (Value > 0)
		{
			Value /= 10;
			Result++;
		}

		return Result;
	}

	inline constexpr const System::uint8_t NumericTraits<System::uint16_t>::GetHigh(ConstValue Value)
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value >> 8 & 0xFF;
		//return ((System::uint8_t*)&Value)[1];	// doesn't allow for constexpr
#else
		return Value & 0xFF;
#endif
	}

	inline constexpr const System::uint8_t NumericTraits<System::uint16_t>::GetLow(ConstValue Value)
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value & 0xFF;
		//return ((System::uint8_t*)&Value)[0];	// doesn't allow for constexpr
#else
		return Value >> 8 & 0xFF;
#endif
	}

	inline constexpr const System::uint16_t NumericTraits<System::uint32_t>::GetHigh(ConstValue Value)
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value >> 16 & 0xFFFF;
#else
		return Value & 0xFFFF;
#endif
	}

	inline constexpr const System::uint16_t NumericTraits<System::uint32_t>::GetLow(ConstValue Value)
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value & 0xFFFF;
#else
		return Value >> 16 & 0xFFFF;
#endif
	}

	inline constexpr const System::uint32_t NumericTraits<System::uint64_t>::GetHigh(ConstValue Value)
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value >> 32 & 0xFFFFFFFF;
#else
		return Value & 0xFFFFFFFF;
#endif
	}

	inline constexpr const System::uint32_t NumericTraits<System::uint64_t>::GetLow(ConstValue Value)
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return Value & 0xFFFFFFFF;
#else
		return Value >> 32 & 0xFFFFFFFF;
#endif
	}
}
#endif
