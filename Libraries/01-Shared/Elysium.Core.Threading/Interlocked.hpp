/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_INTERLOCKED
#define ELYSIUM_CORE_THREADING_INTERLOCKED

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef _STDINT
#include <cstdint>
#endif

namespace Elysium::Core::Threading
{
	// Provides atomic operations for variables that are shared by multiple threads.
	class ELYSIUM_CORE_API Interlocked final
	{
	public:
		static int32_t Add(int32_t& Location, int32_t Value);
		static int64_t Add(int64_t& Location, int64_t Value);
		
		static int32_t Decrement(int32_t& Location);
		static int64_t Decrement(int64_t& Location);

		static int32_t Increment(int32_t& Location);
		static int64_t Increment(int64_t& Location);
	private:
		Interlocked();
		~Interlocked();
	};
	/*
	template <class T>
	class Interlocked final
	{
	public:
		static_assert(std::is_same<T, int32_t>::value || std::is_same<T, int64_t>::value,
			"some meaningful error message");
	private:
	};
	*/
	/*
#include <type_traits>

	template <typename RealType>
	class A
	{
		static_assert(std::is_same<RealType, double>::value || std::is_same<RealType, float>::value,
			"some meaningful error message");
	};

	template <typename RealType>
	class A
	{
		static_assert(std::is_floating_point<RealType>::value,
			"class A can only be instantiated with floating point types");
	};
	*/
}
#endif
