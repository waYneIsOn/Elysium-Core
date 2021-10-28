/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Checksum
{
	class ELYSIUM_CORE_SECURITY_API Adler32 final
	{
	public:
		Adler32() = delete;
		Adler32(const Adler32& Source) = delete;
		Adler32(Adler32&& Right) noexcept = delete;
		~Adler32() = delete;

		Adler32& operator=(const Adler32& Other) = delete;
		Adler32& operator=(Adler32&& Right) noexcept = delete;

		static const Elysium::Core::uint32_t CalculateBytewise(const Elysium::Core::byte* Data, const Elysium::Core::size Length);
	private:
		static const Elysium::Core::uint32_t _Modulo = 65521;
	};
}
#endif
