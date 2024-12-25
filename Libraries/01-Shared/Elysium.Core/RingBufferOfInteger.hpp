/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONTAINER_RINGBUFFEROFINTEGER
#define ELYSIUM_CORE_CONTAINER_RINGBUFFEROFINTEGER

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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER
#include "../Elysium.Core.Template/RingBuffer.hpp"
#endif

namespace Elysium::Core::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint64_t>;

	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int64_t>;

	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::RingBuffer<Elysium::Core::size>;

	using RingBufferOfUInt8_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint8_t>;
	using RingBufferOfUInt16_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint16_t>;
	using RingBufferOfUInt32_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint32_t>;
	using RingBufferOfUInt64_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::uint64_t>;

	using RingBufferOfInt8_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int8_t>;
	using RingBufferOfInt16_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int16_t>;
	using RingBufferOfInt32_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int32_t>;
	using RingBufferOfInt64_t = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::int64_t>;

	using RingBufferOfSize = Elysium::Core::Template::Container::RingBuffer<Elysium::Core::size>;
}
#endif
