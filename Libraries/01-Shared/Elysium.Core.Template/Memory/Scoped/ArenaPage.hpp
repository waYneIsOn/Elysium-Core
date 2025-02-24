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
		ArenaPage(Elysium::Core::Template::System::size Capacity) noexcept;
	public:
		ArenaPage() = delete;

		ArenaPage(const ArenaPage&& Source) = delete;

		ArenaPage(ArenaPage&& Right) = delete;

		~ArenaPage() noexcept;
	public:
		ArenaPage& operator=(const ArenaPage& Source) = delete;

		ArenaPage& operator=(ArenaPage&& Right) noexcept = delete;
	public:
		//bool IsFull() const noexcept;
	private:
		void* Push(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept;

		void Pop(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept;

		void Clear() noexcept;
	private:
		Elysium::Core::Template::System::byte* _Data;
		Elysium::Core::Template::System::size _Capacity;
		Elysium::Core::Template::System::size _CurrentOffset;
		ArenaPage* _NextPage;
	};

	inline ArenaPage::ArenaPage(Elysium::Core::Template::System::size Capacity) noexcept
		: _Data(static_cast<Elysium::Core::Template::System::byte*>(malloc(Capacity))), _Capacity(Capacity),
		_CurrentOffset(0), _NextPage(nullptr)
	{ }

	inline ArenaPage::~ArenaPage() noexcept
	{
		Clear();
	}

	inline void* ArenaPage::Push(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept
	{
		Elysium::Core::Template::System::byte* CurrentAddress = &_Data[_CurrentOffset];

		// use a bithack to calculate modulus "reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) % AlignSize"
		const Elysium::Core::Template::System::uint64_t Padding =
			(~reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) + 1) & (AlignSize - 1);

		CurrentAddress += Padding;
		if (CurrentAddress + Size > (_Data + _Capacity))
		{	// @ToDo: resize strategy? linked list? virtual page?
			return nullptr;
		}

		_CurrentOffset += (Padding + Size);

		return CurrentAddress;
	}

	inline void ArenaPage::Pop(const Elysium::Core::Template::System::size Size, const Elysium::Core::Template::System::size AlignSize) noexcept
	{
		Elysium::Core::Template::System::byte* CurrentAddress = &_Data[_CurrentOffset];

		// use a bithack to calculate modulus "reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) % AlignSize"
		const Elysium::Core::Template::System::uint64_t Padding =
			(~reinterpret_cast<Elysium::Core::Template::System::uint64_t>(CurrentAddress) + 1) & (AlignSize - 1);

		CurrentAddress -= Padding;
		if (CurrentAddress - Size < _Data)
		{	// @ToDo: resize strategy? linked list? virtual page?
			return;
		}

		_CurrentOffset -= (Padding + Size);
	}
	
	inline void ArenaPage::Clear() noexcept
	{
		if (_Data != nullptr)
		{
			free(_Data);
			_Data = nullptr;
		}
	}
}
#endif
