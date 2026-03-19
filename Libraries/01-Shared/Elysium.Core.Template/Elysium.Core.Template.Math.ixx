module;

#ifndef _CMATH_
#include <cmath>
#endif

// @ToDo: all classes, methods etc. here can be heavily improved!
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "Math/Absolute.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_CEILING
#include "Math/Ceiling.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_DECIMAL
#include "Math/Decimal.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_FACTORIAL
#include "Math/Factorial.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_FLOOR
#include "Math/Floor.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_GREATESTCOMMONDIVISOR
#include "Math/GreatestCommonDivisor.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_LOGARITHM
#include "Math/Logarithm.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIDPOINTROUNDING
#include "Math/MidpointRounding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_POWER
#include "Math/Power.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ROUND
#include "Math/Round.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_SIGNOF
#include "Math/SignOf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_TRUNCATE
#include "Math/Truncate.hpp"
#endif

export module Elysium.Core.Template.Math;

export
{
	using Elysium::Core::Template::Math::Absolute;
	using Elysium::Core::Template::Math::Ceiling;
	using Elysium::Core::Template::Math::Decimal;
	using Elysium::Core::Template::Math::Factorial;
	using Elysium::Core::Template::Math::Floor;
	using Elysium::Core::Template::Math::GreatestCommonDivisor;
	using Elysium::Core::Template::Math::Logarithm;
	using Elysium::Core::Template::Math::MidpointRounding;
	using Elysium::Core::Template::Math::Power;
	using Elysium::Core::Template::Math::Round;
	using Elysium::Core::Template::Math::SignOf;
	using Elysium::Core::Template::Math::Truncate;
}