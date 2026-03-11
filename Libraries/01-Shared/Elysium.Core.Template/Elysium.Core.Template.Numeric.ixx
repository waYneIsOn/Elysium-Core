module;

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

export module Elysium.Core.Template.Numeric;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO
#include "Numeric/Ratio.hpp"
#endif
}