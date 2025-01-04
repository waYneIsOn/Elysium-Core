/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_BITCONVERTER
#define ELYSIUM_CORE_BITCONVERTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif


namespace Elysium::Core
{
	class ELYSIUM_CORE_API BitConverter 
	{
	public:
		BitConverter() = delete;

		BitConverter(const BitConverter& Source) = delete;

		BitConverter(BitConverter&& Right) noexcept = delete;

		~BitConverter() = delete;
	public:
		BitConverter& operator=(const BitConverter& Source) = delete;

		BitConverter& operator=(BitConverter&& Right) noexcept = delete;
	public:
		static const bool GetIsLittleEndian();
	public:
		static const Elysium::Core::Container::VectorOfByte GetBytes(const Elysium::Core::int16_t Value);

		static const Elysium::Core::Container::VectorOfByte GetBytes(const Elysium::Core::int32_t Value);

		static const Elysium::Core::Container::VectorOfByte GetBytes(const Elysium::Core::int64_t Value);

		static const Elysium::Core::Container::VectorOfByte GetBytes(const Elysium::Core::uint16_t Value);

		static const Elysium::Core::Container::VectorOfByte GetBytes(const Elysium::Core::uint32_t Value);

		static const Elysium::Core::Container::VectorOfByte GetBytes(const Elysium::Core::uint64_t Value);
	public:
		static const Elysium::Core::int16_t ToInt16(const Elysium::Core::byte* Value);

		static const Elysium::Core::int32_t ToInt24(const Elysium::Core::byte* Value);	// ToDo: return custom uint24_t-type?

		static const Elysium::Core::int32_t ToInt32(const Elysium::Core::byte* Value);

		static const Elysium::Core::int64_t ToInt64(const Elysium::Core::byte* Value);

		static const Elysium::Core::uint16_t ToUInt16(const Elysium::Core::byte* Value);

		static const Elysium::Core::uint32_t ToUInt24(const Elysium::Core::byte* Value);	// ToDo: return custom uint24_t-type?

		static const Elysium::Core::uint32_t ToUInt32(const Elysium::Core::byte* Value);

		static const Elysium::Core::uint64_t ToUInt64(const Elysium::Core::byte* Value);
	};
}
#endif
