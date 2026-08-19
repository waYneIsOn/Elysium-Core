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
	// @ToDo: concept for sources!
	template <class InnerSource, class TlsSession>
	class TlsSource
	{
	public:
		using DeviceType = InnerSource::DeviceType;

		using MostInnerSourceType = InnerSource::MostInnerSourceType;
	public:
		constexpr TlsSource() noexcept = delete;

		inline constexpr TlsSource(InnerSource& InnerSourceX, TlsSession& Session) noexcept
			: _InnerSource(InnerSourceX), _Session(Session)
		{ }

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
		
		inline constexpr const TlsSession& GetSession() const
		{
			return _Session;
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
		TlsSession& _Session;
	};
}
#endif
