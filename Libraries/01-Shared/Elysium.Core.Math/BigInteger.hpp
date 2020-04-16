/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API BigInteger
	{
	public:
		BigInteger(const uint32_t Value);
		//BigInteger(const int32_t Value);
		//BigInteger(const Collections::Template::Array<byte> Value);
		BigInteger(const BigInteger& Source) = delete;
		BigInteger(BigInteger&& Right) = delete;
		~BigInteger();

		BigInteger& operator=(const BigInteger& Source) = delete;
		BigInteger& operator=(BigInteger&& Right) noexcept = delete;
	private:
		int32_t _Sign;
		Collections::Template::Array<uint32_t> _Bits;
	};
}
#endif
