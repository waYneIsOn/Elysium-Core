/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFINTEGER
#include "../Elysium.Core/VectorOfInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM
#include "HashAlgorithm.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API MD5 final : public HashAlgorithm
	{
	public:
		MD5();

		MD5(const MD5& Source) = delete;

		MD5(MD5&& Right) noexcept = delete;

		virtual ~MD5();
	public:
		MD5& operator=(const MD5& Source) = delete;

		MD5& operator=(MD5&& Right) noexcept = delete;
	public:
		virtual void Initialize() override;
	private:
		static const Elysium::Core::Container::VectorOfUInt32_t _S;
		static const Elysium::Core::Container::VectorOfUInt32_t _K;

		virtual void HashCore(Elysium::Core::byte* Array, const Elysium::Core::size Length) override;

		virtual const Elysium::Core::Container::VectorOfByte HashFinal() override;
	};
}
#endif
