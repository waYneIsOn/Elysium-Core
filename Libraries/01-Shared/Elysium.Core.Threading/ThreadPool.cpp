#include "ThreadPool.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "Task.hpp"
#endif

Elysium::Core::Threading::ThreadPool::ThreadPool()
	: _Ids(Elysium::Core::Collections::Template::Array<unsigned long>(Environment::ProcessorCount() - 1)),
	_ThreadHandles(Elysium::Core::Collections::Template::Array<ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE>(Environment::ProcessorCount() - 1)),
	_ShouldStop(false), _IsRunning(false)
{ }
Elysium::Core::Threading::ThreadPool::ThreadPool(const size_t NumberOfThreads)
	: _Ids(Elysium::Core::Collections::Template::Array<unsigned long>(NumberOfThreads)),
	_ThreadHandles(Elysium::Core::Collections::Template::Array<ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE>(NumberOfThreads)),
	_ShouldStop(false), _IsRunning(false)
{ }
Elysium::Core::Threading::ThreadPool::~ThreadPool()
{ 
	Stop();
}

const size_t Elysium::Core::Threading::ThreadPool::GetNumberOfThreads() const
{
	return _ThreadHandles.GetLength();
}

void Elysium::Core::Threading::ThreadPool::Start()
{
	if (_IsRunning)
	{
		return;
	}
	_ShouldStop = false;
	for (size_t i = 0; i < _ThreadHandles.GetLength(); i++)
	{
		_ThreadHandles[i] = ELYSIUM_THREAD_CREATE(nullptr, 0, (LPTHREAD_START_ROUTINE)ThreadMain, this, 0, &_Ids[i]);
	}
	_IsRunning = true;
}
void Elysium::Core::Threading::ThreadPool::Stop()
{
	if (_ShouldStop)
	{
		return;
	}
	_ShouldStop = true;
	ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_MULTIPLE_OBJECTS_EX(_ThreadHandles.GetLength(), &_ThreadHandles[0], true, INFINITE, false);
	_IsRunning = false;
}

void Elysium::Core::Threading::ThreadPool::ThreadMain(ThreadPool & ThreadPool)
{
	/*
	Elysium::Core::Collections::Template::Array<Elysium::Core::Threading::Tasks::Task> RingBuffer = 
		Elysium::Core::Collections::Template::Array<Elysium::Core::Threading::Tasks::Task>(128);
	*/
	//Elysium::Core::Threading::Tasks::Task RingBuffer[128];
	//size_t CurrentJob = 0;
	//int32_t LastStalledJob = -1;

	while (!ThreadPool._ShouldStop)
	{
		// fetch any new task to add to the local ringbuffer
		// ...

		// grab the next task
		// ...

		// execute the job
		// ...
	}
}
