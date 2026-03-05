/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSTHREAD
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSTHREAD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
	/*
	class ProcessThread final
	{
	public:
		constexpr ProcessThread() = delete;

		constexpr ProcessThread(const Elysium::Core::Template::System::uint32_t Id, const Elysium::Core::Template::System::uint32_t OwnerProcessId,
			const Elysium::Core::Template::System::int32_t BasePriority, const Elysium::Core::Template::System::int32_t CurrentPriority) noexcept;

		constexpr ProcessThread(const ProcessThread& Source);

		constexpr ProcessThread(ProcessThread&& Right) noexcept;

		constexpr ~ProcessThread();
	public:
		constexpr ProcessThread& operator=(const ProcessThread& Source);

		constexpr ProcessThread& operator=(ProcessThread&& Right) noexcept;
	public:
		const Elysium::Core::Template::System::uint32_t GetId() const;

		const Elysium::Core::Template::System::uint32_t GetOwnedProcessId() const;

		const Elysium::Core::Template::System::int32_t GetBasePriority() const;

		const Elysium::Core::Template::System::int32_t GetCurrentPriority() const;
	private:
		Elysium::Core::Template::System::uint32_t _Id;
		Elysium::Core::Template::System::uint32_t _OwnerProcessId;

		Elysium::Core::Template::System::int32_t _BasePriority;
		Elysium::Core::Template::System::int32_t _CurrentPriority;
	};
	*/
}
#endif
