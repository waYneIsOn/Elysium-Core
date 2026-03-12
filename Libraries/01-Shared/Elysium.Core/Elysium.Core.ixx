module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
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

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef _LIMITS_
#include <limits>
#endif

#ifndef _CMATH_
// @ToDo: implement myself and remove
#include <cmath>
#endif

#ifndef _NEW_
#include <new>
#endif

#ifndef _TYPEINFO_
#include <typeinfo>
#endif

export module Elysium.Core;

export
{
	/*
#ifndef ELYSIUM_CORE_AGGREGATEEXCEPTION
#include "AggregateException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARITHMETICEXCEPTION
#include "ArithmeticException.hpp"
#endif

#ifndef ELYSIUM_CORE_BITCONVERTER
#include "BitConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_BOOLEAN
#include "Boolean.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_CONSOLE
#include "Console.hpp"
#endif

#ifndef ELYSIUM_CORE_DATEPART
#include "DatePart.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEKIND
#include "DateTimeKind.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEOFFSET
#include "DateTimeOffset.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_DECIMAL
#include "Decimal.hpp"
#endif

#ifndef ELYSIUM_CORE_DIVIDEBYZEROEXCEPTION
#include "DivideByZeroException.hpp"
#endif

#ifndef ELYSIUM_CORE_ENUM
#include "Enum.hpp"
#endif

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_EVENT
#include "Event.hpp"
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_FLOAT
#include "Float.hpp"
#endif

#ifndef ELYSIUM_CORE_GUID
#include "Guid.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_IFORMATPROVIDER
#include "IFormatProvider.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERFACE
#include "Interface.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDCASTEXCEPTION
#include "InvalidCastException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NUMERIC
#include "Numeric.hpp"
#endif

#ifndef ELYSIUM_CORE_OBJECT
#include "Object.hpp"
#endif

#ifndef ELYSIUM_CORE_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "OutOfMemoryException.hpp"
#endif

#ifndef ELYSIUM_CORE_OVERFLOWEXCEPTION
#include "OverflowException.hpp"
#endif

#ifndef ELYSIUM_CORE_PLATFORMID
#include "PlatformID.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif







#ifndef ELYSIUM_CORE_SPAN
#include "Span.hpp"
#endif





#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif





#ifndef ELYSIUM_CELYSIUM_CORE_SYSTEMORE_AGGREGATEEXCEPTION
#include "System.hpp"
#endif





#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMSPECIFIC
#include "SystemSpecific.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_VERSION
#include "Version.hpp"
#endif
*/
}