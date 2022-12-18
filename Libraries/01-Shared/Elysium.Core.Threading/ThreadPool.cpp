#include "ThreadPool.hpp"

void Elysium::Core::Threading::ThreadPool::GetAvailableThreads(Elysium::Core::uint32_t & WorkerThreads, Elysium::Core::uint32_t & CompletionPortThreads)
{
	_WorkerPool.GetAvailableThreads(WorkerThreads);
	_IOPool.GetAvailableThreads(CompletionPortThreads);
}

void Elysium::Core::Threading::ThreadPool::GetMaxThreads(Elysium::Core::uint32_t & WorkerThreads, Elysium::Core::uint32_t & CompletionPortThreads)
{
	_WorkerPool.GetMaxThreads(WorkerThreads);
	_IOPool.GetMaxThreads(CompletionPortThreads);
}

void Elysium::Core::Threading::ThreadPool::GetMinThreads(Elysium::Core::uint32_t & WorkerThreads, Elysium::Core::uint32_t & CompletionPortThreads)
{
	_WorkerPool.GetMinThreads(WorkerThreads);
	_IOPool.GetMinThreads(CompletionPortThreads);
}

const bool Elysium::Core::Threading::ThreadPool::SetMaxThreads(const Elysium::Core::uint32_t WorkerThreads, const Elysium::Core::uint32_t CompletionPortThreads)
{
	return _WorkerPool.SetMaxThreads(WorkerThreads) && _IOPool.SetMaxThreads(CompletionPortThreads);
}

const bool Elysium::Core::Threading::ThreadPool::SetMinThreads(const Elysium::Core::uint32_t WorkerThreads, const Elysium::Core::uint32_t CompletionPortThreads)
{
	return _WorkerPool.SetMinThreads(WorkerThreads) && _IOPool.SetMinThreads(CompletionPortThreads);
}
