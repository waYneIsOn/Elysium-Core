/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILERSETTINGS
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILERSETTINGS

#ifdef _MSC_VER
#pragma once
#endif

//#define ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATIONS
#if defined ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATIONS
#define ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATION_X509CERTIFICATE
#define ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATION_TLS
#endif

#endif
