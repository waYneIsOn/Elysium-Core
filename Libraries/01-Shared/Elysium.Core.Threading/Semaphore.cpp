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
{ }
Elysium::Core::Threading::Semaphore::~Semaphore()
{ }
