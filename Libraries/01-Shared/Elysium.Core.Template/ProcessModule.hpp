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

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif

	#ifndef _PSAPI_H_
	#include <Psapi.h>
	#endif
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class Process;

	class ProcessModule final
	{
		friend class Process;
	private:
		constexpr ProcessModule(const void* ProcessHandle, const void* ModuleHandle) noexcept;
	public:
		//ProcessModule(const ProcessModule& Source);

		//ProcessModule(ProcessModule&& Right) noexcept;

		constexpr ~ProcessModule();
	public:
		//ProcessModule& operator=(const ProcessModule& Source);

		//ProcessModule& operator=(ProcessModule&& Right) noexcept;
	public:
		const Text::String<char8_t> GetModuleName() const;

		const void* GetBaseAddress() const;
	private:
		const void* _ProcessHandle;
		const void* _ModuleHandle;
	};

	inline constexpr Elysium::Core::Template::Diagnostics::ProcessModule::ProcessModule(const void* ProcessHandle, const void* ModuleHandle) noexcept
		: _ProcessHandle(ProcessHandle), _ModuleHandle(ModuleHandle)
	{ }

	inline constexpr Elysium::Core::Template::Diagnostics::ProcessModule::~ProcessModule()
	{
		// @ToDo: do I need to close these handles? do I need to keep track of them in Process-class?
		/*
		if (_ProcessHandle != nullptr)
		{
			CloseHandle(const_cast<void*>(_ProcessHandle));
			_ProcessHandle = nullptr;
		}
		if (_ModuleHandle != nullptr)
		{
			CloseHandle(const_cast<void*>(_ModuleHandle));
			_ModuleHandle = nullptr;
		}
		*/
		_ProcessHandle = nullptr;
		_ModuleHandle = nullptr;
	}

	inline const Text::String<char8_t> ProcessModule::GetModuleName() const
	{
		// @ToDo: windows max module-(file-?)name length?
		char Name[MAX_PATH];
		if (!GetModuleBaseNameA(const_cast<void*>(_ProcessHandle), reinterpret_cast<HMODULE>(const_cast<void*>(_ModuleHandle)), Name, sizeof(Name)))
		{
			throw Exceptions::SystemException();
		}

		return Text::String<char8_t>((char8_t*)&Name);
	}

	inline const void* ProcessModule::GetBaseAddress() const
	{
		MODULEINFO ModuleInfo;
		if (!GetModuleInformation(const_cast<void*>(_ProcessHandle), reinterpret_cast<HMODULE>(const_cast<void*>(_ModuleHandle)), &ModuleInfo, sizeof(ModuleInfo))) 
		{
			throw Exceptions::SystemException();
		}

		return ModuleInfo.lpBaseOfDll;
	}
}
#endif
