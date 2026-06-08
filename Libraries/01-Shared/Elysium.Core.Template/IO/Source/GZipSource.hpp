/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_GZIPSOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_GZIPSOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPFOOTER
#include "../Compression/Format/GZip/GZipFooter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPHEADER
#include "../Compression/Format/GZip/GZipHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	// @ToDo: concept for sources!
	template <class InnerSource>
	class GZipSource
	{
	public:
		using DeviceType = InnerSource::DeviceType;
	public:
		inline constexpr GZipSource(InnerSource& InnerSource, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _Position(0), _InnerSource(InnerSource)
		{}

		constexpr GZipSource(const GZipSource& Source) = delete;

		constexpr GZipSource(GZipSource&& Right) noexcept = delete;

		inline ~GZipSource()
		{
			Close();
		}
	public:
		constexpr GZipSource& operator=(const GZipSource& Source) = delete;

		constexpr GZipSource& operator=(GZipSource&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSource.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSource.GetPosition();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSource.GetDevice();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSource.SetPosition(Position);
			_Position = 0;
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _InnerSource.Close(); })
			{
				_InnerSource.Close();
			}
		}

		inline Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader ReadHeader()
		{
			// @ToDo: might want to add a positional check?

			Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader Header{};
			Elysium::Core::Template::System::byte* AddressOfHeader = reinterpret_cast<Elysium::Core::Template::System::byte*>(&Header);

			{
				Elysium::Core::Template::System::size TotalBytesRead = 0;
				while (TotalBytesRead < Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::Size)
				{
					Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&AddressOfHeader[TotalBytesRead],
						Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::Size - TotalBytesRead);
					TotalBytesRead += BytesRead;
				}
			}

			if (!Header.ValidateIds())
			{	// @ToDo: magic number incorrect -> not a gzip file
				throw 1;
			}

			if (!Header.ValidateCompressionMethod())
			{	// @ToDo: must be deflate (8)
				throw 1;
			}

			if (0x1F != Header._Id1 || 0x8B != Header._Id2)
			{	// @ToDo: magic number incorrect -> not a gzip file
				throw 1;
			}

			if (8 != Header._CompressionMethod)
			{	// @ToDo: must be deflate (8)
				throw 1;
			}

			return Header;
		}

		inline void ReadOptionalHeader(const Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader& Header)
		{
			// @ToDo: might want to add a positional check?
			// @ToDo: the following code basically reads byte by byte -> improve!!!
			if (Header.GetExtraExists())
			{
				Elysium::Core::Template::System::uint16_t ExtraLength;
				Elysium::Core::Template::System::byte* AddressOfExtraLength = reinterpret_cast<Elysium::Core::Template::System::byte*>(&ExtraLength);

				Elysium::Core::Template::System::size TotalBytesRead = 0;
				while (TotalBytesRead < sizeof(ExtraLength))
				{
					Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&AddressOfExtraLength[TotalBytesRead], sizeof(ExtraLength) - TotalBytesRead);
					TotalBytesRead += BytesRead;
				}

				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Extra(ExtraLength);
				TotalBytesRead = 0;
				while (TotalBytesRead < ExtraLength)
				{
					Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&Extra[TotalBytesRead], ExtraLength - TotalBytesRead);
					TotalBytesRead += BytesRead;
				}
			}

			if (Header.GetNameExists())
			{
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Name(1);
				Name.Clear();
				byte CurrentByte;

				do
				{
					Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&CurrentByte, sizeof(CurrentByte));
					if (0 == BytesRead)
					{
						continue;
					}

					Name.PushBack(CurrentByte);
				} while (0x00 != CurrentByte);
			}

			if (Header.GetCommentExists())
			{
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Comment(1);
				Comment.Clear();
				byte CurrentByte;

				do
				{
					Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&CurrentByte, sizeof(CurrentByte));
					if (0 == BytesRead)
					{
						continue;
					}

					Comment.PushBack(CurrentByte);
				} while (0x00 != CurrentByte);
			}

			if (Header.GetHeaderCrcExists())
			{
				Elysium::Core::Template::System::uint16_t Crc;
				Elysium::Core::Template::System::byte* AddressOfCrc = reinterpret_cast<Elysium::Core::Template::System::byte*>(&Crc);

				Elysium::Core::Template::System::size TotalBytesRead = 0;
				while (TotalBytesRead < sizeof(Crc))
				{
					Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&AddressOfCrc[TotalBytesRead], sizeof(Crc) - TotalBytesRead);
					TotalBytesRead += BytesRead;
				}
			}
		}

		inline bool ReadBlock()
		{
			// 1st byte:
			//	- 1st bit BFINAL: final block == 1
			//  - 2nd and 3rd bit BTYPE:
			//		- 00 (0) uncompressed
			//		- 01 (1) compressed fixed huffman codes
			//		- 10 (2) compressed dynamic huffmand codes
			//		- 11 (3) reserved (currently invalid afaik)


			return false;
		}

		inline Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter ReadFooter()
		{
			// @ToDo: might want to add a positional check?

			Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter Footer{};
			Elysium::Core::Template::System::byte* AddressOfFooter = reinterpret_cast<Elysium::Core::Template::System::byte*>(&Footer);

			Elysium::Core::Template::System::size TotalBytesRead = 0;
			while (TotalBytesRead < Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size)
			{
				Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&AddressOfFooter[TotalBytesRead],
					Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size - TotalBytesRead);
				TotalBytesRead += BytesRead;
			}

			return Footer;
		}

		inline const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
		{
			return 0;
			/*
			if (_Position == _EndPosition)
			{
				Elysium::Core::Template::System::size BytesToBuffer = Elysium::Core::Template::Math::Min(_Buffer.GetCapacity(), _InnerSource.GetLength());

				_Position = 0;
				_EndPosition = _InnerSource.Read(&_Buffer[_Position], BytesToBuffer);
			}

			Elysium::Core::Template::System::size BytesToRead = Elysium::Core::Template::Math::Min(_Buffer.GetCapacity(), Count);

			Elysium::Core::Template::Memory::MemCpy(Buffer, &_Buffer[_Position], BytesToRead);

			_Position += BytesToRead;

			return BytesToRead;
			*/
		}
	private:
		Elysium::Core::Template::System::size _Position;
		InnerSource& _InnerSource;
	};
}
#endif
