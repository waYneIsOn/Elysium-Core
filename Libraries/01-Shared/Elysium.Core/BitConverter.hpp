/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

		static const Collections::Template::Array<byte> GetBytes(int16_t Value);
		static const Collections::Template::Array<byte> GetBytes(int32_t Value);
		static const Collections::Template::Array<byte> GetBytes(int64_t Value);
		static const Collections::Template::Array<byte> GetBytes(uint16_t Value);
		static const Collections::Template::Array<byte> GetBytes(uint32_t Value);

		static const uint16_t ToUint16(byte* Value);
	private:
		BitConverter();
	};
}
#endif
