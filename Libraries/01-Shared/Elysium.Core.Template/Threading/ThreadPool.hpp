/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#define ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_HARDWARE_CENTRALPROCESSINGUNIT
#include "../System/Hardware/CentralProcessingUnit.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _THREADPOOLAPISET_H_
#include <threadpoolapiset.h>
#endif

#else
#error "undefined os"
#endif

namespace Elysium::Core::Template::IO::Device
{
	class FileDevice;
}

namespace Elysium::Core::Template::Threading
{
	class ThreadPool final
	{
	private:
		friend class Elysium::Core::Template::IO::Device::FileDevice;
	public:
		constexpr ThreadPool() = delete;

		constexpr ThreadPool(const ThreadPool& Source) = delete;

		constexpr ThreadPool(ThreadPool&& Right) noexcept = delete;

		~ThreadPool() = delete;
	public:
		ThreadPool& operator=(const ThreadPool& Source) = delete;

		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;
	public:
		/*
		inline void GetAvailableThreads(Elysium::Core::Template::System::uint32_t& WorkerThreads, Elysium::Core::Template::System::uint32_t& IOThreads) const
		{

		}
		*/
		inline void GetMaxThreads(Elysium::Core::Template::System::uint32_t& WorkerThreads, Elysium::Core::Template::System::uint32_t& IOThreads) const
		{
			GetWorkerPool().GetMaxThreads(WorkerThreads);
			GetIOPool().GetMaxThreads(IOThreads);
		}

		inline void GetMinThreads(Elysium::Core::Template::System::uint32_t& WorkerThreads, Elysium::Core::Template::System::uint32_t& IOThreads) const
		{
			GetWorkerPool().GetMinThreads(WorkerThreads);
			GetIOPool().GetMinThreads(IOThreads);
		}
	public:
		inline const bool SetMaxThreads(const Elysium::Core::Template::System::uint32_t WorkerThreads, const Elysium::Core::Template::System::uint32_t IOThreads)
		{
			const bool WorkerResult = GetWorkerPool().SetMaxThreads(WorkerThreads);
			const bool IOResult = GetIOPool().SetMaxThreads(IOThreads);

			return WorkerResult && IOResult;
		}

		inline const bool SetMinThreads(const Elysium::Core::Template::System::uint32_t WorkerThreads, const Elysium::Core::Template::System::uint32_t IOThreads)
		{
			const bool WorkerResult = GetWorkerPool().SetMinThreads(WorkerThreads);
			const bool IOResult = GetIOPool().SetMinThreads(IOThreads);

			return WorkerResult && IOResult;
		}
	private:
		struct InternalThreadPool
		{
		private:
			friend class Elysium::Core::Template::IO::Device::FileDevice;
		public:
			inline InternalThreadPool(const Elysium::Core::Template::System::uint32_t Maximum, const Elysium::Core::Template::System::uint32_t Minimum)
#if defined ELYSIUM_CORE_OS_WINDOWS
				: _Handle(CreateThreadpool(nullptr)), _Environment{}, _CleanupGroup(CreateThreadpoolCleanupGroup())
			{
				InitializeThreadpoolEnvironment(&_Environment);
				SetThreadpoolCallbackPool(&_Environment, _Handle);
				/*
				// ToDo: use Assembly::GetExecutingAssembly()
				const wchar_t* ExecutingModuleName = L"Elysium.Core.dll";
				HMODULE ExecutingModuleHandle = nullptr;
				bool Result = GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)ExecutingModuleName, &ExecutingModuleHandle);

				SetThreadpoolCallbackLibrary(&_Environment, ExecutingModuleHandle);
				*/
				SetThreadpoolCallbackCleanupGroup(&_Environment, _CleanupGroup, nullptr);
				
				const bool SetMaxThreadsResult = SetMaxThreads(Maximum);
				const bool SetMinThreadsResult = SetMinThreads(Minimum);
			}
#else
				= default;
#endif

			inline ~InternalThreadPool()
#if defined ELYSIUM_CORE_OS_WINDOWS
			{
				CloseThreadpoolCleanupGroupMembers(_CleanupGroup, false, nullptr);

				CloseThreadpoolCleanupGroup(_CleanupGroup);
				DestroyThreadpoolEnvironment(&_Environment);
				CloseThreadpool(_Handle);
			}
#else
				= default;
#endif
		public:
			inline void GetMaxThreads(const Elysium::Core::Template::System::uint32_t& Value)
			{
				// @ToDo
			}

			inline void GetMinThreads(const Elysium::Core::Template::System::uint32_t& Value)
			{
				// @ToDo
			}
		public:
			inline bool SetMaxThreads(const Elysium::Core::Template::System::uint32_t Value) noexcept
			{
#if defined ELYSIUM_CORE_OS_WINDOWS
				DWORD DesiredMaxThreads = Value;
				SetThreadpoolThreadMaximum(_Handle, DesiredMaxThreads);
				if (0 == GetLastError())
				{
					return false;
				}

				return true;
#endif
			}

			inline bool SetMinThreads(const Elysium::Core::Template::System::uint32_t Value) noexcept
			{
#if defined ELYSIUM_CORE_OS_WINDOWS
				DWORD DesiredMinThreads = Value;
				return SetThreadpoolThreadMinimum(_Handle, DesiredMinThreads) == TRUE;
#endif
			}
		private:
#if defined ELYSIUM_CORE_OS_WINDOWS
			PTP_POOL _Handle;
			TP_CALLBACK_ENVIRON_V3 _Environment;
			PTP_CLEANUP_GROUP _CleanupGroup;
#endif
		};
	private:
		inline static InternalThreadPool& GetWorkerPool()
		{
			static const Elysium::Core::Template::System::uint32_t LogicalCores = Elysium::Core::Template::System::Hardware::CentralProcessingUnit::GetCountOfLogicalCores();
			static InternalThreadPool WorkerPool(LogicalCores, LogicalCores * 128 - 1);
			return WorkerPool;
		}

		inline static InternalThreadPool& GetIOPool()
		{
			static const Elysium::Core::Template::System::uint32_t LogicalCores = Elysium::Core::Template::System::Hardware::CentralProcessingUnit::GetCountOfLogicalCores();
			static InternalThreadPool IOPool(LogicalCores, 1000);
			return IOPool;
		}
	};
}
#endif
