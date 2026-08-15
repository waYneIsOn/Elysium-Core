/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_TLSSOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_TLSSOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../../Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
#if defined ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATION_TLS

#elif defined ELYSIUM_CORE_OS_WINDOWS
	// @ToDo: concept for sources!
	template <class InnerSource>
	class TlsSource
	{
	public:
		using DeviceType = InnerSource::DeviceType;

		using MostInnerSourceType = InnerSource::MostInnerSourceType;
	public:
		constexpr TlsSource() noexcept = delete;

		inline constexpr TlsSource(InnerSource& InnerSource) noexcept
			: _InnerSource(InnerSource)
		{}

		constexpr TlsSource(const TlsSource& Source) = delete;

		constexpr TlsSource(TlsSource&& Right) noexcept = delete;

		~TlsSource() = default;
	public:
		constexpr TlsSource& operator=(const TlsSource& Source) = delete;

		constexpr TlsSource& operator=(TlsSource&& Right) noexcept = delete;
	public:
		inline MostInnerSourceType& GetMostInnerSource()
		{
			return *this;
		}

		inline DeviceType& GetDevice()
		{
			return _InnerSource.GetDevice();
		}

		inline constexpr DeviceType& GetDevice() const
		{
			return _InnerSource.GetDevice();
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			throw;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			throw;
		}
	private:
		InnerSource& _InnerSource;
	};
#endif
}
#endif
