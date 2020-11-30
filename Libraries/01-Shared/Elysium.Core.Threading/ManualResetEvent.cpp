#include "ManualResetEvent.hpp"

Elysium::Core::Threading::ManualResetEvent::ManualResetEvent(const bool InitialState)
	: EventWaitHandle(false, InitialState, u8"")
{ }
Elysium::Core::Threading::ManualResetEvent::~ManualResetEvent()
{ }
