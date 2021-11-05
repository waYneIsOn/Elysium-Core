#include "ManualResetEvent.hpp"

Elysium::Core::Threading::ManualResetEvent::ManualResetEvent(const bool InitialState)
	: EventWaitHandle(false, InitialState, nullptr)
{ }

Elysium::Core::Threading::ManualResetEvent::~ManualResetEvent()
{ }
