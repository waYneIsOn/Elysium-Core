/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_BUFFEREDSOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_BUFFEREDSOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "../../Container/FixedSizeBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	// @ToDo: concept for sources!
	template <class S>
	class BufferedSource
	{
	public:
		inline constexpr BufferedSource(S& InnerSource, const Elysium::Core::Template::System::size BufferSize = 2) noexcept
			: _Buffer(0 == BufferSize ? 4096 : BufferSize), _Position(0), _EndPosition(0), _InnerSource(InnerSource)
		{ }

		constexpr BufferedSource(const BufferedSource& Source) = delete;

		constexpr BufferedSource(BufferedSource&& Right) noexcept = delete;

		inline ~BufferedSource()
		{
			Close();
		}
	public:
		constexpr BufferedSource& operator=(const BufferedSource& Source) = delete;

		constexpr BufferedSource& operator=(BufferedSource&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSource.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSource.GetPosition();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSource.SetPosition(Position);
			_Position = 0;
			_EndPosition = 0;
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _InnerSource.Close(); })
			{
				_InnerSource.Close();
			}
		}

		inline const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
		{
			if (_Position == _EndPosition)
			{
				Elysium::Core::Template::System::size BytesToBuffer = Elysium::Core::Template::Math::Min(_Buffer.GetCapacity(), _InnerSource.GetLength());

				_Position = 0;
				_EndPosition = _InnerSource.Read(&_Buffer[_Position], BytesToBuffer);
			}

			Elysium::Core::Template::System::size BytesToRead = Elysium::Core::Template::Math::Min(_Buffer.GetCapacity(), Count);

			Elysium::Core::Template::Memory::MemCpy(Buffer, &_Buffer[_Position], BytesToRead);

			_Position += BytesToRead;

			return BytesToRead;
		}
	private:
		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
		Elysium::Core::Template::System::size _EndPosition;
		S& _InnerSource;
	};
}
#endif
