/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_STREAMWRITER
#define ELYSIUM_CORE_IO_STREAMWRITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_TEXTWRITER
#include "TextWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API StreamWriter : public TextWriter
	{
	public:
		StreamWriter(Stream& OutputStream);
		StreamWriter(Stream& OutputStream, const Elysium::Core::Text::Encoding& Encoding);
		StreamWriter(const StreamWriter& Source) = delete;
		StreamWriter(StreamWriter&& Right) noexcept = delete;
		virtual ~StreamWriter();

		StreamWriter& operator=(const StreamWriter& Other) = delete;
		StreamWriter& operator=(StreamWriter&& Right) noexcept = delete;

		virtual const Text::Encoding& GetEncoding() override;

		virtual void Close() override;

		virtual void Flush() override;

		virtual void Write(const byte* Value, const Elysium::Core::size Length) override;
	private:
		Stream& _OutputStream;
		const Elysium::Core::Text::Encoding& _Encoding;
	};
}
#endif
