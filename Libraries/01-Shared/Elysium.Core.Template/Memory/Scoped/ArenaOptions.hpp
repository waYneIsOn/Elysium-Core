/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAOPTIONS
#define ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAOPTIONS

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Memory::Scoped
{
	class ArenaOptions
	{
		friend class Arena;
	public:
		constexpr ArenaOptions() noexcept = default;

		constexpr ArenaOptions(Elysium::Core::Template::System::size InitialPageSize,
			Elysium::Core::Template::System::size NumberOfPreallocatedPages, bool UseVirtualPaging = false, bool ClearMemory = false) noexcept;

		constexpr ArenaOptions(const ArenaOptions& Source) noexcept = default;

		constexpr ArenaOptions(ArenaOptions&& Right) = default;

		constexpr ~ArenaOptions() noexcept = default;
	public:
		constexpr ArenaOptions& operator=(const ArenaOptions& Source) noexcept = default;

		constexpr ArenaOptions& operator=(ArenaOptions&& Right) noexcept = default;
	public:
		inline static constexpr const Elysium::Core::Template::System::size DefaultCapacityPerPage = 1024;

		inline static constexpr const Elysium::Core::Template::System::size DefaultNumberOfPreallocatedPages = 1;
	private:
		Elysium::Core::Template::System::size _InitialPageSize{};
		Elysium::Core::Template::System::size _NumberOfPreallocatedPages{};
		bool _UseVirtualPaging{};
		bool _ClearMemory{};
	};

	inline constexpr ArenaOptions::ArenaOptions(Elysium::Core::Template::System::size InitialPageSize,
		Elysium::Core::Template::System::size NumberOfPreallocatedPages, bool UseVirtualPaging, bool ClearMemory) noexcept
		: _InitialPageSize(InitialPageSize == 0 ? DefaultCapacityPerPage : InitialPageSize),
		_NumberOfPreallocatedPages(NumberOfPreallocatedPages == 0 ? DefaultNumberOfPreallocatedPages : NumberOfPreallocatedPages), 
		_UseVirtualPaging(UseVirtualPaging), _ClearMemory(ClearMemory)
	{ }
}
#endif
