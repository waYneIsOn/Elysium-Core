/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_MEMORYDEVICE
#define ELYSIUM_CORE_TEMPLATE_IO_DEVICE_MEMORYDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Device
{
	class MemoryDevice
	{
	public:
		constexpr MemoryDevice() noexcept = delete;

		inline constexpr MemoryDevice(const Elysium::Core::Template::System::size Capacity) noexcept
			: _Buffer(Capacity), _Position(0)
		{
			//_Buffer.Clear();
		}

		constexpr MemoryDevice(const MemoryDevice& Source) = delete;

		constexpr MemoryDevice(MemoryDevice&& Right) noexcept = delete;

		~MemoryDevice() = default;
	public:
		constexpr MemoryDevice& operator=(const MemoryDevice& Source) = delete;

		constexpr MemoryDevice& operator=(MemoryDevice&& Right) noexcept = delete;
	public:
		inline constexpr const bool operator==(const MemoryDevice& Other) noexcept
		{
			return &_Buffer == &Other._Buffer;
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _Buffer.GetCapacity();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _Position;
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_Position = Position;
		}
	public:
		inline const Elysium::Core::Template::System::size Read(Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			Elysium::Core::Template::Memory::MemCpy(Buffer, &_Buffer[_Position], Count);
			_Position += Count;

			return Count;
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				return;
			}
			
			_Buffer.Reserve(_Position + Count);
			Elysium::Core::Template::Memory::MemCpy(&_Buffer[_Position], Buffer, Count);
			
			_Position += Count;
		}
	private:
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
	};
}
#endif
