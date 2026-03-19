module;

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_EQUAL
#include "Operators/Equal.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_GREATER
#include "Operators/Greater.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_GREATEROREQUAL
#include "Operators/GreaterOrEqual.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESS
#include "Operators/Less.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESSOREQUAL
#include "Operators/LessOrEqual.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_NOTEQUAL
#include "Operators/NotEqual.hpp"
#endif

export module Elysium.Core.Template.Operators;

export
{
	using Elysium::Core::Template::Operators::Equal;
	using Elysium::Core::Template::Operators::Greater;
	using Elysium::Core::Template::Operators::GreaterOrEqual;
	using Elysium::Core::Template::Operators::Less;
	using Elysium::Core::Template::Operators::LessOrEqual;
	using Elysium::Core::Template::Operators::NotEqual;
}
