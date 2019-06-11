/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_GUID
#define ELYSIUM_CORE_GUID

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef _STDINT_H
#include <cstdint>
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "List.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API Guid final
		{
			friend class Collections::Generic::List<Guid>;
		public:
			Guid(const byte B[16]);
			Guid(const uint32_t A, const uint16_t B, const uint16_t C, const byte* D[8]);
			~Guid();

			static const Guid& Empty();
			static Guid NewGuid();
			static Guid Parse(const char* Input);

			const byte* ToByteArray() const;
			void ToString(String* Output) const;
			//std::string ToString() const;

			// relational operators
			bool operator==(const Guid& Other);
			bool operator!=(const Guid& Other);
			bool operator<(const Guid& Other);
			bool operator>(const Guid& Other);
			bool operator<=(const Guid& Other);
			bool operator>=(const Guid& Other);
		private:
			byte _Data[16];

			Guid();

			static Guid _EmptyGuid;

			static void ParseN(const char* Input, byte* Data);
			static void ParseD(const char* Input, byte* Data);
			static void ParseB(const char* Input, byte* Data);
			static void ParseP(const char* Input, byte* Data);
			static void ParseX(const char* Input, byte* Data);

			static char HexDigitToChar(char Input);
			static void ByteToHexDigit(byte Input, char* Chars);
		};
	}
}
#endif
