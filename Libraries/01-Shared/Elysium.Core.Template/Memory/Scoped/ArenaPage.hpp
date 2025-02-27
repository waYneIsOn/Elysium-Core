/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAPAGE
#define ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAPAGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "../../MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Memory::Scoped
{
	class ArenaPage
	{
		friend class Arena;
	private:
		ArenaPage() noexcept = default;
	public:
		ArenaPage(const ArenaPage&& Source) = delete;

		ArenaPage(ArenaPage&& Right) = delete;

		~ArenaPage() noexcept = default;
	public:
		ArenaPage& operator=(const ArenaPage& Source) = delete;

		ArenaPage& operator=(ArenaPage&& Right) noexcept = delete;
	public:
		//bool IsFull() const noexcept;
	private:
		Elysium::Core::Template::System::byte* _Data;
		Elysium::Core::Template::System::size _Capacity;
		Elysium::Core::Template::System::size _CurrentOffset;
		ArenaPage* _NextPage;
	};
}
#endif
