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
		/*
		OutputDebugStringA("MemSet hit\n");

		void* caller = _ReturnAddress();  // x64: use _ReturnAddress()
		char buf[256];
		sprintf_s(buf, "MemSet hit: caller=%p, Dest=%p, Size=%zu\n",
			caller, Destination, Size);
		OutputDebugStringA(buf);

		if (Destination == nullptr || (uintptr_t)Destination > 0x800000000000ULL)
		{
			bool bla = false;
			__debugbreak(); // or force a crash here
		}

		__try
		{
			RtlFillMemory(Destination, Size, static_cast<Elysium::Core::Template::System::byte>(Value));
			return Destination;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) 
		{
			OutputDebugStringA("Access violation in SafeMemSet!\n");
			return nullptr;
		}
		*/
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
