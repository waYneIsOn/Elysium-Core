/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_API

#ifdef _MSC_VER
#pragma once
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifdef ELYSIUMCORESERVICEPROCESS_EXPORTS
#define ELYSIUM_CORE_SERVICEPROCESS_API __declspec(dllexport)
#else
#define ELYSIUM_CORE_SERVICEPROCESS_API __declspec(dllimport)
#endif
#elif defined(__ANDROID__)
#define EXPORT
#else
#error "undefined os"
#endif

#endif
