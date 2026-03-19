module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os regarding filesystem"
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef _NEW_
#include <new>
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_COMPOSITETYPE
#include "RunTimeTypeInformation/CompositeType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_ENUMERATION
#include "RunTimeTypeInformation/Enumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_SOURCELOCATION
#include "RunTimeTypeInformation/SourceLocation.hpp"
#endif

export module Elysium.Core.Template.RunTimeTypeInformation;

export
{
	using Elysium::Core::Template::RunTimeTypeInformation::CompositeType;
	using Elysium::Core::Template::RunTimeTypeInformation::Enumeration;
	using Elysium::Core::Template::RunTimeTypeInformation::SourceLocation;
}