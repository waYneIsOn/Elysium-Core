/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_STRINGWRITER
#define ELYSIUM_CORE_IO_STRINGWRITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_TEXTWRITER
#include "TextWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API StringWriter : public TextWriter
	{
	public:
		StringWriter(Elysium::Core::Text::StringBuilder& StringBuilder);
		StringWriter(const StringWriter& Source) = delete;
		StringWriter(StringWriter&& Right) noexcept = delete;
		virtual ~StringWriter();

		StringWriter& operator=(const StringWriter& Other) = delete;
		StringWriter& operator=(StringWriter&& Right) noexcept = delete;

		virtual void Write(const byte* Value, const size_t Length) override;
		virtual void Write(const String& Value) override;
	private:
		Elysium::Core::Text::StringBuilder& _StringBuilder;
	};
}
#endif
