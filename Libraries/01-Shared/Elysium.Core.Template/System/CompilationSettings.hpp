/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS

#ifdef _MSC_VER
#pragma once
#endif

//#define ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATIONS

#if defined ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATIONS
#define ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATION_X509CERTIFICATE
#define ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATION_TLS
#endif

#endif
