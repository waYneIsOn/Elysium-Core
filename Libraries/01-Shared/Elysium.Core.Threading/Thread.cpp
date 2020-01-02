#include "Thread.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Threading::Thread::Thread()
	: _Name(), _State(ThreadState::Unstarted)
{ }
Elysium::Core::Threading::Thread::Thread(const String& Name)
	: _Name(Name), _State(ThreadState::Unstarted)
{ }
Elysium::Core::Threading::Thread::Thread(Thread && Right) noexcept
{
	*this = std::move(Right);
}
Elysium::Core::Threading::Thread::~Thread()
{
	Join();
}

Elysium::Core::Threading::Thread & Elysium::Core::Threading::Thread::operator=(Thread && Right) noexcept
{
	if (this != &Right)
	{
		//_ThreadStart = std::move(Right._ThreadStart);
		_NativeThread = std::move(Right._NativeThread);

		//Right._ThreadStart = nullptr;
		_NativeThread = std::thread();
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

const Elysium::Core::Globalization::CultureInfo & Elysium::Core::Threading::Thread::GetCurrentCulture() const
{
	return _CurrentCulture;
}
const int Elysium::Core::Threading::Thread::GetThreadId() const
{
	std::thread::id NativeId = _NativeThread.get_id();
	//unsigned int Bla = NativeId._Id;
	throw NotImplementedException();
}

const int Elysium::Core::Threading::Thread::GetCurrentThreadId()
{
	std::thread::id NativeId = std::this_thread::get_id();
	throw NotImplementedException();
}

void Elysium::Core::Threading::Thread::Start(const Delegate<void>& ThreadStart)
{
	if ((_State | ThreadState::Running) == ThreadState::Running)
	{
		return;
	}
	_NativeThread = std::thread(ThreadStart);
	_State = ThreadState::Running;
}

void Elysium::Core::Threading::Thread::Join()
{
	_State = ThreadState::StopRequested;
	if (_NativeThread.joinable())
	{
		_NativeThread.join();
	}
	_State = ThreadState::Stopped;
}

void Elysium::Core::Threading::Thread::Sleep(const TimeSpan & Timeout)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(Timeout.GetTicks() * 100));
}
