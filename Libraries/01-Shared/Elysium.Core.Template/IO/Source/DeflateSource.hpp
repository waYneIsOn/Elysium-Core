/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_DEFLATESOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_DEFLATESOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	// @ToDo: concept for sources!
	template <class InnerSource>
	class DeflateSource
	{
	public:
		using DeviceType = InnerSource::DeviceType;
	public:
		inline constexpr DeflateSource(InnerSource& InnerSource, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _InnerSource(InnerSource)
		{ }

		constexpr DeflateSource(const DeflateSource& Source) = delete;

		constexpr DeflateSource(DeflateSource&& Right) noexcept = delete;

		inline ~DeflateSource()
		{
			Close();
		}
	public:
		constexpr DeflateSource& operator=(const DeflateSource& Source) = delete;

		constexpr DeflateSource& operator=(DeflateSource&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSource.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSource.GetPosition();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSource.GetDevice();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSource.SetPosition(Position);
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _InnerSource.Close(); })
			{
				_InnerSource.Close();
			}
		}

		inline const Elysium::Core::Template::System::size Read(Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			const Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&Buffer[0], Count);

			return BytesRead;
		}
	private:
		InnerSource& _InnerSource;
	};
}
#endif
