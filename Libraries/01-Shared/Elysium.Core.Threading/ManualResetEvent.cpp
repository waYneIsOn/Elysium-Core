#include "ManualResetEvent.hpp"

Elysium::Core::Threading::ManualResetEvent::ManualResetEvent(const bool InitialState)
	: EventWaitHandle(false, InitialState, L"")
{ }
Elysium::Core::Threading::ManualResetEvent::~ManualResetEvent()
{ }
