#include "ThreadPoolWorkQueue.hpp"

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "Task.hpp"
#endif

Elysium::Core::Threading::ThreadPoolWorkQueue::ThreadPoolWorkQueue()
	: _WorkAvailable(false)
{ }
Elysium::Core::Threading::ThreadPoolWorkQueue::~ThreadPoolWorkQueue()
{ }

void Elysium::Core::Threading::ThreadPoolWorkQueue::Submit(Elysium::Core::Threading::Tasks::Task & Task)
{
	_CriticalSection.Enter();
	_Queue.Enqueue(&Task);
	_WorkAvailable.Set();
	_CriticalSection.Exit();
}
Elysium::Core::Threading::Tasks::Task * Elysium::Core::Threading::ThreadPoolWorkQueue::GetNextTask()
{
	_CriticalSection.Enter();
	Tasks::Task* NextTask = nullptr;
	try
	{
		NextTask = _Queue.Dequeue();
	}
	catch(InvalidOperationException& Ex)
	{ 
		// ...
	}
	_CriticalSection.Exit();

	return NextTask;
}
