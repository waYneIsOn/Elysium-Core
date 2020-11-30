/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API

#ifdef _MSC_VER
#pragma once
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifdef ELYSIUMCOREDATASQLNATIVECLIENT_EXPORTS
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API __declspec(dllexport)
#else
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API __declspec(dllimport)
#endif
#elif defined(__ANDROID__)
#define EXPORT
#else
#error "undefined os"
#endif

#endif
