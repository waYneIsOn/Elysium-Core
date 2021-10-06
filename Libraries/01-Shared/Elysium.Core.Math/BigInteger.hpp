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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API BigInteger final
	{
	public:
		BigInteger(const Elysium::Core::int32_t Sign, const Collections::Template::Array<Elysium::Core::uint32_t>& Value);
		BigInteger(const Collections::Template::Array<Elysium::Core::uint32_t>& Value, const bool IsNegative);
		BigInteger(Collections::Template::Array<Elysium::Core::uint32_t>& Value);
		BigInteger(const Elysium::Core::int32_t Value);
		BigInteger(const Elysium::Core::uint32_t Value);
		BigInteger(const Collections::Template::Array<Elysium::Core::byte>& Value);
		BigInteger(const BigInteger& Source);
		BigInteger(BigInteger&& Right) noexcept;
		~BigInteger();

		BigInteger& operator=(const BigInteger& Source);
		BigInteger& operator=(BigInteger&& Right) noexcept;

		BigInteger operator<<(const Elysium::Core::int32_t& Shift);
		BigInteger operator>>(const Elysium::Core::int32_t& Shift);

		BigInteger operator|(const BigInteger& Right);

		const bool GetIsZero() const;

		const Elysium::Core::int32_t GetSign() const;
	private:
		Elysium::Core::int32_t _Sign;
		Collections::Template::Array<Elysium::Core::uint32_t> _Bits;

		inline static constexpr const Elysium::Core::uint32_t _uMaskHighBit = static_cast<Elysium::Core::uint32_t>(Elysium::Core::UInt32::GetMinValue());
		inline static constexpr const Elysium::Core::int32_t _CBITUINT = 32;
		inline static constexpr const Elysium::Core::int32_t _CBitUint32 = 32;

		static const BigInteger _bnMinInt;
		static const BigInteger _MinusOneInt;
		static const BigInteger _ZeroInt;

		static const bool GetPartsForBitManipulation(const BigInteger& Value, Collections::Template::Array<Elysium::Core::uint32_t>& Bits, Elysium::Core::int32_t& Length);

		const Collections::Template::Array<Elysium::Core::uint32_t> ToUInt32Array() const;

		// ToDo: move to Elysium::Core::Numerics::NumericsHelper-class
		static const Collections::Template::Array<Elysium::Core::uint32_t> DangerousMakeTwosComplement(Collections::Template::Array<Elysium::Core::uint32_t>& d);
		static const Collections::Template::Array<Elysium::Core::uint32_t> Resize(Collections::Template::Array<Elysium::Core::uint32_t>& Value, const Elysium::Core::int32_t Length);
	};
}
#endif
