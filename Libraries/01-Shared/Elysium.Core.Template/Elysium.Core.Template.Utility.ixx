export module Elysium.Core.Template.Utility;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define WIN32_LEAN_AND_MEAN
	//#include <Windows.h>;
	import <Windows.h>;
	#endif
#else
#error "unsupported os"
#endif

#ifndef _INITIALIZER_LIST_
//#include <initializer_list>
import <initializer_list>;
#endif

#ifndef _NEW_
//#include <new>;
import <new>;
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