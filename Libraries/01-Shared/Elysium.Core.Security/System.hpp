/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS

#ifndef __WINCRYPT_H__
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <windows.h>
#endif

#include <wincrypt.h>
#pragma comment(lib, "Crypt32.Lib")
#endif
/*
#ifndef __BCRYPT_H__
#ifndef _WINDOWS_
#include <windows.h>
#endif

#include <bcrypt.h>
#pragma comment(lib, "Bcrypt.Lib")
#endif
*/
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATESTOREPOINTER HCERTSTORE

#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER PCCERT_CONTEXT
//#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXT CERT_CONTEXT

#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECHAINENGINEHANDLE HCERTCHAINENGINE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECHAINENGINECONFIG CERT_CHAIN_ENGINE_CONFIG

#define ELYSIUM_CORE_SECURITY_CRYPTOHRAPHY_OIDPOINTER PCCRYPT_OID_INFO

#else
#error "unsupported os"
#endif
#endif
