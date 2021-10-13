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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../Elysium.Core/ArrayOfByte.hpp"
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

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API BinaryReader
	{
	public:
		BinaryReader(Stream& InputStream, Elysium::Core::Text::Encoding& Encoding, const bool LeaveOpen = false);
		BinaryReader(const BinaryReader& Source) = delete;
		BinaryReader(BinaryReader&& Right) noexcept = delete;
		~BinaryReader();

		BinaryReader& operator=(const BinaryReader& Source) = delete;
		BinaryReader& operator=(BinaryReader&& Right) noexcept = delete;

		virtual Elysium::Core::IO::Stream& GetBaseStream() const;

		virtual void Close();
		virtual const bool ReadBoolean();
		virtual const Elysium::Core::byte ReadByte();
		virtual const Elysium::Core::size ReadBytes(Elysium::Core::byte* Buffer, const Elysium::Core::size Count);
		virtual const double ReadDouble();
		virtual const Elysium::Core::int16_t ReadInt16();
		virtual const Elysium::Core::int32_t ReadInt32();
		virtual const Elysium::Core::int64_t ReadInt64();
		virtual const float ReadSingle();
		virtual const Elysium::Core::uint16_t ReadUInt16();
		virtual const Elysium::Core::uint32_t ReadUInt32();
		virtual const Elysium::Core::uint64_t ReadUInt64();
	private:
		static const Elysium::Core::size DefaultBufferSize = 16;

		Stream& _InputStream;
		Elysium::Core::Text::Encoding& _Encoding;
		const bool _LeaveOpen;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _Buffer;
	protected:
		void FillBuffer(const Elysium::Core::size Count);
	};
}
#endif
