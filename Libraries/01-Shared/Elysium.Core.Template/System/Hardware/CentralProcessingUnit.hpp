/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_HARDWARE_CENTRALPROCESSINGUNIT
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_HARDWARE_CENTRALPROCESSINGUNIT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../../Exceptions/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS

#ifndef _SYSINFOAPI_H_
#include <sysinfoapi.h>
#endif

#else
#error "undefined os"
#endif

namespace Elysium::Core::Template::System::Hardware
{
	class CentralProcessingUnit
	{
	public:
		/// <summary>
		/// Returns the overall number of CPUs.
		/// </summary>
		/// <returns></returns>
		inline static Elysium::Core::Template::System::uint32_t GetCount()
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			return GetCountOf(LOGICAL_PROCESSOR_RELATIONSHIP::RelationProcessorPackage);
#else
			return 0;
#endif
		}

		/// <summary>
		/// Gets the overall number of currently active logical cores.
		/// </summary>
		/// <returns></returns>
		inline static Elysium::Core::Template::System::uint32_t GetCountOfActiveLogicalCores()
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			return GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
#else
			return 0;
#endif
		}

		/// <summary>
		/// Gets the overall number of logical cores.
		/// </summary>
		/// <returns></returns>
		inline static Elysium::Core::Template::System::uint32_t GetCountOfLogicalCores()
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			return GetMaximumProcessorCount(ALL_PROCESSOR_GROUPS);
#else
			return 0;
#endif
		}

		/// <summary>
		/// Gets the overall number of phsyical cores.
		/// </summary>
		/// <returns></returns>
		inline static Elysium::Core::Template::System::uint32_t GetCountOfPhysicalCores()
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			return GetCountOf(LOGICAL_PROCESSOR_RELATIONSHIP::RelationProcessorCore);
#else
			return 0;
#endif
		}
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static Elysium::Core::Template::System::uint32_t GetCountOf(LOGICAL_PROCESSOR_RELATIONSHIP Relationship)
		{
			DWORD RequiredLength = 0;
			const BOOL InitialQueryResult = GetLogicalProcessorInformationEx(Relationship, nullptr, &RequiredLength);
			if (FALSE == InitialQueryResult)
			{
				const DWORD ErrorCode = GetLastError();
				if (ERROR_INSUFFICIENT_BUFFER != ErrorCode)
				{
					throw Elysium::Core::Template::Exceptions::SystemException(ErrorCode);
				}
			}

			//SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Information{};
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Buffer(RequiredLength);
			const BOOL QueryResult = GetLogicalProcessorInformationEx(Relationship, reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(&Buffer[0]), &RequiredLength);
			if (FALSE == QueryResult)
			{
				return 1;
			}

			PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX CurrentInformation = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(&Buffer[0]);
			DWORD Offset = 0;
			DWORD Count = 0;
			while (Offset < RequiredLength)
			{
				++Count;

				Offset += CurrentInformation->Size; 
				CurrentInformation = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(&Buffer[Offset]);
			}

			return Count;
		}
#endif
	};
}
#endif
