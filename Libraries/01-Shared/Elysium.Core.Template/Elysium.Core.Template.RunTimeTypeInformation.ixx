export module Elysium.Core.Template.RunTimeTypeInformation;

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
#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_COMPOSITETYPE
#include "RunTimeTypeInformation/CompositeType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_ENUMERATION
#include "RunTimeTypeInformation/Enumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_SOURCELOCATION
#include "RunTimeTypeInformation/SourceLocation.hpp"
#endif
}