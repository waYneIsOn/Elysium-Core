#include "ThreadPool.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "Task.hpp"
#endif

Elysium::Core::Threading::ThreadPool::ThreadPool()
	: _Threads(Elysium::Core::Collections::Template::Array<Thread>(Environment::ProcessorCount() - 1)),
	_ShouldStop(false), _IsRunning(false)
{ }
Elysium::Core::Threading::ThreadPool::ThreadPool(const size_t NumberOfThreads)
	: _Threads(Elysium::Core::Collections::Template::Array<Thread>(NumberOfThreads)),
	_ShouldStop(false), _IsRunning(false)
{ }
Elysium::Core::Threading::ThreadPool::~ThreadPool()
{ 
	Stop();
}

const size_t Elysium::Core::Threading::ThreadPool::GetNumberOfThreads() const
{
	return _Threads.GetLength();
}

void Elysium::Core::Threading::ThreadPool::Start()
{
	if (_IsRunning)
	{
		return;
	}
	_ShouldStop = false;

	for (size_t i = 0; i < _Threads.GetLength(); i++)
	{
		_Threads[i].Start(Delegate<void>::CreateDelegate<ThreadPool, &ThreadPool::Run>(*this));
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

	for (size_t i = 0; i < _Threads.GetLength(); i++)
	{
		_Threads[i].Join();
	}

	_IsRunning = false;
}

void Elysium::Core::Threading::ThreadPool::Run()
{
	/*
	Elysium::Core::Collections::Template::Array<Elysium::Core::Threading::Tasks::Task> RingBuffer = 
		Elysium::Core::Collections::Template::Array<Elysium::Core::Threading::Tasks::Task>(128);
	*/
	//Elysium::Core::Threading::Tasks::Task RingBuffer[128];
	//size_t CurrentJob = 0;
	//size_t LastStalledJob = static_cast<size_t>(-1);

	while (!_ShouldStop)
	{
		// fetch any new task to add to the local ringbuffer
		// ...

		// grab the next task
		// ...

		// execute the job
		// ...
	}
}
