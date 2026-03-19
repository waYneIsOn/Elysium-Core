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
#error "unsupported os"
#endif

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

export module Elysium.Core.Template.Exceptions;

export
{
	using Elysium::Core::Template::Exceptions::AggregateException;
	using Elysium::Core::Template::Exceptions::ArgumentException;
	using Elysium::Core::Template::Exceptions::ArgumentNullException;
	using Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException;
	using Elysium::Core::Template::Exceptions::ArithmeticException;
	using Elysium::Core::Template::Exceptions::DivideByZeroException;
	using Elysium::Core::Template::Exceptions::Exception;
	using Elysium::Core::Template::Exceptions::IndexOutOfRangeException;
	using Elysium::Core::Template::Exceptions::InvalidCastException;
	using Elysium::Core::Template::Exceptions::InvalidOperationException;
	using Elysium::Core::Template::Exceptions::NotImplementedException;
	using Elysium::Core::Template::Exceptions::NotSupportedException;
	using Elysium::Core::Template::Exceptions::OutOfMemoryException;
	using Elysium::Core::Template::Exceptions::OverflowException;
	using Elysium::Core::Template::Exceptions::SystemException;
}
