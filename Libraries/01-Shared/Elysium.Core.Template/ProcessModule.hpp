/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSMODULE
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSMODULE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
	/*
	class ProcessModule final
	{
	public:
		constexpr ProcessModule() = delete;

		constexpr ProcessModule(Elysium::Core::Template::Text::String<char8_t>&& Name, Elysium::Core::Template::Text::String<char8_t>&& FileName,
			void* BaseAddress, void* EntryPoint, const Elysium::Core::Template::System::uint32_t SizeOfImage,
			const Elysium::Core::Template::System::uint32_t Id) noexcept;

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
	*/
}
#endif
