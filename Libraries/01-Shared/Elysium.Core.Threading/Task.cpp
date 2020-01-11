#include "Task.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_OPERATIONCANCELEDEXCEPTION
#include "OperationCanceledException.hpp"
#endif

Elysium::Core::Threading::Tasks::Task::Task(Delegate<void> Action)
	: _Status(TaskStatus::Created), _Action(Action), _CreationOptions(TaskCreationOptions::None), _Exception(nullptr)
{ }
Elysium::Core::Threading::Tasks::Task::Task(const Task & Source)
	: _Status(TaskStatus::Created), _Action(Source._Action), _CreationOptions(TaskCreationOptions::None), _Exception(nullptr)
{ }
Elysium::Core::Threading::Tasks::Task::Task(Task && Right) noexcept
	: _Status(TaskStatus::Created), _Action(Delegate<void>::CreateDelegate<[]() -> void { }>()), _CreationOptions(TaskCreationOptions::None), _Exception(nullptr)
{
	*this = std::move(Right);
}
Elysium::Core::Threading::Tasks::Task::~Task()
{
	if (_Exception != nullptr)
	{
		delete _Exception;
		_Exception = nullptr;
	}
}

Elysium::Core::Threading::Tasks::Task & Elysium::Core::Threading::Tasks::Task::operator=(const Task & Source)
{
	if (this != &Source)
	{
		_Action = Source._Action;
		_Status = Source._Status;
		_CreationOptions = Source._CreationOptions;
		_Exception = Source._Exception;
	}
	return *this;
}
Elysium::Core::Threading::Tasks::Task & Elysium::Core::Threading::Tasks::Task::operator=(Task && Right) noexcept
{
	if (this != &Right)
	{
		_Action = std::move(Right._Action);
		_Status = std::move(Right._Status);
		_CreationOptions = std::move(Right._CreationOptions);
		_Exception = std::move(Right._Exception);

		Right._Action = Delegate<void>::CreateDelegate<[]() -> void {}>();
		Right._Status = TaskStatus::Created;
		Right._CreationOptions = TaskCreationOptions::None;
		Right._Exception = nullptr;
	}
	return *this;
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
	try
	{
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
void Elysium::Core::Threading::Tasks::Task::Start(const ThreadPool & ThreadPool)
{
	
}
void Elysium::Core::Threading::Tasks::Task::Wait()
{
	// ToDo: wait signal
	if (_Status == TaskStatus::Canceled)
	{
		//throw OperationCanceledException();
	}
}
