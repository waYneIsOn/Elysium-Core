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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_TEXTREADER
#include "TextReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API StreamReader : public TextReader
	{
	public:
		StreamReader(Stream& InputStream, Elysium::Core::Text::Encoding& Encoding, const bool DetectEncodingFromByteOrderMarks = true, const Elysium::Core::int32_t MinimumBufferSize = -1, const bool LeaveOpen = false);
		StreamReader(const StreamReader& Source) = delete;
		StreamReader(StreamReader&& Right) noexcept = delete;
		virtual ~StreamReader();

		StreamReader& operator=(const StreamReader& Other) = delete;
		StreamReader& operator=(StreamReader&& Right) noexcept = delete;

		virtual void Close() override;

		virtual const Elysium::Core::uint8_t Peek() override;

		virtual const Elysium::Core::uint8_t Read() override;

		virtual const Elysium::Core::int32_t Read(char8_t* Buffer, const Elysium::Core::int32_t Count) override;

		virtual Elysium::Core::String ReadLine() override;

		virtual Elysium::Core::String ReadToEnd() override;
	private:
		static const size_t DefaultBufferSize = 4096;

		Stream& _InputStream;
		Elysium::Core::Text::Encoding& _Encoding;
		bool _DetectEncoding;
		bool _LeaveOpen;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _Buffer;
		Elysium::Core::uint64_t _BufferWritingPosition;
		Elysium::Core::uint64_t _BufferReadingPosition;

		void FillBuffer(const size_t Count);

		/// <summary>
		/// Read the first few bytes to detect BOMs.
		/// Obviously any file could simply be starting with those bytes, ergo this performs a "best effort guess".
		/// </summary>
		void DetectEncoding();
	};
}
#endif
