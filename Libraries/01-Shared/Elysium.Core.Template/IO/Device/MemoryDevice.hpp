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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../../Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../../Math/Min.hpp"
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
			_Buffer.Clear();
		}

		constexpr MemoryDevice(const MemoryDevice& Source) = delete;

		constexpr MemoryDevice(MemoryDevice&& Right) noexcept = delete;

		constexpr ~MemoryDevice() = default;
	public:
		constexpr MemoryDevice& operator=(const MemoryDevice& Source) = delete;

		constexpr MemoryDevice& operator=(MemoryDevice&& Right) noexcept = delete;
	public:
		inline constexpr const bool operator==(const MemoryDevice& Other) const noexcept
		{
			return &_Buffer == &Other._Buffer;
		}

		inline constexpr const bool operator!=(const MemoryDevice& Other) const noexcept
		{
			return &_Buffer != &Other._Buffer;
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
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			if (_Position >= _Buffer.GetLength())
			{
				return Elysium::Core::Template::IO::ReadResult::EndOfStream;
			}

			DataView.SetData(&_Buffer[_Position]);
			DataView.SetLength(_Buffer.GetLength() - _Position);

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			if (_Position + Length > _Buffer.GetLength())
			{	// @ToDo
				throw 1;
			}

			_Position += Length;
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				return;
			}
			
			_Buffer.Reserve(_Position + Count);

			Elysium::Core::Template::System::size LeftOver = Count;
			if (_Position < _Buffer.GetLength())
			{
				Elysium::Core::Template::System::size Available = Elysium::Core::Template::Math::Min(Count, _Buffer.GetLength() - _Position);

				Elysium::Core::Template::Memory::MemCpy(&_Buffer[_Position], Buffer, Available);

				LeftOver -= Available;
			}

			_Buffer.PushBackRange(Buffer, LeftOver);

			_Position += Count;
		}
	private:
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
	};
}
#endif
