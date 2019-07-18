/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#define ELYSIUM_CORE_TEXT_ENCODING

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Text
		{
			class ELYSIUM_CORE_API ASCIIEncoding;
			class ELYSIUM_CORE_API UnicodeEncoding;
			class ELYSIUM_CORE_API UTF32Encoding;
			class ELYSIUM_CORE_API UTF7Encoding;
			class ELYSIUM_CORE_API UTF8Encoding;

			class ELYSIUM_CORE_API Encoding
			{
			public:
				Encoding(const Encoding& Encoding);
				virtual ~Encoding();

				static void GetEncoding(int CodePage, Encoding* Output);

				static const Encoding* ASCII();
				static const Encoding* BigEndianUnicode();	// UTF-16 big-endian
				static const Encoding* Default();
				static const Encoding* Unicode();	// UTF-16 little-endian
				static const Encoding* UTF32();
				static const Encoding* UTF7();
				static const Encoding* UTF8();
				
				// properties - getter
				virtual bool GetIsSingleByte() const;
				virtual int GetCodePage() const;
				virtual const String& GetEncodingName() const;

				// methods
				virtual Elysium::Core::Collections::Generic::List<byte> GetBytes(const String& Input, const size_t CharIndex, const size_t CharCount) const;
				virtual String GetString(const byte* Bytes, const size_t ByteCount) const;
			protected:
				Encoding();
				Encoding(int CodePage);
			private:
				int _CodePage;
				String _EncodingName;
				bool _IsSingleByte;

				static const Encoding _Default;
				static const UTF8Encoding _UTF8;
				static const ASCIIEncoding _ASCII;
			};
		}
	}
}
#endif
