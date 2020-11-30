/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_TEXTREADER
#define ELYSIUM_CORE_IO_TEXTREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_DECIMAL
#include "../Elysium.Core/Decimal.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API TextReader
	{
	public:
		virtual ~TextReader();

		virtual void Close();

		virtual const int32_t Peek();
		
		virtual const int32_t Read();
		//virtual int Read(array<char>& Buffer, int Index, int Count);
		//virtual int Read(String& Buffer, int Index, int Count);

		virtual String ReadLine() = 0;

		virtual String ReadToEnd() = 0;
	protected:
		TextReader();
	};
}
#endif
