#include "ThreadPool.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

Elysium::Core::Threading::ThreadPool::ThreadPool()
	: _WorkerThreads(Elysium::Core::Collections::Template::Array<Thread>(Environment::ProcessorCount() - 1)),
	_IOThreads(Elysium::Core::Collections::Template::Array<Thread>(Environment::ProcessorCount() * 10)),
	_ShouldStop(false), _IsRunning(false)
{ }
Elysium::Core::Threading::ThreadPool::ThreadPool(const size_t NumberOfWorkerThreads, const size_t NumberOfIOThreads)
	: _WorkerThreads(Elysium::Core::Collections::Template::Array<Thread>(NumberOfWorkerThreads)),
	_IOThreads(Elysium::Core::Collections::Template::Array<Thread>(NumberOfIOThreads)),
	_ShouldStop(false), _IsRunning(false)
{ }
Elysium::Core::Threading::ThreadPool::~ThreadPool()
{ }

void Elysium::Core::Threading::ThreadPool::Start()
{
	if (_IsRunning)
	{
		return;
	}
	_ShouldStop = false;

	for (size_t i = 0; i < _WorkerThreads.GetLength(); i++)
	{
		_WorkerThreads[i].Start(Delegate<void>::CreateDelegate<ThreadPool, &ThreadPool::RunWorker>(*this));
	}
	for (size_t i = 0; i < _IOThreads.GetLength(); i++)
	{
		_IOThreads[i].Start(Delegate<void>::CreateDelegate<ThreadPool, &ThreadPool::RunIO>(*this));
	}

	_IsRunning = true;
}
void Elysium::Core::Threading::ThreadPool::Stop()
{
	if (!_IsRunning)
	{
		return;
	}
	_ShouldStop = true;

	for (size_t i = 0; i < _WorkerThreads.GetLength(); i++)
	{
		_WorkerThreads[i].Join();
	}
	for (size_t i = 0; i < _IOThreads.GetLength(); i++)
	{
		_WorkerThreads[i].Join();
	}

	_IsRunning = false;
}

void Elysium::Core::Threading::ThreadPool::RunWorker()
{
	do
	{

	} while (!_ShouldStop);
}
void Elysium::Core::Threading::ThreadPool::RunIO()
{
	do
	{

	} while (!_ShouldStop);
}
