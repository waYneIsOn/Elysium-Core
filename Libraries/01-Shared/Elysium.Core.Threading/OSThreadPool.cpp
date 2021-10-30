#include "OSThreadPool.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef _APISETLIBLOADER_
#include <libloaderapi.h>
#endif

Elysium::Core::Threading::Internal::OSThreadPool::OSThreadPool(const Elysium::Core::uint32_t Minimum, const Elysium::Core::uint32_t Maximum)
	: _Handle(ELYSIUM_THREADPOOL_CREATE(nullptr)), _Environment(ELYSIUM_THREADPOOL_ENVIRONMENT()), _CleanupGroup(ELYSIUM_THREADPOOL_CLEANUPGROUP_CREATE()),
	_MaxThreads(Maximum), _MinThreads(Minimum)
{
	ELYSIUM_THREADPOOL_ENVIRONMENT_INITIALIZE(&_Environment);
	ELYSIUM_THREADPOOL_SET_CALLBACK_POOL(&_Environment, _Handle);

	// ToDo: use Assembly::GetExecutingAssembly()
	const wchar_t* ExecutingModuleName = L"Elysium.Core.dll";
	HMODULE ExecutingModuleHandle = nullptr;
	bool Result = GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)ExecutingModuleName, &ExecutingModuleHandle);

	ELYSIUM_THREADPOOL_SET_CALLBACK_LIBRARY(&_Environment, ExecutingModuleHandle);
	ELYSIUM_THREADPOOL_SET_CALLBACK_CLEANUPGROUP(&_Environment, _CleanupGroup, nullptr);

	const bool SetMaxThreadsResult = SetMaxThreads(Maximum);
	const bool SetMinThreadsResult = SetMinThreads(Minimum);
}

Elysium::Core::Threading::Internal::OSThreadPool::~OSThreadPool()
{
	ELYSIUM_THREADPOOL_CLEANUPGROUP_CLOSE_MEMBERS(_CleanupGroup, false, nullptr);

	ELYSIUM_THREADPOOL_CLEANUPGROUP_CLOSE(_CleanupGroup);
	ELYSIUM_THREADPOOL_ENVIRONMENT_DESTROY(&_Environment);
	ELYSIUM_THREADPOOL_CLOSE(_Handle);
}

void Elysium::Core::Threading::Internal::OSThreadPool::GetAvailableThreads(Elysium::Core::uint32_t & Threads) const
{	// ToDo: this should return the difference of _MaxThreads and currently used ones 
	Threads = _MaxThreads;
}

void Elysium::Core::Threading::Internal::OSThreadPool::GetMaxThreads(Elysium::Core::uint32_t & Threads) const
{
	Threads = _MaxThreads;
}

void Elysium::Core::Threading::Internal::OSThreadPool::GetMinThreads(Elysium::Core::uint32_t & Threads) const
{
	Threads = _MinThreads;
}

const bool Elysium::Core::Threading::Internal::OSThreadPool::SetMaxThreads(const Elysium::Core::uint32_t Threads)
{
	ELYSIUM_THREADPOOL_SET_THREAD_MAXIMUM(_Handle, Threads);
	_MaxThreads = Threads;

	return true;
}

const bool Elysium::Core::Threading::Internal::OSThreadPool::SetMinThreads(const Elysium::Core::uint32_t Threads)
{
	_MinThreads = Threads;
	return ELYSIUM_THREADPOOL_SET_THREAD_MINIMUM(_Handle, Threads);
}
