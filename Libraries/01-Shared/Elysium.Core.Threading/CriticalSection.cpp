#include "CriticalSection.hpp"

Elysium::Core::Threading::CriticalSection::CriticalSection()
	: _Handle(ELYSIUM_CRITICAL_SECTION_HANDLE())
{
	ELYSIUM_CRITICAL_SECTION_CREATE(&_Handle);
}

Elysium::Core::Threading::CriticalSection::~CriticalSection()
{
	ELYSIUM_CRITICAL_SECTION_DESTROY(&_Handle);
}

const bool Elysium::Core::Threading::CriticalSection::Enter(const bool Blocking)
{
	if (ELYSIUM_CRITICAL_SECTION_TRYENTER(&_Handle) == 0)
	{
		if (!Blocking)
		{
			return false;
		}
		ELYSIUM_CRITICAL_SECTION_ENTER(&_Handle);
	}
	return true;
}

void Elysium::Core::Threading::CriticalSection::Exit()
{
	ELYSIUM_CRITICAL_SECTION_LEAVE(&_Handle);
}
