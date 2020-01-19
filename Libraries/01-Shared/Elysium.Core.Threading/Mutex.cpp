#include "Mutex.hpp"

#include <mutex>

Elysium::Core::Threading::Mutex::Mutex()
	: WaitHandle(ELYSIUM_MUTEX_CREATE(nullptr, false, nullptr))
{ }
Elysium::Core::Threading::Mutex::~Mutex()
{ }

void Elysium::Core::Threading::Mutex::ReleaseMutexX()
{
	ELYSIUM_MUTEX_UNLOCK(_Handle);
}
