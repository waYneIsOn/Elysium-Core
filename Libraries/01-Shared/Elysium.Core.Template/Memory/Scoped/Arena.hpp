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

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAOPTIONS
#include "ArenaOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAPAGE
#include "ArenaPage.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Memory::Scoped
{
	class Arena
	{
	public:
		Arena(const ArenaOptions& Options) noexcept;

		Arena(const Arena&& Source) = delete;

		Arena(Arena&& Right) = delete;

		~Arena() noexcept;
	public:
		Arena& operator=(const Arena& Source) = delete;

		Arena& operator=(Arena&& Right) noexcept = delete;
	public:
		const Elysium::Core::Template::System::size GetTotalSize() const;
	public:
		template <class T>
		T* Push(Elysium::Core::Template::System::size NumberOfElements = 1) noexcept;

		template <class T>
		void Pop(Elysium::Core::Template::System::size NumberOfElements = 1) noexcept;

		void Clear() noexcept;

		//void Reset();
	private:
		const ArenaOptions _Options;
		ArenaPage* _First;
		ArenaPage* _Last;
	};

	inline Arena::Arena(const ArenaOptions& Options) noexcept
		: _Options(Options), _First(new ArenaPage(Options._CapacityPerPage)), _Last(_First)
	{ }

	inline Arena::~Arena() noexcept
	{
		Clear();
	}

	inline const Elysium::Core::Template::System::size Arena::GetTotalSize() const
	{
		Elysium::Core::Template::System::size TotalSize = 0;

		ArenaPage* CurrentPage = _First;
		while (CurrentPage != nullptr)
		{
			TotalSize += CurrentPage->_CurrentOffset;
			CurrentPage = CurrentPage->_NextPage;
		}

		return TotalSize;
	}

	template<class T>
	inline T* Arena::Push(Elysium::Core::Template::System::size NumberOfElements) noexcept
	{
		static const Elysium::Core::Template::System::size AlignSize = alignof(T);
		static const Elysium::Core::Template::System::size Size = sizeof(T);

		if (NumberOfElements == 0)
		{
			return nullptr;
		}

		if (AlignSize == 0 ||
			(AlignSize & (AlignSize - 1)) == 1)	// is power of two
		{
			return nullptr;
		}

		const Elysium::Core::Template::System::size AllocationSize = NumberOfElements * Size;

		return static_cast<T*>(_Last->Push(AllocationSize, AlignSize));
	}

	template<class T>
	inline void Arena::Pop(Elysium::Core::Template::System::size NumberOfElements) noexcept
	{
		static const Elysium::Core::Template::System::size AlignSize = alignof(T);
		static const Elysium::Core::Template::System::size Size = sizeof(T);

		if (NumberOfElements == 0)
		{
			return;
		}

		if (AlignSize == 0 ||
			(AlignSize & (AlignSize - 1)) == 1)	// is power of two
		{
			return;
		}

		const Elysium::Core::Template::System::size AllocationSize = NumberOfElements * Size;

		_Last->Pop(AllocationSize, AlignSize);
	}

	inline void Arena::Clear() noexcept
	{
		ArenaPage* CurrentPage = _First;
		while (CurrentPage != nullptr)
		{
			CurrentPage->Clear();
			CurrentPage = CurrentPage->_NextPage;
		}
	}
}
#endif
