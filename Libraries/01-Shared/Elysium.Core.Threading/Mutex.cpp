#include "Mutex.hpp"

Elysium::Core::Threading::Mutex::Mutex()
{ 
	ELYSIUM_MUTEX_CREATE(&_Handle);
}
Elysium::Core::Threading::Mutex::~Mutex()
{
	// ToDo: do I need to ReleaseMutex() before destroying?
	ELYSIUM_MUTEX_DESTROY(&_Handle);
}

const bool Elysium::Core::Threading::Mutex::WaitOne(bool Blocking)
{
	if (ELYSIUM_MUTEX_TRYLOCK(&_Handle) == 0)
	{
		if (!Blocking)
		{
			return false;
		}
		ELYSIUM_MUTEX_LOCK(&_Handle);
	}
	return true;
}
void Elysium::Core::Threading::Mutex::ReleaseMutex()
{
	ELYSIUM_MUTEX_UNLOCK(&_Handle);
}
