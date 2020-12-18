/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_TEXTWRITER
#define ELYSIUM_CORE_IO_TEXTWRITER

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

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API TextWriter
	{
	public:
		TextWriter(const TextWriter& Source) = delete;
		TextWriter(TextWriter&& Right) noexcept = delete;
		virtual ~TextWriter();

		TextWriter& operator=(const TextWriter& Other) = delete;
		TextWriter& operator=(TextWriter&& Right) noexcept = delete;

		virtual const Text::Encoding& GetEncoding();
		virtual const String& GetNewLine();

		virtual void SetNewLine(const String& NewLine);

		virtual void Close();

		virtual void Flush();

		virtual void Write(const bool Value);

		virtual void Write(const byte Value);

		virtual void Write(const byte* Value, const size_t Count) = 0;

		virtual void Write(const char8_t Value);

		virtual void Write(const char8_t* Value, const size_t Count);

		virtual void Write(const float Value);

		virtual void Write(const double Value);

		virtual void Write(const Decimal& Value);

		virtual void Write(const int16_t Value);

		virtual void Write(const int32_t Value);

		virtual void Write(const int64_t Value);

		virtual void Write(const uint16_t Value);

		virtual void Write(const uint32_t Value);

		virtual void Write(const uint64_t Value);

		virtual void Write(const String& Value);


		virtual void WriteLine(const bool Value);

		virtual void WriteLine(const byte Value);

		virtual void WriteLine(const byte* Value, const size_t Count);

		virtual void WriteLine(const char8_t Value);

		virtual void WriteLine(const char8_t* Value, const size_t Count);

		virtual void WriteLine(const float Value);

		virtual void WriteLine(const double Value);

		virtual void WriteLine(const Decimal& Value);

		virtual void WriteLine(const int16_t Value);

		virtual void WriteLine(const int32_t Value);

		virtual void WriteLine(const int64_t Value);

		virtual void WriteLine(const uint16_t Value);

		virtual void WriteLine(const uint32_t Value);

		virtual void WriteLine(const uint64_t Value);

		virtual void WriteLine(const String& Value);

		virtual void WriteLine();
	protected:
		TextWriter();
	private:
		Elysium::Core::String _NewLineCharacters;
	};
}
#endif
