/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GUID
#define ELYSIUM_CORE_GUID

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Guid final
	{
		friend class Collections::Template::List<Guid>;
	public:
		Guid(const Elysium::Core::byte B[16]);
		Guid(const Elysium::Core::uint32_t A, const Elysium::Core::uint16_t B, const Elysium::Core::uint16_t C, const Elysium::Core::byte* D[8]);
		Guid(const Guid& Source);
		Guid(Guid&& Right) noexcept;
		~Guid();

		Guid& operator=(const Guid& Source);
		Guid& operator=(Guid&& Right) noexcept;

		const bool operator==(const Guid& Other);
		const bool operator!=(const Guid& Other);
		const bool operator<(const Guid& Other);
		const bool operator>(const Guid& Other);
		const bool operator<=(const Guid& Other);
		const bool operator>=(const Guid& Other);

		static const Guid& Empty();
		static Guid NewGuid();
		static Guid Parse(const char8_t* Input);

		const byte* ToByteArray() const;
		String ToString() const;
	private:
		//byte _Data[16];
		Elysium::Core::uint64_t _Data;

		Guid();

		static Guid _EmptyGuid;

		static void ParseN(const char8_t* Input, Elysium::Core::byte* Data);
		static void ParseD(const char8_t* Input, Elysium::Core::byte* Data);
		static void ParseB(const char8_t* Input, Elysium::Core::byte* Data);
		static void ParseP(const char8_t* Input, Elysium::Core::byte* Data);
		static void ParseX(const char8_t* Input, Elysium::Core::byte* Data);

		static Elysium::Core::uint8_t HexDigitToChar(char8_t Input);
		static void ByteToHexDigit(Elysium::Core::byte Input, char8_t* Chars);
	};
}
#endif
