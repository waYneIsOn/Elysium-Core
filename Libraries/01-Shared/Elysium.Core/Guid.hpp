/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_GUID
#define ELYSIUM_CORE_GUID

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT Guid final
		{
		public:
			Guid(const byte B[16]);
			Guid(const unsigned __int32 A, const unsigned __int16 B, const unsigned __int16 C, const byte* D[8]);
			~Guid();

			static const Guid& Empty();
			static Guid NewGuid();
			static Guid Parse(const char* Input);

			const byte* ToByteArray() const;
			std::string ToString() const;
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
