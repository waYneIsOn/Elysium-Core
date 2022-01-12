/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER

#ifdef _MSC_VER
#pragma once
#endif

#if defined _MSC_VER
#define ELYSIUM_CORE_COMPILER u8"Microsoft Visual C++"
#elif defined __clang__
#define ELYSIUM_CORE_COMPILER u8"LLVM C compiler"
#elif defined __INTEL_
#define ELYSIUM_CORE_COMPILER u8"Intel C/C++ compiler"
#elif defined __GNUC__
#define ELYSIUM_CORE_COMPILER u8"GNU C compiler"
#else
#error "unsupported compiler"
#endif

#endif
