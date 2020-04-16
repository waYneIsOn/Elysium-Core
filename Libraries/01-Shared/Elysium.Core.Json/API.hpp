/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_API

#ifdef _MSC_VER
#pragma once
#endif

#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#ifdef ELYSIUMCOREJSON_EXPORTS
#define ELYSIUM_CORE_JSON_API __declspec(dllexport)
#else
#define ELYSIUM_CORE_JSON_API __declspec(dllimport)
#endif
#elif defined(__ANDROID__)
#define EXPORT
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__))

#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))

#else
#error "unsupported os"
#endif

#endif
