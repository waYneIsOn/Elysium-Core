/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_INOUTSTREAM
#define ELYSIUM_CORE_TEMPLATE_IO_INOUTSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO
{
	struct DeviceIndependent
	{
		inline static constexpr bool RequireShared = false;
	};

	struct DeviceCoupled
	{
		inline static constexpr bool RequireShared = true;
	};

	// @ToDo: concept for sinks, sources and policies!
	template<class Sink, class Source, class Policy = DeviceIndependent>
	class InOutStream
	{
	public:
		constexpr InOutStream() noexcept = delete;

		inline constexpr InOutStream(Sink& Sink, Source& Source)
			: _Sink(Sink), _Source(Source)
		{
			if constexpr (Policy::RequireShared)
			{
				const Sink::DeviceType& SinkDevice = _Sink.GetDevice();
				const Source::DeviceType& SourceDevice = _Source.GetDevice();
				if (SinkDevice != SourceDevice)
				{	// @ToDo: throw specific exception (Elysium::Core::Template::Security::Policy::PolicyException???)
					throw 1;
				}
			}
		}

		constexpr InOutStream(const InOutStream& Source) = delete;

		constexpr InOutStream(InOutStream&& Right) noexcept = delete;

		~InOutStream()
		{
			Flush();
			Close();
		}
	public:
		constexpr InOutStream& operator=(const InOutStream& Source) = delete;

		constexpr InOutStream& operator=(InOutStream&& Right) noexcept = delete;
	public:
		inline void SetPosition(const Elysium::Core::Template::System::size Value)
		{
			_Sink.SetPosition(Value);
			_Source.SetPosition(Value);
		}

		inline void SetReadPosition(const Elysium::Core::Template::System::size Value)
		{
			_Source.SetPosition(Value);
		}

		inline void SetWritePosition(const Elysium::Core::Template::System::size Value)
		{
			_Sink.SetPosition(Value);
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _Sink.Close(); })
			{
				_Sink.Close();
			}
			if constexpr (requires { _Source.Close(); })
			{
				_Source.Close();
			}
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			return _Source.ReadBlock(DataView);
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			_Source.AdvanceReadingBlock(Length);
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			_Sink.Write(Buffer, Count);
		}

		inline void Flush()
		{
			if constexpr (requires { _Sink.Flush(); })
			{
				_Sink.Flush();
			}
		}
	private:
		Sink& _Sink;
		Source& _Source;
	};
	/*
	using FileStream = InOutStream<FileSink, FileSource>;
	using BufferedFileStream = InOutStream<BufferedSink<FileSink>, BufferedSource<FileSource>>;

	using MemoryStream = InOutStream<MemorySink, MemorySource>;
	using BufferedMemoryStream = InOutStream<BufferedSink<MemorySink>, BufferedSource<MemorySource>>;




	using NetworkStream = InOutStream<BufferedSink<SocketSink>, BufferedSource<SocketSource>>;

	using GZipFileStream = InOutStream<BufferedSink<GZipSink<FileSink>>, BufferedSource<GZipSource<FileSource>>>;
	*/
}
#endif
