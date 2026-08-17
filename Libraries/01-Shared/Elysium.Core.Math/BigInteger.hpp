/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_NUMERICS_BIGINTEGER
#include "../Elysium.Core.Template/Math/Numerics/BigInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFINTEGER
#include "../Elysium.Core/VectorOfInteger.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template class ELYSIUM_CORE_MATH_API Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int8_t>;
	template class ELYSIUM_CORE_MATH_API Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int16_t>;
	template class ELYSIUM_CORE_MATH_API Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int32_t>;
	template class ELYSIUM_CORE_MATH_API Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int64_t>;

	using BigInteger8 = Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int8_t>;
	using BigInteger16 = Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int16_t>;
	using BigInteger32 = Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int32_t>;
	using BigInteger64 = Elysium::Core::Template::Math::Numerics::BigInteger<Elysium::Core::Template::System::int64_t>;
}
#endif
