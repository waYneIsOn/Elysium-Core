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
		constexpr ArenaOptions() noexcept = delete;

		constexpr ArenaOptions(Elysium::Core::Template::System::size CapacityPerPage,
			Elysium::Core::Template::System::size NumberOfPreallocatedPages, bool UseVirtualPaging = false, bool ClearMemory = false) noexcept;

		constexpr ArenaOptions(const ArenaOptions& Source) noexcept;

		constexpr ArenaOptions(ArenaOptions&& Right) = delete;

		constexpr ~ArenaOptions() noexcept = default;
	public:
		constexpr ArenaOptions& operator=(const ArenaOptions& Source) noexcept = delete;

		constexpr ArenaOptions& operator=(ArenaOptions&& Right) noexcept = delete;
	public:
		inline static const Elysium::Core::Template::System::size DefaultCapacityPerPage = 1024;

		inline static const Elysium::Core::Template::System::size DefaultNumberOfPreallocatedPages = 1;
	private:
		Elysium::Core::Template::System::size _CapacityPerPage;
		Elysium::Core::Template::System::size _NumberOfPreallocatedPages;
		bool _UseVirtualPaging;
		bool _ClearMemory;
	};

	inline constexpr ArenaOptions::ArenaOptions(Elysium::Core::Template::System::size CapacityPerPage,
		Elysium::Core::Template::System::size NumberOfPreallocatedPages, bool UseVirtualPaging, bool ClearMemory) noexcept
		: _CapacityPerPage(CapacityPerPage == 0 ? DefaultCapacityPerPage : CapacityPerPage), 
		_NumberOfPreallocatedPages(NumberOfPreallocatedPages == 0 ? DefaultNumberOfPreallocatedPages : NumberOfPreallocatedPages), 
		_UseVirtualPaging(UseVirtualPaging), _ClearMemory(ClearMemory)
	{ }

	inline constexpr ArenaOptions::ArenaOptions(const ArenaOptions& Source) noexcept
		: _CapacityPerPage(Source._CapacityPerPage), _NumberOfPreallocatedPages(Source._NumberOfPreallocatedPages),
		_UseVirtualPaging(Source._UseVirtualPaging), _ClearMemory(Source._ClearMemory)
	{ }
}
#endif
