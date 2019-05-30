/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_EXPORT
#define ELYSIUM_CORE_EXPORT

#if defined(__ANDROID__)
#define EXPORT
#elif defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#error "undefined os"
#endif
#endif
