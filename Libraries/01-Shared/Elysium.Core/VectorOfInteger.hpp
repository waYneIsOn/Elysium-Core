/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFINTEGER
#define ELYSIUM_CORE_CONTAINER_VECTOROFINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFINTEGER
#include "DefaultAllocatorOfInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::uint8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::uint16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::uint32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::uint64_t>;

	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::int8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::int16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::int32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::int64_t>;

	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::size>;

	using VectorOfUInt8_t = Elysium::Core::Template::Container::Vector<Elysium::Core::uint8_t>;
	using VectorOfUInt16_t = Elysium::Core::Template::Container::Vector<Elysium::Core::uint16_t>;
	using VectorOfUInt32_t = Elysium::Core::Template::Container::Vector<Elysium::Core::uint32_t>;
	using VectorOfUInt64_t = Elysium::Core::Template::Container::Vector<Elysium::Core::uint64_t>;

	using VectorOfInt8_t = Elysium::Core::Template::Container::Vector<Elysium::Core::int8_t>;
	using VectorOfInt16_t = Elysium::Core::Template::Container::Vector<Elysium::Core::int16_t>;
	using VectorOfInt32_t = Elysium::Core::Template::Container::Vector<Elysium::Core::int32_t>;
	using VectorOfInt64_t = Elysium::Core::Template::Container::Vector<Elysium::Core::int64_t>;

	using VectorOfSize = Elysium::Core::Template::Container::Vector<Elysium::Core::size>;
}
#endif
