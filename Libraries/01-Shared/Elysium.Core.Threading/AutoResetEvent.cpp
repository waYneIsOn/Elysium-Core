#include "AutoResetEvent.hpp"

Elysium::Core::Threading::AutoResetEvent::AutoResetEvent(const bool InitialState)
	: EventWaitHandle(true, InitialState, L"")
{ }
Elysium::Core::Threading::AutoResetEvent::~AutoResetEvent()
{ }
