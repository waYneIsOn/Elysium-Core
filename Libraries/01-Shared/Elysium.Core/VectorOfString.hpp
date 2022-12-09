/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFSTRING
#define ELYSIUM_CORE_CONTAINER_VECTOROFSTRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFSTRING
#include "DefaultAllocatorOfString.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::Utf16String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::Utf32String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::WideString>;
	
	using VectorOfString = Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;
	using VectorOfUtf8String = Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;
	using VectorOfUtf16String = Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;
	using VectorOfUtf32String = Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;
	using VectorOfWideString = Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;
}
#endif
