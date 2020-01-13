#include "Interlocked.hpp"

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

#include <assert.h>

int32_t Elysium::Core::Threading::Interlocked::Add(int32_t & Location, int32_t Value)
{
	assert(sizeof(long) == sizeof(int32_t));
	return ELYSIUM_INTERLOCKED_ADD(reinterpret_cast<long*>(&Location), Value);
}
int64_t Elysium::Core::Threading::Interlocked::Add(int64_t & Location, int64_t Value)
{
	assert(sizeof(__int64) == sizeof(int64_t));
	return ELYSIUM_INTERLOCKED_ADD64(&Location, Value);
}

int32_t Elysium::Core::Threading::Interlocked::Decrement(int32_t & Location)
{
	assert(sizeof(long) == sizeof(int32_t));
	return ELYSIUM_INTERLOCKED_DECREMENT(reinterpret_cast<long*>(&Location));
}
int64_t Elysium::Core::Threading::Interlocked::Decrement(int64_t & Location)
{
	assert(sizeof(__int64) == sizeof(int64_t));
	return ELYSIUM_INTERLOCKED_DECREMENT64(&Location);
}

int32_t Elysium::Core::Threading::Interlocked::Increment(int32_t & Location)
{
	assert(sizeof(long) == sizeof(int32_t));
	return ELYSIUM_INTERLOCKED_INCREMENT(reinterpret_cast<long*>(&Location));
}
int64_t Elysium::Core::Threading::Interlocked::Increment(int64_t & Location)
{
	assert(sizeof(__int64) == sizeof(int64_t));
	return ELYSIUM_INTERLOCKED_INCREMENT64(&Location);
}

Elysium::Core::Threading::Interlocked::Interlocked()
{
}
Elysium::Core::Threading::Interlocked::~Interlocked()
{
}
