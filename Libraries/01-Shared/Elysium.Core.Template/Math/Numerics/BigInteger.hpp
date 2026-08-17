/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_NUMERICS_BIGINTEGER
#define ELYSIUM_CORE_TEMPLATE_MATH_NUMERICS_BIGINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "../../Concepts/SignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../../Functional/RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../../Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_ARCHTECTURE
#include "../../System/Architecture.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

namespace Elysium::Core::Template::Math::Numerics
{
	template <Elysium::Core::Template::Concepts::SignedInteger Sign = Elysium::Core::Template::System::int32_t,
		Elysium::Core::Template::Concepts::UnsignedInteger Limb = Elysium::Core::Template::Numeric::NumericTraits<Sign>::UnsignedType>
	class BigInteger
	{
	public:
		using SignType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Sign>;

		using LimbType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Limb>;
	private:
		inline static constexpr const Elysium::Core::Template::System::uint8_t _SignTypeBitWidth = sizeof(SignType) * Elysium::Core::Template::System::Architecture::BitsPerByte;

		inline static constexpr const SignType _uMaskHighBit = Elysium::Core::Template::Numeric::NumericTraits<LimbType>::Minimum;
	public:
		constexpr BigInteger() = delete;

		inline constexpr BigInteger(const SignType Value)
			: _SignOrValue(Value), _Limbs{}
		{ }
		/*
		inline constexpr BigInteger(const LimbType Value)
			: _SignOrValue(Value <= Elysium::Core::Template::Numeric::NumericTraits<SignType>::Maximum ? Value : 0), _Limbs{}
		{ }
		*/
		inline constexpr BigInteger(const SignType SignOrValue, const Elysium::Core::Template::Container::Vector<LimbType>& Limbs)
			: _SignOrValue(SignOrValue), _Limbs(Limbs)
		{ }
		
		//inline constexpr BigInteger(const Elysium::Core::Template::Container::Vector<LimbType>& Value, const bool IsNegative);

		//inline constexpr BigInteger(const Elysium::Core::Template::Container::Vector<LimbType>& Value);
		
		inline constexpr BigInteger(const BigInteger& Source)
			: _SignOrValue(Source._SignOrValue), _Limbs(Source._Limbs)
		{ }

		inline constexpr BigInteger(BigInteger&& Right) noexcept
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~BigInteger() = default;
	public:
		inline constexpr BigInteger& operator=(const BigInteger& Source)
		{
			if (this != &Source)
			{
				_SignOrValue = Source._SignOrValue;
				_Limbs = Source._Limbs;
			}
			return *this;
		}

		inline constexpr BigInteger& operator=(BigInteger&& Right) noexcept
		{
			if (this != &Right)
			{
				_SignOrValue = Elysium::Core::Template::Functional::Move(Right._SignOrValue);
				_Limbs = Elysium::Core::Template::Functional::Move(Right._Limbs);
			}
			return *this;
		}
	public:
		inline constexpr BigInteger operator<<(const Elysium::Core::Template::System::int32_t Shift)
		{
			if (0 == Shift)
			{
				return *this;
			}

			throw;
		}

		inline constexpr BigInteger operator>>(const Elysium::Core::Template::System::int32_t Shift)
		{
			throw;
		}
	public:
		inline constexpr BigInteger operator|(const BigInteger& Right)
		{
			throw;
		}
	public:
		inline constexpr const SignType GetSign() const noexcept
		{
			/*
			if (_SignOrValue < 0)
			{
				return -1;
			}
			else if (_SignOrValue > 0)
			{
				return 1;
			}

			return 0;
			*/
			//return (_SignOrValue >> (_SignTypeBitWidth - 1)) - (-_SignOrValue >> (_SignTypeBitWidth - 1));
			return (_SignOrValue > 0) - (_SignOrValue < 0);
		}

		inline constexpr const bool GetIsZero() const noexcept
		{
			return 0 == _SignOrValue;
		}

		inline constexpr const bool GetIsPositive() const noexcept
		{
			return 0 < _SignOrValue;
		}

		inline constexpr const bool GetIsNegative() const noexcept
		{
			return 0 > _SignOrValue;
		}
	public:
		inline static constexpr const BigInteger& MinInt()
		{
			throw;
			/*
			static const BigInteger Value = BigInteger(-1, Elysium::Core::Template::Container::Vector<LimbType>({ _uMaskHighBit }));
			return Value;
			*/
		}

		inline static constexpr const BigInteger& MinusOne()
		{
			static const BigInteger Value = BigInteger(-1);
			return Value;
		}

		inline static constexpr const BigInteger& Zero()
		{
			static const BigInteger Value = BigInteger(0);
			return Value;
		}
	private:
		/// <summary>
		/// Represents the sign of given value.
		/// Also is used as an optimization to store all data if it fits in "SignType".
		/// </summary>
		SignType _SignOrValue;

		/// <summary>
		/// If given value is too large to fit into "SignType", more data is stored here.
		/// </summary>
		Elysium::Core::Template::Container::Vector<LimbType> _Limbs;
	};
}
#endif