/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif
//WINBASEAPI VOID WINAPI RtlFillMemory(_Out_ VOID UNALIGNED* Destination,	_In_  SIZE_T Length, _In_  BYTE Fill);
#else
/*
#ifndef _CSTRING_
#include <cstring>
#endif
*/
// c runtime memset
extern "C" void* __cdecl memset(void* dest, int c, size_t count);
#endif

namespace Elysium::Core::Template::Memory
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	inline void* MemSet(void* Destination, Elysium::Core::Template::System::int32_t Value, Elysium::Core::Template::System::size Size)
	{
		OutputDebugStringA("MemSet hit\n");

		void* caller = _ReturnAddress();  // x64: use _ReturnAddress()
		char buffer[128];
		sprintf_s(buffer, "MemSet called from address: %p\n", caller);
		OutputDebugStringA(buffer);

		if (IsBadWritePtr(Destination, Size))
		{
			__debugbreak(); // or force a crash here
		}

		RtlFillMemory(Destination, Size, static_cast<Elysium::Core::Template::System::byte>(Value));
		return Destination;
	}
#else
	inline void* MemSet(void* Destination, Elysium::Core::Template::System::int32_t Value, Elysium::Core::Template::System::size Size)
	{
		return memset(Destination, Value, Size);
	}
#endif
}
#endif
