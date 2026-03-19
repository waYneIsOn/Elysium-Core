module;

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO
#include "Numeric/Ratio.hpp"
#endif

export module Elysium.Core.Template.Numeric;

export
{
	using Elysium::Core::Template::Numeric::NumericTraits;
	using Elysium::Core::Template::Numeric::Ratio;
}