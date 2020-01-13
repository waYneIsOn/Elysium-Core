#include "Mutex.hpp"

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

Elysium::Core::Threading::Mutex::Mutex()
	: _Target(0)
{ }
Elysium::Core::Threading::Mutex::~Mutex()
{ 
	Unlock();
}

void Elysium::Core::Threading::Mutex::Lock()
{
	while (_Target == 1 || ELYSIUM_INTERLOCKED_COMPARE_EXCHANGE(&_Target, 1, 0) == 1)
	{ /* spin-lock */ }
}
void Elysium::Core::Threading::Mutex::Unlock()
{
	_Target = 0;
}
