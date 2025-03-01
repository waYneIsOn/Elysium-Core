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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Threading::Thread::Thread()
	: _Id(0), _Handle(nullptr), _Name(), _State(ThreadState::Unstarted), _CurrentCulture(Globalization::CultureInfo::GetInvariantCulture()),
	_Parameters()
{ }

Elysium::Core::Threading::Thread::Thread(const Elysium::Core::Template::Container::Delegate<void>& ThreadStart)
	: _Id(0), _Handle(nullptr), _Name(), _State(ThreadState::Unstarted), _CurrentCulture(Globalization::CultureInfo::GetInvariantCulture()),
	_Parameters(ThreadStart)
{ }

Elysium::Core::Threading::Thread::Thread(const Elysium::Core::Template::Container::Delegate<void, void*>& ParameterizedThreadStart)
	: _Id(0), _Handle(INVALID_HANDLE_VALUE), _Name(), _State(ThreadState::Unstarted), _CurrentCulture(Globalization::CultureInfo::GetInvariantCulture()),
	_Parameters(ParameterizedThreadStart)
{ }

Elysium::Core::Threading::Thread::Thread(Thread&& Right) noexcept
	: _Id(0), _Handle(INVALID_HANDLE_VALUE), _Name(), _State(ThreadState::Unstarted), _CurrentCulture(Globalization::CultureInfo::GetInvariantCulture()),
	_Parameters()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Threading::Thread::~Thread()
{
	Join();
	bool WasDestroyed = ELYSIUM_SYNCHRONIZATION_PRIMITIVE_DESTROY(_Handle);
}

Elysium::Core::Threading::Thread& Elysium::Core::Threading::Thread::operator=(Thread&& Right) noexcept
{
	if (this != &Right)
	{
		_Id = Elysium::Core::Template::Functional::Move(Right._Id);
		_Handle = Elysium::Core::Template::Functional::Move(Right._Handle);
		_Name = Elysium::Core::Template::Functional::Move(Right._Name);
		_State = Right._State.Load();
		_CurrentCulture = Elysium::Core::Template::Functional::Move(Right._CurrentCulture);
		_Parameters = Elysium::Core::Template::Functional::Move(Right._Parameters);

		Right._Id = 0;
		Right._Handle = INVALID_HANDLE_VALUE;
		Right._State = ThreadState::Unstarted;
		Right._CurrentCulture = Globalization::CultureInfo::GetInvariantCulture();
	}
	return *this;
}

bool Elysium::Core::Threading::Thread::operator==(const Thread & Other) const
{
	return &Other == this;
}

bool Elysium::Core::Threading::Thread::operator!=(const Thread & Other) const
{
	return &Other != this;
}

const Elysium::Core::uint32_t Elysium::Core::Threading::Thread::GetCurrentThreadIdX()
{
	return ELYSIUM_THREAD_GETCURRENTTHREADID();
}

const Elysium::Core::Globalization::CultureInfo & Elysium::Core::Threading::Thread::GetCurrentCulture() const
{
	// SetThreadUILanguage
	return _CurrentCulture;
}

const Elysium::Core::uint32_t Elysium::Core::Threading::Thread::GetThreadId() const
{
	return _Id;
}

void Elysium::Core::Threading::Thread::Sleep(const TimeSpan& Timeout)
{
	ELYSIUM_THREAD_SLEEP(static_cast<unsigned long>(Timeout.GetTicks() / DateTimeUtility::TicksPerMillisecond), false);
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
	if (_Handle == INVALID_HANDLE_VALUE)
	{
		return;
	}

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

Elysium::Core::Threading::Thread::ThreadParameters::ThreadParameters()
	: _Target(nullptr), _Method(nullptr), _FurtherParameter(nullptr), _ParamaterizedMethod(nullptr)
{ }

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
