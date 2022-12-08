/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_AGGREGATEEXCEPTION
#define ELYSIUM_CORE_AGGREGATEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_AGGREGATEEXCEPTION
#include "../Elysium.Core.Template/AggregateException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::AggregateException;

	using AggregateException = Elysium::Core::Template::Exceptions::AggregateException;
}
#endif
