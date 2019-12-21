/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#pragma warning( disable : 4251 )

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_API HashAlgorithm
	{
	public:
		HashAlgorithm(const HashAlgorithm& Source) = delete;
		HashAlgorithm(HashAlgorithm&& Right) noexcept = delete;
		~HashAlgorithm();

		HashAlgorithm& operator=(const HashAlgorithm& Source) = delete;
		HashAlgorithm& operator=(HashAlgorithm&& Right) noexcept = delete;

		virtual const size_t GetHashSize() const;
		virtual const bool GetCanReuseTransform() const;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> ComputeHash(Elysium::Core::IO::Stream& InputStream);
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> ComputeHash(Elysium::Core::byte* Buffer, const size_t Length);

		virtual void Initialize() = 0;
	protected:
		HashAlgorithm(int32_t HashSizeValue);

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _HashValue;
		int32_t _State;

		virtual void HashCore(Elysium::Core::byte* Array, const size_t Length) = 0;
		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> HashFinal() = 0;
	};
}
#endif
