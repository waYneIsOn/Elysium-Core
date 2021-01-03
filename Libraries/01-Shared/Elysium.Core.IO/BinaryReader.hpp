/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_BINARYREADER
#define ELYSIUM_CORE_IO_BINARYREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
	class ELYSIUM_CORE_API BinaryReader
	{
	public:
		BinaryReader(Stream& BaseStream, const Elysium::Core::Text::Encoding& Encoding, const bool LeaveOpen);
		BinaryReader(const BinaryReader& Source) = delete;
		BinaryReader(BinaryReader&& Right) noexcept = delete;
		~BinaryReader();

		BinaryReader& operator=(const BinaryReader& Source) = delete;
		BinaryReader& operator=(BinaryReader&& Right) noexcept = delete;

		virtual Elysium::Core::IO::Stream& GetBaseStream() const;

		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> ReadBytes(const Elysium::Core::uint32_t Count);
		virtual const Elysium::Core::uint16_t ReadUInt16();
		virtual const Elysium::Core::uint32_t ReadUInt32();
	private:
		Stream& _BaseStream;
		const Elysium::Core::Text::Encoding& _Encoding;
		const bool _LeaveOpen;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _Buffer;
	};
}
#endif
