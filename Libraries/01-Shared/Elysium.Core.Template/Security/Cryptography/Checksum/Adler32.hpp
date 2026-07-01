/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Checksum
{
	class Adler32 final
	{
	public:
		Adler32() = delete;

		Adler32(const Adler32& Source) = delete;

		Adler32(Adler32&& Right) noexcept = delete;

		~Adler32() = delete;
	public:
		Adler32& operator=(const Adler32& Other) = delete;

		Adler32& operator=(Adler32&& Right) noexcept = delete;
	public:
		inline static const Elysium::Core::Template::System::uint32_t CalculateBytewise(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length) noexcept
		{
			if (nullptr == Data || 0 == Length)
			{
				return 0;
			}

			Elysium::Core::Template::System::uint32_t A = 1;
			Elysium::Core::Template::System::uint32_t B = 0;

			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				A = (A + Data[i]) % _Modulo;
				B = (B + A) % _Modulo;
			}

			return (B << 16) | A;
		}
	private:
		static const Elysium::Core::Template::System::uint32_t _Modulo = 65521;
	};
}
#endif
