/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		~StreamWriter();

		virtual const Text::Encoding& GetEncoding() override;

		virtual void Close() override;
		virtual void Flush() override;

		virtual void Write(const byte* Value, const size_t Length) override;
	private:
		Stream& _OutputStream;
	};
}
#endif
