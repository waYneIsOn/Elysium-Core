#include "Semaphore.hpp"
/*
#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "../Elysium.Core.Math/MathHelper.hpp"
#endif
*/
#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

Elysium::Core::Threading::Semaphore::Semaphore(const uint32_t InitialCount, const uint32_t MaximumCount)
	: _MaximumCount(MaximumCount), _Count(InitialCount)
	//: _MaximumCount(Elysium::Core::Math::MathHelper::Min(1, MaximumCount)), _Count(Elysium::Core::Math::MathHelper::Max(_MaximumCount, InitialCount))
{ 
	//ELYSIUM_SEMAPHORE_CREATE()
}
Elysium::Core::Threading::Semaphore::~Semaphore()
{ }

void Elysium::Core::Threading::Semaphore::Increment()
{
	//ELYSIUM_INTERLOCKED_INCREMENT(reinterpret_cast<long*>(&_Count));
}
void Elysium::Core::Threading::Semaphore::Decrement()
{
	//ELYSIUM_INTERLOCKED_DECREMENT(reinterpret_cast<long*>(&_Count));
}
const bool Elysium::Core::Threading::Semaphore::WaitOne()
{
	return false;
}
