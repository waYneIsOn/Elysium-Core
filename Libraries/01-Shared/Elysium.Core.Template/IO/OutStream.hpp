/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_OUTSTREAM
#define ELYSIUM_CORE_TEMPLATE_IO_OUTSTREAM

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::IO
{
	// @ToDo: concept for sources!
	template<class Source>
	class OutStream
	{
	public:
		using DeviceType = Source::DeviceType;
	public:
		constexpr OutStream() noexcept = delete;

		inline constexpr OutStream(Source& Source) noexcept
			: _Source(Source)
		{ }

		constexpr OutStream(const OutStream& Source) = delete;

		constexpr OutStream(OutStream&& Right) noexcept = delete;

		~OutStream()
		{
			Close();
		}
	public:
		constexpr OutStream& operator=(const OutStream& Source) = delete;

		constexpr OutStream& operator=(OutStream&& Right) noexcept = delete;
	public:
		inline void SetPosition(const Elysium::Core::Template::System::size Value)
		{
			_Source.SetPosition(Value);
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _Source.Close(); })
			{
				_Source.Close();
			}
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			return _Source.ReadBlock(DataView);
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			_Source.AdvanceReadingBlock(Length);
		}
	private:
		Source& _Source;
	};
}
#endif
