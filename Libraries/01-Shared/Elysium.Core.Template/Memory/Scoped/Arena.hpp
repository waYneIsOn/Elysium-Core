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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIAL
#include "../../Concepts/Trivial.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "../../MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAOPTIONS
#include "ArenaOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAPAGE
#include "ArenaPage.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _PROCESSTHREADSAPI_H_
	#include <processthreadsapi.h>
	#endif
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
		void* Push(const Elysium::Core::Template::System::size Size, 
			const Elysium::Core::Template::System::size AlignSize = alignof(Elysium::Core::Template::System::size)) noexcept;

		template <Elysium::Core::Template::Concepts::Trivial T>
		T* Push(const Elysium::Core::Template::System::size NumberOfElements = 1) noexcept;

		void Pop(const Elysium::Core::Template::System::size Size, 
			const Elysium::Core::Template::System::size AlignSize = alignof(Elysium::Core::Template::System::size)) noexcept;
		
		template <Elysium::Core::Template::Concepts::Trivial T>
		void Pop(const Elysium::Core::Template::System::size NumberOfElements = 1) noexcept;
		
		void Clear() noexcept;

		//void Reset();
	private:
		ArenaPage* CreatePage(const Elysium::Core::Template::System::size PageSize, ArenaPage* PreviousPage = nullptr) noexcept;
	private:
		const ArenaOptions _Options;
		ArenaPage* _CurrentPage;
	};

	inline Arena::Arena(const ArenaOptions& Options) noexcept
		: _Options(Options), _CurrentPage(CreatePage(_Options._InitialPageSize))
	{ }

	inline Arena::~Arena() noexcept
	{
		Clear();

		ArenaPage* CurrentPage = _CurrentPage;
		ArenaPage* ToBeDeleted = nullptr;
		while (CurrentPage != nullptr)
		{
			ToBeDeleted = CurrentPage;

			CurrentPage = CurrentPage->_NextPage;

			delete ToBeDeleted;
		}
	}

	inline const Elysium::Core::Template::System::size Arena::GetTotalSize() const
	{
		Elysium::Core::Template::System::size TotalSize = 0;

		ArenaPage* CurrentPage = _CurrentPage;
		while (CurrentPage != nullptr)
		{
			TotalSize += CurrentPage->_CurrentOffset;
			CurrentPage = CurrentPage->_NextPage;
		}

		return TotalSize;
	}

	inline void* Arena::Push(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept
	{
		if (Size == 0)
		{
			return nullptr;
		}

		if (AlignSize == 0 ||
			(AlignSize & (AlignSize - 1)) == 1)	// is power of two
		{
			return nullptr;
		}

		ArenaPage* CurrentPage = _CurrentPage;
		Elysium::Core::Template::System::byte* CurrentAddress = &CurrentPage->_Data[CurrentPage->_CurrentOffset];

		// use a bithack to calculate modulus "reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) % AlignSize"
		const Elysium::Core::Template::System::uint64_t Padding =
			(~reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) + 1) & (AlignSize - 1);

		CurrentAddress += Padding;
		if (CurrentAddress + Size > &CurrentPage->_Data[CurrentPage->_Capacity])
		{	// @ToDo: resize strategy?
			return nullptr;
		}

		CurrentPage->_CurrentOffset += (Padding + Size);

		return CurrentAddress;
	}

	template<Elysium::Core::Template::Concepts::Trivial T>
	inline T* Arena::Push(const Elysium::Core::Template::System::size NumberOfElements) noexcept
	{
		static constexpr const Elysium::Core::Template::System::size AlignSize = alignof(T);
		static constexpr const Elysium::Core::Template::System::size Size = sizeof(T);

		const Elysium::Core::Template::System::size AllocationSize = Size * NumberOfElements;

		void* Data = Push(AllocationSize, AlignSize);
		if (Data == nullptr)
		{
			return nullptr;
		}
		
		// always necessary, memory could have been used before!
		Elysium::Core::Template::Memory::MemSet(Data, 0, AllocationSize);

		return reinterpret_cast<T*>(Data);
	}

	inline void Arena::Pop(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept
	{
		if (Size == 0)
		{
			return;
		}

		if (AlignSize == 0 ||
			(AlignSize & (AlignSize - 1)) == 1)	// is power of two
		{
			return;
		}

		ArenaPage* CurrentPage = _CurrentPage;
		Elysium::Core::Template::System::byte* CurrentAddress = &CurrentPage->_Data[CurrentPage->_CurrentOffset];

		// use a bithack to calculate modulus "reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) % AlignSize"
		const Elysium::Core::Template::System::uint64_t Padding =
			(~reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) + 1) & (AlignSize - 1);

		CurrentAddress -= Padding;
		if (CurrentAddress - Size < CurrentPage->_Data)
		{	// @ToDo: this seems like an actual error on the user's part!
			return;
		}

		CurrentPage->_CurrentOffset -= (Padding + Size);
	}

	template<Elysium::Core::Template::Concepts::Trivial T>
	inline void Arena::Pop(const Elysium::Core::Template::System::size NumberOfElements) noexcept
	{
		static constexpr const Elysium::Core::Template::System::size AlignSize = alignof(T);
		static constexpr const Elysium::Core::Template::System::size Size = sizeof(T);

		Pop(Size * NumberOfElements, AlignSize);
	}

	inline void Arena::Clear() noexcept
	{
		ArenaPage* CurrentPage = _CurrentPage;
		while (CurrentPage != nullptr)
		{
			if (CurrentPage->_Data != nullptr)
			{
				if (_Options._UseVirtualPaging)
				{
#if defined ELYSIUM_CORE_OS_WINDOWS
					BOOL Result = VirtualFreeEx(GetCurrentProcess(), CurrentPage->_Data, 0, MEM_RELEASE);
					if (Result == FALSE)
					{
						// @ToDo: assert
						throw 1;
					}
#else
#error "unhandled operating system"
#endif
				}
				else
				{
					delete[] CurrentPage->_Data;
				}
				CurrentPage->_Data = nullptr;
			}

			CurrentPage = CurrentPage->_NextPage;
		}
	}

	inline ArenaPage* Arena::CreatePage(const Elysium::Core::Template::System::size PageSize, ArenaPage* PreviousPage) noexcept
	{
		void* Data = nullptr;

		if (_Options._UseVirtualPaging)
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			Data = VirtualAllocEx(GetCurrentProcess(), 0, PageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
#error "unhandled operating system"
#endif
		}
		else
		{
			Data = new Elysium::Core::Template::System::byte[PageSize];
		}

		if (Data == nullptr)
		{
			// @ToDo: assert
			throw 1;
		}

		if (_Options._ClearMemory)
		{
			Elysium::Core::Template::Memory::MemSet(Data, 0, PageSize);
		}

		ArenaPage* Page = new ArenaPage();
		Page->_Data = reinterpret_cast<Elysium::Core::Template::System::byte*>(Data);
		Page->_Capacity = PageSize;
		Page->_CurrentOffset = 0;
		Page->_NextPage = PreviousPage;

		return Page;
	}
}
#endif
