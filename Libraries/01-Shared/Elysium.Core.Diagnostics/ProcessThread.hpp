/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSTHREAD
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESSTHREAD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class Process;

	class ELYSIUM_CORE_API ProcessThread final
	{
		friend class Process;
	private:
		constexpr ProcessThread(const Elysium::Core::Template::System::uint32_t Id, const Elysium::Core::Template::System::uint32_t OwnerProcessId, 
			const Elysium::Core::Template::System::int32_t BasePriority, const Elysium::Core::Template::System::int32_t CurrentPriority) noexcept;
	public:
		constexpr ProcessThread();

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
}
#endif
