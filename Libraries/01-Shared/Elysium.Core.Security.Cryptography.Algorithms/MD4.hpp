/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD4
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD4

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM
#include "../Elysium.Core.Security.Cryptography.Primitives/HashAlgorithm.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API MD4 final : public HashAlgorithm
	{
	public:
		MD4();
		MD4(const MD4& Source) = delete;
		MD4(MD4&& Right) noexcept = delete;
		~MD4();

		MD4& operator=(const MD4& Source) = delete;
		MD4& operator=(MD4&& Right) noexcept = delete;

		virtual void Initialize() override;
	private:
		virtual void HashCore(Elysium::Core::byte* Array, const Elysium::Core::size Length) override;
		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> HashFinal() override;
	};
}
#endif

