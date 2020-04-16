/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_INTERLOCKEDINT32
#define ELYSIUM_CORE_THREADING_INTERLOCKEDINT32

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
	class ELYSIUM_CORE_API InterlockedInt32 final
	{
	public:
		InterlockedInt32();
		InterlockedInt32(const int32_t InitialValue);
		InterlockedInt32(const InterlockedInt32& Source);
		InterlockedInt32(InterlockedInt32&& Right) noexcept;
		~InterlockedInt32();

		InterlockedInt32& operator=(const InterlockedInt32& Source);
		InterlockedInt32& operator=(InterlockedInt32&& Right) noexcept;

		int32_t operator++();
		int32_t operator--();

		int32_t operator+=(const int32_t Value);
		int32_t operator-=(const int32_t Value);
	private:
		int32_t _Value;
	};
}
#endif
