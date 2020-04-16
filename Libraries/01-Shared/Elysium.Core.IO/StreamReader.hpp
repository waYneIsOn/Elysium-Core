/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_STREAMREADER
#define ELYSIUM_CORE_IO_STREAMREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_TEXTREADER
#include "TextReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API StreamReader : public TextReader
	{
	public:
		StreamReader(Stream& InputStream);
		~StreamReader();

		virtual void Close() override;

		virtual const int32_t Peek() override;

		virtual const int32_t Read() override;

		virtual StringView ReadLine() override;

		virtual StringView ReadToEnd() override;
	private:
		size_t _Position;
		Stream& _InputStream;
	};
}
#endif
