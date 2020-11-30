/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
		StreamReader(Stream& InputStream, const Text::Encoding& Encoding, const bool DetectEncodingFromByteOrderMarks = true, const Elysium::Core::int32_t MinimumBufferSize = -1, const bool LeaveOpen = false);
		~StreamReader();

		virtual void Close() override;

		virtual const int32_t Peek() override;

		virtual const int32_t Read() override;

		virtual String ReadLine() override;

		virtual String ReadToEnd() override;
	private:
		size_t _Position;
		Stream& _InputStream;
		const Text::Encoding& _Encoding;
		const bool _LeaveOpen;

		//Elysium::Core::Collections::Template::List<Elysium::Core::byte> _Buffer;
	};
}
#endif
