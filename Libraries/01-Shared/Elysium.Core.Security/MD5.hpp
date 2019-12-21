/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM
#include "HashAlgorithm.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_API MD5 final : public HashAlgorithm
	{
	public:
		MD5();
		MD5(const MD5& Source) = delete;
		MD5(MD5&& Right) noexcept = delete;
		~MD5();

		MD5& operator=(const MD5& Source) = delete;
		MD5& operator=(MD5&& Right) noexcept = delete;

		virtual void Initialize() override;
	private:
		static const Elysium::Core::Collections::Template::Array<const uint32_t> _S;
		static const Elysium::Core::Collections::Template::Array<const uint32_t> _K;

		virtual void HashCore(Elysium::Core::byte* Array, const size_t Length) override;
		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> HashFinal() override;
	};
}
#endif
