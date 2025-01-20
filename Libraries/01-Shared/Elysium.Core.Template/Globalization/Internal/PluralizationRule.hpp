/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_PLURALIZATIONRULE
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_PLURALIZATIONRULE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "../../Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS
#include "../../Operators.hpp"
#endif

namespace Elysium::Core::Template::Globalization::Internal
{
	template <class Operator, Elysium::Core::Template::System::int8_t ComparisonValue>
	class PluralizationRule
	{
	};
	
	using ZeroSingular = PluralizationRule<Elysium::Core::Template::Operators::Equal<Elysium::Core::Template::System::int8_t>, 0_i8>;
	using ZeroPlural = PluralizationRule<Elysium::Core::Template::Operators::Equal<Elysium::Core::Template::System::int8_t>, 0>;
	
	using Singular = PluralizationRule<Elysium::Core::Template::Operators::Equal<Elysium::Core::Template::System::int8_t>, 1>;
	using GeneralPlural = PluralizationRule<Elysium::Core::Template::Operators::Greater<Elysium::Core::Template::System::int8_t>, 1>;
	
	using Dual = PluralizationRule<Elysium::Core::Template::Operators::Equal<Elysium::Core::Template::System::int8_t>, 2>;
}
#endif
