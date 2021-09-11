/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_STRINGREADER
#define ELYSIUM_CORE_IO_STRINGREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_TEXTREADER
#include "TextReader.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API StringReader : public TextReader
	{
	public:
		StringReader(const String& Input);
		StringReader(const StringReader& Source) = delete;
		StringReader(StringReader&& Right) noexcept = delete;
		virtual ~StringReader();

		StringReader& operator=(const StringReader& Other) = delete;
		StringReader& operator=(StringReader&& Right) noexcept = delete;

		virtual const Elysium::Core::uint8_t Peek() override;

		virtual const Elysium::Core::uint8_t Read() override;

		virtual Elysium::Core::String ReadLine() override;

		virtual Elysium::Core::String ReadToEnd() override;
	private:
		Elysium::Core::uint64_t _Position = 0;
		StringView _Input;
	};
}
#endif
