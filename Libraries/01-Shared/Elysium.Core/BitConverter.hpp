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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API BitConverter 
	{
	public:
		~BitConverter();

		static const bool GetIsLittleEndian();

		static const Collections::Template::Array<Elysium::Core::byte> GetBytes(const int16_t Value);
		static const Collections::Template::Array<Elysium::Core::byte> GetBytes(const int32_t Value);
		static const Collections::Template::Array<Elysium::Core::byte> GetBytes(const int64_t Value);
		static const Collections::Template::Array<Elysium::Core::byte> GetBytes(const uint16_t Value);
		static const Collections::Template::Array<Elysium::Core::byte> GetBytes(const uint32_t Value);
		static const Collections::Template::Array<Elysium::Core::byte> GetBytes(const uint64_t Value);

		static const int16_t ToInt16(const Elysium::Core::byte* Value);
		static const int32_t ToInt24(const Elysium::Core::byte* Value);	// ToDo: return custom uint24_t-type?
		static const int32_t ToInt32(const Elysium::Core::byte* Value);
		static const int64_t ToInt64(const Elysium::Core::byte* Value);
		static const uint16_t ToUInt16(const Elysium::Core::byte* Value);
		static const uint32_t ToUInt24(const Elysium::Core::byte* Value);	// ToDo: return custom uint24_t-type?
		static const uint32_t ToUInt32(const Elysium::Core::byte* Value);
		static const uint64_t ToUInt64(const Elysium::Core::byte* Value);
	private:
		BitConverter();
	};
}
#endif
