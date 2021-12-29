#include "Mutex.hpp"

Elysium::Core::Threading::Mutex::Mutex()
	: WaitHandle(ELYSIUM_MUTEX_CREATE(nullptr, false, nullptr))
{ }

Elysium::Core::Threading::Mutex::Mutex(const bool InitiallyOwned)
	: WaitHandle(ELYSIUM_MUTEX_CREATE(nullptr, InitiallyOwned, nullptr))
{ }

Elysium::Core::Threading::Mutex::Mutex(const bool InitiallyOwned, const Elysium::Core::Utf8String& Name)
	: WaitHandle(ELYSIUM_MUTEX_CREATE(nullptr, InitiallyOwned, nullptr)) // ToDo: last parameter (char8_t -> wchar_t)
{ }

Elysium::Core::Threading::Mutex::~Mutex()
{ }

void Elysium::Core::Threading::Mutex::Release()
{
	bool WasReleased = ELYSIUM_MUTEX_UNLOCK(_Handle);
}
