/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_INTERLOCKEDINT64
#define ELYSIUM_CORE_THREADING_INTERLOCKEDINT64

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API InterlockedInt64 final
	{
	public:
		InterlockedInt64();
		InterlockedInt64(const int64_t InitialValue);
		InterlockedInt64(const InterlockedInt64& Source);
		InterlockedInt64(InterlockedInt64&& Right) noexcept;
		~InterlockedInt64();

		InterlockedInt64& operator=(const InterlockedInt64& Source);
		InterlockedInt64& operator=(InterlockedInt64&& Right) noexcept;

		int64_t operator++();
		int64_t operator--();

		int64_t operator+=(const int64_t Value);
		int64_t operator-=(const int64_t Value);
	private:
		int64_t _Value;
	};
}
#endif
