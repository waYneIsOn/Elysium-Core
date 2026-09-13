/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../../System/CompilationSettings.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_OID
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID_FALLBACK
#include "Oid.Fallback.hpp"
#endif
#elif defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID_WINDOWS
#include "Oid.Windows.hpp"
#endif
#endif

#endif
