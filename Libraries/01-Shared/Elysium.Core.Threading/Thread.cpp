#include "Thread.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::Threading::Thread::Thread()
{
}
Elysium::Core::Threading::Thread::Thread(Thread && Right) noexcept
{
	*this = std::move(Right);
}
Elysium::Core::Threading::Thread::~Thread()
{
	if (_NativeThread.joinable())
	{
		// ToDo: request the thread to stop somehow
		_NativeThread.join();
	}
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
	_NativeThread = std::thread(ThreadStart);
}

void Elysium::Core::Threading::Thread::Join()
{
	_NativeThread.join();
}

void Elysium::Core::Threading::Thread::Sleep(TimeSpan & Timeout)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(Timeout.GetTicks() * 100));
}
