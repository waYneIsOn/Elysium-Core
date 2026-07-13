/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_DEFLATESOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_DEFLATESOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKHEADER
#include "../Compression/Format/Deflate/DeflateBlockHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATESTATE
#include "../Compression/Format/Deflate/DeflateState.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	// @ToDo: concept for sources!
	template <class InnerSource>
	class DeflateSource
	{
	public:
		using DeviceType = InnerSource::DeviceType;
	public:
		inline constexpr DeflateSource(InnerSource& InnerSource, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _State(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader), _InnerSource(InnerSource)
		{ }

		constexpr DeflateSource(const DeflateSource& Source) = delete;

		constexpr DeflateSource(DeflateSource&& Right) noexcept = delete;

		inline ~DeflateSource()
		{
			Close();
		}
	public:
		constexpr DeflateSource& operator=(const DeflateSource& Source) = delete;

		constexpr DeflateSource& operator=(DeflateSource&& Right) noexcept = delete;
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
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _InnerSource.Close(); })
			{
				_InnerSource.Close();
			}
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			while (true)
			{
				switch (_State)
				{
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader:
				{
					/*
					Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DeflateDataView{};
					_InnerSource.ReadBlock(DeflateDataView);

					Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader* Header =
						reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader*>(DeflateDataView.GetData());

					const bool IsFinalBlock = Header->GetIsFinalBlock();
					const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType BlockType = Header->GetCompressionMethod();

					return false;
					*/
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done:
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				default:
					// @ToDo
					throw 1;
				}
			}
			
			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			_InnerSource.AdvanceReadingBlock(Length);
		}
	private:
		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState _State;

		InnerSource& _InnerSource;
	};
}
#endif
