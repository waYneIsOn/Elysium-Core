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
		StreamReader(Stream& InputStream, const Elysium::Core::Text::Encoding& Encoding, const bool DetectEncodingFromByteOrderMarks = true, const Elysium::Core::int32_t MinimumBufferSize = -1, const bool LeaveOpen = false);
		StreamReader(const StreamReader& Source) = delete;
		StreamReader(StreamReader&& Right) noexcept = delete;
		virtual ~StreamReader();

		StreamReader& operator=(const StreamReader& Other) = delete;
		StreamReader& operator=(StreamReader&& Right) noexcept = delete;

		virtual void Close() override;

		virtual const Elysium::Core::int32_t Peek() override;

		virtual const Elysium::Core::int32_t Read() override;

		virtual const Elysium::Core::int32_t Read(char8_t* Buffer, const Elysium::Core::int32_t Count) override;

		virtual Elysium::Core::String ReadLine() override;

		virtual Elysium::Core::String ReadToEnd() override;
	private:
		Stream& _InputStream;
		const Elysium::Core::Text::Encoding& _Encoding;
		const bool _LeaveOpen;

		static constexpr const Elysium::Core::uint32_t DefaultBufferSize = 4096;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _Buffer;
		Elysium::Core::uint64_t _BufferPosition;
	};
}
#endif
