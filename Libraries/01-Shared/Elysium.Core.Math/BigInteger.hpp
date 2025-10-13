/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

Code translated and edited from original implementation:
https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs
Copyright (c) Microsoft Corporation. All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_BIGINTEGER
#define ELYSIUM_CORE_MATH_NUMERICS_BIGINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFINTEGER
#include "../Elysium.Core/VectorOfInteger.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API BigInteger final
	{
	public:
		BigInteger() = delete;

		BigInteger(const Elysium::Core::int32_t Sign, const Elysium::Core::Container::VectorOfUInt32_t& Value);

		BigInteger(const Elysium::Core::Container::VectorOfUInt32_t& Value, const bool IsNegative);

		BigInteger(Elysium::Core::Container::VectorOfUInt32_t& Value);

		BigInteger(const Elysium::Core::int32_t Value);

		BigInteger(const Elysium::Core::uint32_t Value);

		BigInteger(const Elysium::Core::Container::VectorOfUInt32_t& Value);

		BigInteger(const BigInteger& Source);

		BigInteger(BigInteger&& Right) noexcept;

		~BigInteger();
	public:
		BigInteger& operator=(const BigInteger& Source);

		BigInteger& operator=(BigInteger&& Right) noexcept;
	public:
		BigInteger operator<<(const Elysium::Core::int32_t& Shift);

		BigInteger operator>>(const Elysium::Core::int32_t& Shift);
	public:
		BigInteger operator|(const BigInteger& Right);
	public:
		const bool GetIsZero() const;

		const Elysium::Core::int32_t GetSign() const;
	public:
		const Elysium::Core::Utf8String ToString() const;
	private:
		static const bool GetPartsForBitManipulation(const BigInteger& Value, Elysium::Core::Container::VectorOfUInt32_t& Bits,
			Elysium::Core::int32_t& Length);
		
		// @ToDo: move to Elysium::Core::Numerics::NumericsHelper-class
		static const Elysium::Core::Container::VectorOfUInt32_t DangerousMakeTwosComplement(Elysium::Core::Container::VectorOfUInt32_t& d);
		
		static const Elysium::Core::Container::VectorOfUInt32_t Resize(Elysium::Core::Container::VectorOfUInt32_t& Value, 
			const Elysium::Core::int32_t Length);

		const Elysium::Core::Container::VectorOfUInt32_t ToUInt32Array() const;
	private:
		inline static constexpr const Elysium::Core::uint32_t _uMaskHighBit = static_cast<Elysium::Core::uint32_t>(Elysium::Core::UInt32::GetMinValue());
		inline static constexpr const Elysium::Core::int32_t _CBITUINT = 32;
		inline static constexpr const Elysium::Core::int32_t _CBitUint32 = 32;
	private:
		static const Elysium::Core::Math::Numerics::BigInteger& MinInt();

		static const Elysium::Core::Math::Numerics::BigInteger& MinusOneInt();

		static const Elysium::Core::Math::Numerics::BigInteger& ZeroInt();
	private:
		Elysium::Core::int32_t _Sign;
		Elysium::Core::Container::VectorOfUInt32_t _Bits;
	};
}
#endif
