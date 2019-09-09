#include "Thread.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::Threading::Thread::Thread(void(*Start)())
	: _ThreadStart(Start)
{
}
Elysium::Core::Threading::Thread::~Thread()
{
	if (_NativeThread.joinable())
	{
		// ToDo: request the thread to stop somehow
		_NativeThread.join();
	}
}

void Elysium::Core::Threading::Thread::GetCurrentCulture(CultureInfo * Value) const
{
	*Value = _CurrentCulture;
}
void Elysium::Core::Threading::Thread::GetThreadId(unsigned int * Value) const
{
	std::thread::id NativeId = _NativeThread.get_id();
	throw NotImplementedException();
}

void Elysium::Core::Threading::Thread::GetCurrentThreadId(unsigned int * Value)
{
	std::thread::id NativeId = std::this_thread::get_id();
	throw NotImplementedException();
}

void Elysium::Core::Threading::Thread::Join()
{
	_NativeThread.join();
}
void Elysium::Core::Threading::Thread::Start()
{
	_NativeThread = std::thread(_ThreadStart);
}

void Elysium::Core::Threading::Thread::Sleep(TimeSpan & Timeout)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(Timeout.GetTicks() * 100));
}
