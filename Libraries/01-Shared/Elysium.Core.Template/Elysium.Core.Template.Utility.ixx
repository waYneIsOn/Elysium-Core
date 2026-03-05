export module Elysium.Core.Template.Utility;

import <InitializerList.hpp>;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
import <Windows.h>;
#else
#error "unsupported os regarding filesystem"
#endif

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INDEXSEQUENCE
#include "Utility/IndexSequence.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE
#include "Utility/IntegerSequence.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_MAKEINTEGERSEQUENCE
#include "Utility/__MakeIntegerSequence.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_REPEAT
#include "Utility/__Repeat.hpp"
#endif
}