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
#include "../MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAPAGE
#include "ArenaPage.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef _ASSERT_OK
#include <cassert>
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
/*
	#ifndef _WINDOWS_
	//#define _WINSOCKAPI_ // don't include winsock
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#endif

	#ifndef _MEMORYAPI_H_
	#include <memoryapi.h>
	#endif

	#ifndef _PROCESSTHREADSAPI_H_
	#include <processthreadsapi.h>
	#endif
*/
#endif

namespace Elysium::Core::Template::Memory::Scoped
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="InitialPageSize"></typeparam>
	/// <typeparam name="NumberOfPreallocatedPages"></typeparam>
	/// <typeparam name="UseVirtualPaging"></typeparam>
	/// <typeparam name="ClearMemory"></typeparam>
	template <Elysium::Core::Template::System::size InitialPageSize = 4096, Elysium::Core::Template::System::size NumberOfPreallocatedPages = 1, bool UseVirtualPaging = false,
		bool ClearMemory = false>
	class Arena
	{
	public:
		inline Arena()
			: _CurrentPage(CreatePage(InitialPageSize))
		{ }
		
		constexpr Arena(const Arena&& Source) = delete;

		constexpr Arena(Arena&& Right) = delete;

		inline ~Arena() noexcept
		{
			ArenaPage* CurrentPage = _CurrentPage;
			while (nullptr != CurrentPage)
			{
				CurrentPage = DestroyPage(CurrentPage);
			}
		}
	public:
		constexpr Arena& operator=(const Arena& Source) = delete;

		constexpr Arena& operator=(Arena&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Returns the number of pages currently allocated.
		/// </summary>
		/// <returns></returns>
		inline const Elysium::Core::Template::System::size GetNumberOfPages() const
		{
			Elysium::Core::Template::System::size NumberOfPages = 0;

			ArenaPage* CurrentPage = _CurrentPage;
			while (nullptr != CurrentPage)
			{
				++NumberOfPages;
				CurrentPage = CurrentPage->_NextPage;
			}

			return NumberOfPages;
		}

		/// <summary>
		/// Returns the total capacity overarching all pages currently allocated.
		/// </summary>
		/// <returns></returns>
		inline const Elysium::Core::Template::System::size GetCapacity() const
		{
			Elysium::Core::Template::System::size TotalCapacity = 0;

			ArenaPage* CurrentPage = _CurrentPage;
			while (nullptr != CurrentPage)
			{
				TotalCapacity += CurrentPage->_Capacity;
				CurrentPage = CurrentPage->_NextPage;
			}

			return TotalCapacity;
		}

		/// <summary>
		/// Returns total number of bytes used overarching all pages currently allocated.
		/// </summary>
		/// <returns></returns>
		inline const Elysium::Core::Template::System::size GetSize() const
		{
			Elysium::Core::Template::System::size TotalSize = 0;

			ArenaPage* CurrentPage = _CurrentPage;
			while (nullptr != CurrentPage)
			{
				TotalSize += CurrentPage->_CurrentOffset;
				CurrentPage = CurrentPage->_NextPage;
			}

			return TotalSize;
		}
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Size"></param>
		/// <param name="AlignSize"></param>
		/// <returns></returns>
		inline void* Push(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize = alignof(Elysium::Core::Template::System::size)) noexcept
		{
			return PushInternally(Size, AlignSize, 0);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		template<Elysium::Core::Template::Concepts::Trivial T>
		inline T* Push(const Elysium::Core::Template::System::size NumberOfElements = 1) noexcept
		{
			static constexpr const Elysium::Core::Template::System::size AlignSize = alignof(T);
			static constexpr const Elysium::Core::Template::System::size Size = sizeof(T);

			const Elysium::Core::Template::System::size AllocationSize = Size * NumberOfElements;

			void* Data = PushInternally(AllocationSize, AlignSize, 0);
			if (nullptr == Data)
			{
				return nullptr;
			}

			// always necessary, memory could have been used before!
			Elysium::Core::Template::Memory::MemSet(Data, 0, AllocationSize);

			return reinterpret_cast<T*>(Data);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Size"></param>
		/// <param name="AlignSize"></param>
		inline void Pop(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept
		{
			if (Size == 0)
			{
				return;
			}

			if (AlignSize == 0 || (AlignSize & (AlignSize - 1)) != 0)	// is power of two
			{
				return;
			}

			ArenaPage* CurrentPage = _CurrentPage;
			Elysium::Core::Template::System::byte* CurrentAddress = &CurrentPage->_Data[CurrentPage->_CurrentOffset];

			// use a bithack for padding ("normal" calculation below for debug-assertion)
			const Elysium::Core::Template::System::size Padding =
				(~reinterpret_cast<Elysium::Core::Template::System::size>(CurrentAddress) + 1) & (AlignSize - 1);
			const Elysium::Core::Template::System::size AdditionalSize = Padding + Size;

#ifdef _DEBUG
			const Elysium::Core::Template::System::size DebugPaddingStep1 =
				reinterpret_cast<Elysium::Core::Template::System::size>(CurrentAddress) % AlignSize;
			const Elysium::Core::Template::System::size DebugPadding = DebugPaddingStep1 == 0 ? DebugPaddingStep1 :
				AlignSize - DebugPaddingStep1;
			assert("Elysium::Core::Template::Memory::Scoped::Arena.Pop(...): " && DebugPadding == Padding);
#endif

			if (CurrentAddress - AdditionalSize < CurrentPage->_Data)
			{	// @ToDo: this seems like an actual error on the user's part!
				return;
			}

			CurrentPage->_CurrentOffset -= AdditionalSize;
		}
		
		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="NumberOfElements"></param>
		template<Elysium::Core::Template::Concepts::Trivial T>
		inline void Pop(const Elysium::Core::Template::System::size NumberOfElements = 1) noexcept
		{
			static constexpr const Elysium::Core::Template::System::size AlignSize = alignof(T);
			static constexpr const Elysium::Core::Template::System::size Size = sizeof(T);

			Pop(Size * NumberOfElements, AlignSize);
		}
		
		/// <summary>
		/// Clears the arena, keeping all pages and allocated memory.
		/// </summary>
		inline void Clear() noexcept
		{
			ArenaPage* CurrentPage = _CurrentPage;
			while (nullptr != CurrentPage)
			{
				CurrentPage->_CurrentOffset = 0;
				CurrentPage = CurrentPage->_NextPage;
			}
		}

		/// <summary>
		/// Destroys all pages except the first one, which will be cleared, keeping it's allocated memory.
		/// </summary>
		inline void Reset() noexcept
		{
			// only clear the first page
			ArenaPage* CurrentPage = _CurrentPage;
			if (nullptr == CurrentPage)
			{
				return;
			}
			CurrentPage->_CurrentOffset = 0;

			ArenaPage* PreviousPage = CurrentPage;
			CurrentPage = CurrentPage->_NextPage;
			PreviousPage->_NextPage = nullptr;

			// destroy all other pages
			while (nullptr != CurrentPage)
			{
				CurrentPage = DestroyPage(CurrentPage);
			}
		}
	private:
		inline ArenaPage* CreatePage(const Elysium::Core::Template::System::size PageSize, ArenaPage* PreviousPage = nullptr) noexcept
		{
			/*
			// Since this method is only used internally, I do not need to check.
			if (0 == PageSize)
			{
				return nullptr;
			}
			*/
			void* Data = nullptr;

			if constexpr (UseVirtualPaging)
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
				assert("Elysium::Core::Template::Memory::Scoped::Arena.CreatePage(...): Couldn't allocate any memory.");
			}

#ifdef _DEBUG
			assert("Elysium::Core::Template::Memory::Scoped::Arena.CreatePage(...): " &&
				(reinterpret_cast<Elysium::Core::Template::System::size>(Data) % 8) == 0);
#endif

			if constexpr (ClearMemory)
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

		inline ArenaPage* DestroyPage(ArenaPage* Page) noexcept
		{
			/*
			// Since this method is only used internally, I do not need to check.
			if (Page == nullptr)
			{
				return;
			}
			*/
			if (Page->_Data != nullptr)
			{
				if constexpr (UseVirtualPaging)
				{
#if defined ELYSIUM_CORE_OS_WINDOWS
					BOOL Result = VirtualFreeEx(GetCurrentProcess(), Page->_Data, 0, MEM_RELEASE);
					if (Result == FALSE)
					{
						// @ToDo: assert
						bool bla = false;
					}
#else
#error "unhandled operating system"
#endif
				}
				else
				{
					delete[] Page->_Data;
				}
				Page->_Data = nullptr;
			}

			ArenaPage* NextPage = Page->_NextPage;

			delete Page;

			return NextPage;
		}
	private:
		inline void* PushInternally(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize, Elysium::Core::Template::System::size RecursionDepth)
		{
			assert("Elysium::Core::Template::Memory::Scoped::Arena.PushInternally(...): " && RecursionDepth < 2);

			if (0 == Size)
			{
				return nullptr;
			}

			if (0 == AlignSize || 0 != (AlignSize & (AlignSize - 1)))	// is power of two
			{
				return nullptr;
			}

			ArenaPage* CurrentPage = _CurrentPage;
			Elysium::Core::Template::System::byte* CurrentAddress = &CurrentPage->_Data[CurrentPage->_CurrentOffset];

			// use a bithack for padding ("normal" calculation below for debug-assertion)
			const Elysium::Core::Template::System::size Padding =
				(~reinterpret_cast<Elysium::Core::Template::System::size>(CurrentAddress) + 1) & (AlignSize - 1);
			const Elysium::Core::Template::System::size AdditionalSize = Padding + Size;

#ifdef _DEBUG
			const Elysium::Core::Template::System::size DebugPaddingStep1 =
				reinterpret_cast<Elysium::Core::Template::System::size>(CurrentAddress) % AlignSize;
			const Elysium::Core::Template::System::size DebugPadding = DebugPaddingStep1 == 0 ? DebugPaddingStep1 :
				AlignSize - DebugPaddingStep1;
			assert("Elysium::Core::Template::Memory::Scoped::Arena.PushInternally(...): " && DebugPadding == Padding);
#endif

			if (CurrentAddress + AdditionalSize > &CurrentPage->_Data[CurrentPage->_Capacity])
			{
				// I need to regard _CurrentPage as being "fully used", simply because "allocating" x numbers of elements on this page
				// and the rest on the next page simply won't work!
				// @ToDo: can think about splitting "memory-push" and "-usage" into seperate methods to make it possible to not "waste" memory.
				// As it stands it's the user's responsibiliy to manage memory.
				// @ToDo: alternatively I could set a flag that a page has "skipped" memory and check whether I can push there later
				_CurrentPage->_CurrentOffset = _CurrentPage->_Capacity;

				// Creating a new page means having to allocate enough memory for given Size plus necessary padding.
				// Most modern systems will return a "power of two" based address meaning no padding will be required on the new page.
				// @ToDo: If I'm ever in a situation where RecursionDepth equals 2, I need to check for this again!
				const Elysium::Core::Template::System::size PageSize = Size > InitialPageSize ? Size : InitialPageSize;
				_CurrentPage = CreatePage(PageSize, _CurrentPage);

				return PushInternally(Size, AlignSize, ++RecursionDepth);
			}

			CurrentPage->_CurrentOffset += AdditionalSize;

			return CurrentAddress;
		}
	private:
		ArenaPage* _CurrentPage{};
	};
}
#endif
