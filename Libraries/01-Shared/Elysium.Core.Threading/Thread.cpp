#include "Thread.hpp"

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "../Elysium.Core/DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Threading::Thread::Thread(const Elysium::Core::Template::Container::Delegate<void>& ThreadStart)
	: _Id(0), _Handle(nullptr), _Name(), _State(ThreadState::Unstarted), _CurrentCulture(Globalization::CultureInfo::GetInvariantCulture()),
	_Parameters(ThreadParameters(ThreadStart))
{ }
Elysium::Core::Threading::Thread::Thread(const Elysium::Core::Template::Container::Delegate<void, void*>& ParameterizedThreadStart)
	: _Id(0), _Handle(nullptr), _Name(), _State(ThreadState::Unstarted), _CurrentCulture(Globalization::CultureInfo::GetInvariantCulture()),
	_Parameters(ThreadParameters(ParameterizedThreadStart))
{ }
Elysium::Core::Threading::Thread::~Thread()
{
	Join();
	bool WasDestroyed = ELYSIUM_SYNCHRONIZATION_PRIMITIVE_DESTROY(_Handle);
}

bool Elysium::Core::Threading::Thread::operator==(const Thread & Other) const
{
	return &Other == this;
}
bool Elysium::Core::Threading::Thread::operator!=(const Thread & Other) const
{
	return &Other != this;
}

const Elysium::Core::Globalization::CultureInfo & Elysium::Core::Threading::Thread::GetCurrentCulture() const
{
	// SetThreadUILanguage
	return _CurrentCulture;
}
const int Elysium::Core::Threading::Thread::GetThreadId() const
{
	return _Id;
}

const int Elysium::Core::Threading::Thread::GetCurrentThreadIdX()
{
	return ELYSIUM_THREAD_GETCURRENTTHREADID();
}

void Elysium::Core::Threading::Thread::Start()
{
	if ((_State | ThreadState::Running) == ThreadState::Running)
	{
		return;
	}
	_State = ThreadState::Running;
	_Handle = ELYSIUM_THREAD_CREATE(nullptr, 0, (LPTHREAD_START_ROUTINE)ThreadMain, &_Parameters, 0, &_Id);
}
void Elysium::Core::Threading::Thread::Start(void * Parameter)
{
	if ((_State | ThreadState::Running) == ThreadState::Running)
	{
		return;
	}
	_State = ThreadState::Running;
	_Parameters._FurtherParameter = Parameter;
	_Handle = ELYSIUM_THREAD_CREATE(nullptr, 0, (LPTHREAD_START_ROUTINE)ThreadMain, &_Parameters, 0, &_Id);
}

void Elysium::Core::Threading::Thread::Join()
{
	/*
	if ((_State & ThreadState::Stopped) == ThreadState::Stopped)
	{
		return;
	}
	*/
	_State = ThreadState::WaitSleepJoin;
	bool SignalReceived = ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_SINGLE_OBJECT(_Handle, INFINITE) == WAIT_OBJECT_0;
	_State = ThreadState::Stopped;
}

void Elysium::Core::Threading::Thread::Sleep(const TimeSpan & Timeout)
{
	ELYSIUM_THREAD_SLEEP(static_cast<unsigned long>(Timeout.GetTicks() / DateTimeUtility::TicksPerMillisecond), false);
}

Elysium::Core::Threading::Thread::ThreadParameters::ThreadParameters(const Elysium::Core::Template::Container::Delegate<void>& ThreadStart)
	: _Target(ThreadStart._Target), _Method(ThreadStart._Method), _FurtherParameter(nullptr), _ParamaterizedMethod(nullptr)
{ }
Elysium::Core::Threading::Thread::ThreadParameters::ThreadParameters(const Elysium::Core::Template::Container::Delegate<void, void*>& ParameterizedThreadStart)
	: _Target(ParameterizedThreadStart._Target), _Method(nullptr), _FurtherParameter(nullptr), _ParamaterizedMethod(ParameterizedThreadStart._Method)
{ }
Elysium::Core::Threading::Thread::ThreadParameters::~ThreadParameters()
{ }

void Elysium::Core::Threading::Thread::ThreadMain(ThreadParameters& Parameters)
{
	if (Parameters._Method == nullptr)
	{
		Parameters._ParamaterizedMethod(Parameters._Target, Parameters._FurtherParameter);
	}
	else
	{
		Parameters._Method(Parameters._Target);
	}
}
