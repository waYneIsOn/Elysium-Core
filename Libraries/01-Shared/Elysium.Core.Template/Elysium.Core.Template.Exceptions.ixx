export module Elysium.Core.Template.Exceptions;

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

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_AGGREGATEEXCEPTION
#include "Exceptions/AggregateException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTEXCEPTION
#include "Exceptions/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTNULLEXCEPTION
#include "Exceptions/ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTOUTOFRANGEEXCEPTION
#include "Exceptions/ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARITHMETICEXCEPTION
#include "Exceptions/ArithmeticException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_DIVIDEBYZEROEXCEPTION
#include "Exceptions/DivideByZeroException.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exceptions/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION
#include "Exceptions/IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDCASTEXCEPTION
#include "Exceptions/InvalidCastException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION
#include "Exceptions/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTIMPLEMENTEDEXCEPTION
#include "Exceptions/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTSUPPORTEDEXCEPTION
#include "Exceptions/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OUTOFMEMORYEXCEPTION
#include "Exceptions/OutOfMemoryException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OVERFLOWEXCEPTION
#include "Exceptions/OverflowException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "Exceptions/SystemException.hpp"
#endif
}
