/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM

#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(__CYGWIN__)

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

#elif defined(__ANDROID__)

#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__))

#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))

#else
#error "unsupported os"
#endif
#endif
