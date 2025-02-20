/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#define ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Memory::Scoped
{
	template <class T>
	class Arena
	{
	public:
		Arena() = default;

		Arena(const Arena&& Source) = delete;

		Arena(Arena&& Right) = delete;

		~Arena() = default;
	public:
		Arena& operator=(const Arena& Source) = delete;

		Arena& operator=(Arena&& Right) noexcept = delete;
	public:

	private:

	};
}
#endif
