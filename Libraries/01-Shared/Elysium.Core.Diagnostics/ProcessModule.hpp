/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSMODULE
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESSMODULE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class Process;

	class ELYSIUM_CORE_API ProcessModule final
	{
		friend class Process;
	private:
		constexpr ProcessModule(Elysium::Core::Template::Text::String<char8_t>&& Name, Elysium::Core::Template::Text::String<char8_t>&& FileName,
			void* BaseAddress, void* EntryPoint, Elysium::Core::Template::System::uint32_t SizeOfImage, Elysium::Core::Template::System::uint32_t Id) noexcept;
	public:
		constexpr ProcessModule();

		constexpr ProcessModule(const ProcessModule& Source);

		constexpr ProcessModule(ProcessModule&& Right) noexcept;

		constexpr ~ProcessModule();
	public:
		constexpr ProcessModule& operator=(const ProcessModule& Source);

		constexpr ProcessModule& operator=(ProcessModule&& Right) noexcept;
	public:
		const Elysium::Core::Template::Text::String<char8_t> GetModuleName() const;

		const Elysium::Core::Template::Text::String<char8_t> GetFileName() const;

		const void* GetBaseAddress() const;

		const void* GetEntryPoint() const;

		const Elysium::Core::Template::System::uint32_t GetSizeOfImage() const;

		const Elysium::Core::Template::System::uint32_t GetId() const;
	private:
		Elysium::Core::Template::Text::String<char8_t> _Name;
		Elysium::Core::Template::Text::String<char8_t> _FileName;
		void* _BaseAddress;
		void* _EntryPoint;
		Elysium::Core::Template::System::uint32_t _SizeOfImage;
		Elysium::Core::Template::System::uint32_t _Id;
	};
}
#endif
