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
	protected:
		TextReader();
	public:
		TextReader(const TextReader& Source) = delete;

		TextReader(TextReader&& Right) noexcept = delete;

		virtual ~TextReader();
	public:
		TextReader& operator=(const TextReader& Other) = delete;

		TextReader& operator=(TextReader&& Right) noexcept = delete;
	public:
		virtual void Close();

		virtual const Elysium::Core::uint32_t Peek() = 0;
		
		virtual const Elysium::Core::uint32_t Read() = 0;

		virtual const Elysium::Core::size Read(char8_t* Buffer, const Elysium::Core::size Count) = 0;

		virtual Elysium::Core::Utf8String ReadLine() = 0;

		virtual Elysium::Core::Utf8String ReadToEnd() = 0;
	};
}
#endif
