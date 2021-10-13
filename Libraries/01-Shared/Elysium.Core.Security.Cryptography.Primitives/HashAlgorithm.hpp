/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#pragma warning( disable : 4251 )

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API HashAlgorithm
	{
	public:
		HashAlgorithm(const HashAlgorithm& Source) = delete;
		HashAlgorithm(HashAlgorithm&& Right) noexcept = delete;
		~HashAlgorithm();

		HashAlgorithm& operator=(const HashAlgorithm& Source) = delete;
		HashAlgorithm& operator=(HashAlgorithm&& Right) noexcept = delete;

		virtual const Elysium::Core::size GetHashSize() const;
		virtual const bool GetCanReuseTransform() const;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> ComputeHash(Elysium::Core::IO::Stream& InputStream);
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> ComputeHash(Elysium::Core::byte* Buffer, const Elysium::Core::size Length);

		virtual void Initialize() = 0;
	protected:
		HashAlgorithm(int32_t HashSizeValue);

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _HashValue;
		int32_t _State;

		virtual void HashCore(Elysium::Core::byte* Array, const Elysium::Core::size Length) = 0;
		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> HashFinal() = 0;
	};
}
#endif
