#include "Task.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_THREADING_INTERLOCKED
#include "Interlocked.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_OPERATIONCANCELEDEXCEPTION
#include "OperationCanceledException.hpp"
#endif

int32_t Elysium::Core::Threading::Tasks::Task::_TaskIdCounter = 0;

Elysium::Core::Threading::Tasks::Task::Task(const Delegate<void> Action)
	: _Id(Interlocked::Increment(_TaskIdCounter)), _Action(Action), _CreationOptions(TaskCreationOptions::None), _Status(TaskStatus::Created), _Exception(nullptr)
{ }
Elysium::Core::Threading::Tasks::Task::~Task()
{
	if (_Exception != nullptr)
	{
		delete _Exception;
		_Exception = nullptr;
	}
}

const int32_t Elysium::Core::Threading::Tasks::Task::GetId() const
{
	return _Id;
}
const Elysium::Core::Threading::Tasks::TaskCreationOptions Elysium::Core::Threading::Tasks::Task::GetCreationOptions() const
{
	return _CreationOptions;
}
const Elysium::Core::Threading::Tasks::TaskStatus Elysium::Core::Threading::Tasks::Task::GetStatus() const
{
	return _Status;
}
const Elysium::Core::AggregateException * Elysium::Core::Threading::Tasks::Task::GetException() const
{
	return _Exception;
}

const bool Elysium::Core::Threading::Tasks::Task::GetIsCanceled() const
{
	return _Status == TaskStatus::Canceled;
}
const bool Elysium::Core::Threading::Tasks::Task::GetIsCompleted() const
{
	return _Status == TaskStatus::RanToCompletion || _Status == TaskStatus::Faulted || _Status == TaskStatus::Canceled;
}
const bool Elysium::Core::Threading::Tasks::Task::GetIsCompletedSuccessfully() const
{
	return _Status == TaskStatus::RanToCompletion;
}
const bool Elysium::Core::Threading::Tasks::Task::GetIsFaulted() const
{
	return _Status == TaskStatus::Faulted;
}

void Elysium::Core::Threading::Tasks::Task::RunSynchronously()
{
	_Status = TaskStatus::WaitingToRun;
	try
	{
		_Status = TaskStatus::Running;
		_Action();
		_Status = TaskStatus::RanToCompletion;
	}
	catch (OperationCanceledException& Ex)
	{
		_Status = TaskStatus::Canceled;
	}
	catch (Exception& Ex)
	{
		// ToDo: store exception
		_Status = TaskStatus::Faulted;
	}

	// ToDo: wait signal
}
void Elysium::Core::Threading::Tasks::Task::Start(ThreadPool & ThreadPool)
{
	ThreadPool._WorkQueue.Submit(*this);
}
void Elysium::Core::Threading::Tasks::Task::Wait()
{
	// ToDo: wait signal
	if (_Status == TaskStatus::Canceled)
	{
		//throw OperationCanceledException();
	}
}
