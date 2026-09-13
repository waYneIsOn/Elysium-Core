/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../../System/CompilationSettings.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATION_X509CERTIFICATE
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE_CUSTOM
#include "X509Certificate.Custom.hpp"
#endif
#elif defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE_WINDOWS
#include "X509Certificate.Windows.hpp"
#endif
#endif

#endif
