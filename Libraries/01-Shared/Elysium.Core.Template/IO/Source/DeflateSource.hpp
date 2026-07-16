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

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#include "../Compression/Format/Deflate/DeflateBlockType.hpp"
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

		using MostInnerSourceType = InnerSource::MostInnerSourceType;
	public:
		inline constexpr DeflateSource(InnerSource& InnerSource, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _State(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader), _InnerSource(InnerSource)
		{ }

		constexpr DeflateSource(const DeflateSource& Source) = delete;

		constexpr DeflateSource(DeflateSource&& Right) noexcept = delete;

		constexpr ~DeflateSource() = default;
	public:
		constexpr DeflateSource& operator=(const DeflateSource& Source) = delete;

		constexpr DeflateSource& operator=(DeflateSource&& Right) noexcept = delete;
	public:
		inline MostInnerSourceType& GetMostInnerSource()
		{
			return _InnerSource.GetMostInnerSource();
		}

		inline DeviceType& GetDevice()
		{
			return _InnerSource._Device;
		}

		inline constexpr DeviceType& GetDevice() const
		{
			return _InnerSource._Device;
		}
	public:
		inline constexpr Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSource.GetLength();
		}

		inline constexpr Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSource.GetPosition();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSource.SetPosition(Position);
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetView)
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

	private:
		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState _State;

		InnerSource& _InnerSource;
	};
}
#endif
