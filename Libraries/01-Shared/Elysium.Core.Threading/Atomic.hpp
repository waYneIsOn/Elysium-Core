/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_ATOMIC
#define ELYSIUM_CORE_THREADING_ATOMIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "../Elysium.Core.Template/Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::Threading
{
	//template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<bool>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::byte>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint64_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int64_t>;
	
	//using AtomicBool = Elysium::Core::Template::Threading::Atomic<bool>;
	using AtomicByte = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::byte>;
	using AtomicUInt8_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint8_t>;
	using AtomicUInt16_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint16_t>;
	using AtomicUInt32_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t>;
	using AtomicUInt64_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint64_t>;
	using AtomicInt8_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int8_t>;
	using AtomicInt16_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int16_t>;
	using AtomicInt32_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int32_t>;
	using AtomicInt64_t = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int64_t>;
}
#endif
