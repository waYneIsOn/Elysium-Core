/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_ZLIBHEADER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPHEADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_KNOWNCOMPRESSIONALGORITHM
#include "../../KnownCompressionAlgorithm.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::ZLib
{
	struct ZLibHeader final
	{
	public:
		inline Elysium::Core::Template::System::byte GetCompressionMethod() const
		{
			return _CompressionMethodsAndFlags & 0x0F;
		}

		inline Elysium::Core::Template::System::byte GetCompressionInfo() const
		{
			return _CompressionMethodsAndFlags >> 4;
		}

		inline Elysium::Core::Template::System::byte GetFlagLevel() const
		{	// just a hint about compression (00 = fastest, 01 = fast, 10 = default, 11 = maximum)
			return (_Flag >> 6) & 0x03;
		}

		inline bool GetFlagDictionary() const
		{
			return (_Flag >> 5) & 0x01;
		}
	public:
		inline void SetCompressionMethod(const Elysium::Core::Template::IO::Compression::KnownCompressionAlgorithm Algorithm)
		{
			if (Elysium::Core::Template::IO::Compression::KnownCompressionAlgorithm::Deflate != Algorithm)
			{	// @ToDo: throw a specific exception! zlib only supports deflate
				throw;
			}

			_CompressionMethodsAndFlags = (_CompressionMethodsAndFlags & 0xF0) | 8;
		}

		inline void SetCompressionInfo(const Elysium::Core::Template::System::byte Info)
		{
			/*
			* 0 = 256 bytes
			* 1 = 512 bytes
			* 2 = 1024 bytes
			* 3 = 2048 bytes
			* 4 = 4096 bytes
			* ...
			* 7 = 32768 bytes
			*/
			if (7 < Info)
			{	// @ToDo: throw a specific exception!
				// @ToDo: I should ensure I can change Deflate's LZ77 sliding window capacity! otherwise malformed streams would be valid!
				throw;
			}

			_CompressionMethodsAndFlags = (_CompressionMethodsAndFlags & 0x0F) | (Info << 4);
		}

		inline void SetFlagLevel(const Elysium::Core::Template::System::byte Level)
		{
			/*
			* 00 = fastest
			* 01 = fast
			* 10 = default
			* 11 = maximum compression
			*/
			if (3 < Level)
			{	// @ToDo
				throw;
			}

			_Flag = (_Flag & 0x3F) | ((Level & 0x03) << 6);
		}

		inline void SetFlagDictionary(const bool UsePresetDictionary)
		{
			_Flag = (_Flag & ~(1 << 5)) | (UsePresetDictionary << 5);
		}
	public:
		inline bool Validate() const
		{
			return (_CompressionMethodsAndFlags << 8 | _Flag) % 31 == 0;
		}
	public:
		inline void RecalculateFlagCheck()
		{
			_Flag &= 0xE0;

			const Elysium::Core::Template::System::uint16_t FullHeader = (static_cast<Elysium::Core::Template::System::uint16_t>(_CompressionMethodsAndFlags) << 8) | _Flag;
			const Elysium::Core::Template::System::byte FCHECK = static_cast<Elysium::Core::Template::System::byte>((31 - (FullHeader % 31)) % 31);

			_Flag |= FCHECK;
		}
	private:
		Elysium::Core::Template::System::byte _CompressionMethodsAndFlags;
		Elysium::Core::Template::System::byte _Flag;
	};
}
#endif
