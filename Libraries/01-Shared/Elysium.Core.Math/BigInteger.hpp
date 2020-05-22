/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API BigInteger
	{
	public:
		BigInteger(const int32_t Sign, const Collections::Template::Array<uint32_t>& Value);
		BigInteger(const Collections::Template::Array<uint32_t>& Value, const bool IsNegative);
		BigInteger(const int32_t Value);
		BigInteger(const uint32_t Value);
		BigInteger(const Collections::Template::Array<byte>& Value);
		BigInteger(const BigInteger& Source);
		BigInteger(BigInteger&& Right) noexcept;
		~BigInteger();

		BigInteger& operator=(const BigInteger& Source);
		BigInteger& operator=(BigInteger&& Right) noexcept;

		BigInteger operator<<(const int32_t& Shift);
		BigInteger operator>>(const int32_t& Shift);

		BigInteger operator|(const int32_t& Right);
	private:
		int32_t _Sign;
		Collections::Template::Array<uint32_t> _Bits;

		static const uint32_t _uMaskHighBit;
		static const int32_t _CBITUINT;

		static const BigInteger _bnMinInt;
		static const BigInteger _MinusOneInt;
		static const BigInteger _ZeroInt;

		static const bool GetPartsForBitManipulation(const BigInteger& Value, Collections::Template::Array<uint32_t>& Bits, int32_t& Length);

		// ToDo: move to Elysium::Core::Numerics::NumericsHelper-class
		static const Collections::Template::Array<uint32_t> DangerousMakeTwosComplement(Collections::Template::Array<uint32_t>& d);
		static const Collections::Template::Array<uint32_t> Resize(Collections::Template::Array<uint32_t>& Value, const Elysium::Core::int32_t Length);
	};
}
#endif
