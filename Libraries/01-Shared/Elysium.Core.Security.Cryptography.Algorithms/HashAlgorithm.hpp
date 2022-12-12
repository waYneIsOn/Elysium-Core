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

#ifndef ELYSIUM_CORE_CONTAINER_ARRAYOFBYTE
#include "../Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API HashAlgorithm
	{
	protected:
		HashAlgorithm(int32_t HashSizeValue);
	public:
		HashAlgorithm(const HashAlgorithm& Source) = delete;

		HashAlgorithm(HashAlgorithm&& Right) noexcept = delete;

		virtual ~HashAlgorithm();
	public:
		HashAlgorithm& operator=(const HashAlgorithm& Source) = delete;

		HashAlgorithm& operator=(HashAlgorithm&& Right) noexcept = delete;
	public:
		virtual const Elysium::Core::size GetHashSize() const;

		virtual const bool GetCanReuseTransform() const;

		Container::ArrayOfByte ComputeHash(Elysium::Core::IO::Stream& InputStream);

		Container::ArrayOfByte ComputeHash(Elysium::Core::byte* Buffer, const Elysium::Core::size Length);

		virtual void Initialize() = 0;
	protected:
		virtual void HashCore(Elysium::Core::byte* Array, const Elysium::Core::size Length) = 0;

		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> HashFinal() = 0;
	protected:
		Container::ArrayOfByte _HashValue;
		int32_t _State;
	};
}
#endif
