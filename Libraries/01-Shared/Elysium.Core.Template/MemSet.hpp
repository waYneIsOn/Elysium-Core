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

#ifndef _CSTRING_
#include <xstring> // @ToDo: stl remnant
#endif

namespace Elysium::Core::Template::Memory
{
	/*
	template <class T>
	void* MemSet(void* Destination, Elysium::Core::Template::System::int32_t Value, Elysium::Core::Template::System::size Size);

	template<class T>
	void* MemSet(void* Destination, Elysium::Core::Template::System::int32_t Value, Elysium::Core::Template::System::size Size)
	{	// @ToDo: this method probably should be more optimized!
		Elysium::Core::Template::System::byte* CastDestination = reinterpret_cast<Elysium::Core::Template::System::byte*>(Destination);
		for (Elysium::Core::Template::System::size i = 0; i != Size; ++i)
		{
			CastDestination[i] = Value;
		}

		return Destination;
	}
	*/
	
	inline void* MemSet(void* Destination, Elysium::Core::Template::System::int32_t Value, Elysium::Core::Template::System::size Size)
	{	// @ToDo: stl remnant
		return std::memset(Destination, Value, Size);
		/*
		// @ToDo: this method probably should be more optimized!
		Elysium::Core::Template::System::byte* CastDestination = reinterpret_cast<Elysium::Core::Template::System::byte*>(Destination);
		for (Elysium::Core::Template::System::size i = 0; i != Size; ++i)
		{
			CastDestination[i] = Value;
		}

		return Destination;
		*/
	}
}
#endif
