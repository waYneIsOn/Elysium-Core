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

export module Elysium.Core.Template.Text.Unicode;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODECATEGORY
#include "Text/Unicode/UnicodeCategory.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGE
#include "Text/Unicode/UnicodeRange.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGES
#include "Text/Unicode/UnicodeRanges.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF8
#include "Text/Unicode/Utf8.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "Text/Unicode/Utf16.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF32
#include "Text/Unicode/Utf32.hpp"
#endif
}
