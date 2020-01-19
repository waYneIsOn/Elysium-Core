#include "Semaphore.hpp"
/*
#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "../Elysium.Core.Math/MathHelper.hpp"
#endif
*/
#ifndef ELYSIUM_CORE_THREADING_SEMAPHOREFULLEXCEPTION
#include "SemaphoreFullException.hpp"
#endif

#include <assert.h>

Elysium::Core::Threading::Semaphore::Semaphore(const uint32_t InitialCount, const uint32_t MaximumCount)
	: _Handle(ELYSIUM_SEMAPHORE_CREATE(nullptr, InitialCount, MaximumCount, nullptr))
{
	assert(_Handle != nullptr);
}
Elysium::Core::Threading::Semaphore::~Semaphore()
{ 
	bool WasDestroyed = ELYSIUM_SEMAPHORE_DESTROY(_Handle);
	assert(WasDestroyed == true);
}

const bool Elysium::Core::Threading::Semaphore::WaitOne()
{
	return ELYSIUM_SEMAPHORE_WAIT(_Handle, -1) == WAIT_OBJECT_0;
}
const Elysium::Core::int32_t Elysium::Core::Threading::Semaphore::Release()
{
	long PreviousCount;
	bool Result = ELYSIUM_SEMAPHORE_RELEASE(_Handle, 1, &PreviousCount);
	if (Result)
	{
		return static_cast<Elysium::Core::int32_t>(PreviousCount);
	}
	else
	{
		throw SemaphoreFullException();
	}
}
