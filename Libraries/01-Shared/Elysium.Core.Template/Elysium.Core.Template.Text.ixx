module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//import <Windows.h>;
#endif
#else
#error "unsupported os"
#endif

#ifndef _CMATH_
// @ToDo: implement myself and remove
#include <cmath>
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef _NEW_
#include <new>
#endif

export module Elysium.Core.Template.Text;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "Text/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "Text/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_ENCODING
#include "Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_FORMAT
#include "Text/Format.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGBUILDER
#include "Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "Text/StringView.hpp"
#endif
}
