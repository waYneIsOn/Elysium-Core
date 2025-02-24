/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAVIRTUALPAGE
#define ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAVIRTUALPAGE

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
	class ArenaVirtualPage
	{
		friend class Arena;
	private:
		//ArenaVirtualPage(Elysium::Core::Template::System::size Capacity) noexcept;
	public:
		ArenaVirtualPage() = delete;

		ArenaVirtualPage(const ArenaVirtualPage&& Source) = delete;

		ArenaVirtualPage(ArenaVirtualPage&& Right) = delete;

		//~ArenaVirtualPage() noexcept;
	public:
		ArenaVirtualPage& operator=(const ArenaVirtualPage& Source) = delete;

		ArenaVirtualPage& operator=(ArenaVirtualPage&& Right) noexcept = delete;
	public:
		//bool IsFull() const noexcept;
	private:
		//void* Push(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept;

		//void Pop(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept;

		//void Clear() noexcept;
	private:
		Elysium::Core::Template::System::byte* _Data;
		Elysium::Core::Template::System::size _Capacity;
		Elysium::Core::Template::System::size _CurrentOffset;
		ArenaPage* _NextPage;
	};
}
#endif