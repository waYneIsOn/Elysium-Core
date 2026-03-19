/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_FLOAT
#define ELYSIUM_CORE_FLOAT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NUMERIC
#include "Numeric.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF
#include "../Elysium.Core.Template/Common/EnableIf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLOATINGPOINT
#include "../Elysium.Core.Template/TypeTraits/IsFloatingPoint.hpp"
#endif

namespace Elysium::Core
{
	template class ELYSIUM_CORE_API Numeric<float>;
	template class ELYSIUM_CORE_API Numeric<double>;
	//template class ELYSIUM_CORE_API Numeric<Decimal>;

	using Single = Numeric<float>;
	using Double = Numeric<double>;
	//using Decimal = Numeric<Decimal>;
}
#endif
