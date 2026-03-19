module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFBYTE
#include "DefaultAllocatorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFCHARACTER
#include "DefaultAllocatorOfCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFINTEGER
#include "DefaultAllocatorOfInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFSTRING
#include "DefaultAllocatorOfString.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_OBSERVERPOINTEROFTPIO
#include "Memory/ObserverPointerOfTPIO.hpp"
#endif

export module Elysium.Core.Memory;

export
{
	// DefaultAllocatorOfByte.hpp
	using Elysium::Core::Memory::DefaultAllocatorOfByte;

	// DefaultAllocatorOfCharacter.hpp
	using Elysium::Core::Memory::DefaultAllocatorOfChar;
	using Elysium::Core::Memory::DefaultAllocatorOfUtf8Char;
	using Elysium::Core::Memory::DefaultAllocatorOfUtf16Char;
	using Elysium::Core::Memory::DefaultAllocatorOfUtf32Char;
	using Elysium::Core::Memory::DefaultAllocatorOfWideChar;

	// DefaultAllocatorOfInteger.hpp
	using Elysium::Core::Memory::DefaultAllocatorOfuint8_t;
	using Elysium::Core::Memory::DefaultAllocatorOfuint16_t;
	using Elysium::Core::Memory::DefaultAllocatorOfuint32_t;
	using Elysium::Core::Memory::DefaultAllocatorOfuint64_t;

	using Elysium::Core::Memory::DefaultAllocatorOfint8_t;
	using Elysium::Core::Memory::DefaultAllocatorOfint16_t;
	using Elysium::Core::Memory::DefaultAllocatorOfint32_t;
	using Elysium::Core::Memory::DefaultAllocatorOfint64_t;

	using Elysium::Core::Memory::DefaultAllocatorOfsize;

	// DefaultAllocatorOfString.hpp
	using Elysium::Core::Memory::DefaultAllocatorOfString;
	using Elysium::Core::Memory::DefaultAllocatorOfUtf8String;
	using Elysium::Core::Memory::DefaultAllocatorOfUtf16String;
	using Elysium::Core::Memory::DefaultAllocatorOfUtf32String;
	using Elysium::Core::Memory::DefaultAllocatorOfWideString;

	// ObserverPointerOfTPIO.hpp
	using Elysium::Core::Memory::ObserverPointerOfTPIO;
}
