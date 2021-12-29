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
		StringReader(const Elysium::Core::Utf8String& Input);

		StringReader(const StringReader& Source) = delete;

		StringReader(StringReader&& Right) noexcept = delete;

		virtual ~StringReader();
	public:
		StringReader& operator=(const StringReader& Other) = delete;

		StringReader& operator=(StringReader&& Right) noexcept = delete;
	public:
		virtual const Elysium::Core::uint32_t Peek() override;

		virtual const Elysium::Core::uint32_t Read() override;

		virtual const Elysium::Core::size Read(char8_t* Buffer, const Elysium::Core::size Count) override;

		virtual Elysium::Core::Utf8String ReadLine() override;

		virtual Elysium::Core::Utf8String ReadToEnd() override;
	private:
		Elysium::Core::uint64_t _Position = 0;
		Elysium::Core::Utf8StringView _Input;
	};
}
#endif
