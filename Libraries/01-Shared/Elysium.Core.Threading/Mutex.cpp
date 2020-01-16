#include "Mutex.hpp"

Elysium::Core::Threading::Mutex::Mutex()
{ 
	ELYSIUM_MUTEX_CREATE(&_Handle);
}
Elysium::Core::Threading::Mutex::~Mutex()
{
	// ToDo: do we need to unlock before destroying?
	ELYSIUM_MUTEX_DESTROY(&_Handle);
}

bool Elysium::Core::Threading::Mutex::Lock(bool Blocking)
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
void Elysium::Core::Threading::Mutex::Unlock()
{
	ELYSIUM_MUTEX_UNLOCK(&_Handle);
}
const bool Elysium::Core::Threading::Mutex::Wait()
{
	return ELYSIUM_MUTEX_WAIT(&_Handle, 50000) == WAIT_OBJECT_0;
}
