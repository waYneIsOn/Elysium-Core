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
	/// <summary>
	/// No relationship required whatsoever between sink and source.
	/// </summary>
	struct Independent
	{
		template<class Sink, class Source>
		static constexpr void Validate(Sink& SinkX, Source& SourceX)
		{ }
	};

	/// <summary>
	/// Both sink and source are required to operate on the same underlying device.
	/// </summary>
	struct DeviceCoupled
	{
		template<class Sink, class Source>
		static constexpr void Validate(Sink& SinkX, Source& SourceX)
		{
			const Sink::DeviceType& SinkDevice = SinkX.GetDevice();
			const Source::DeviceType& SourceDevice = SourceX.GetDevice();
			if (&SinkDevice != &SourceDevice)
			{	// @ToDo: throw specific exception (Elysium::Core::Template::Security::Policy::PolicyException???)
				throw 1;
			}
		}
	};

	/// <summary>
	/// Both sink and source are required to operate on the same underlying device resource/handle.
	/// </summary>
	struct DeviceResourceShared
	{
		template<class Sink, class Source>
		static constexpr void Validate(Sink& SinkX, Source& SourceX)
		{
			const Sink::DeviceType& SinkDevice = SinkX.GetDevice();
			const Source::DeviceType& SourceDevice = SourceX.GetDevice();
			if (SinkDevice != SourceDevice)
			{	// @ToDo: throw specific exception (Elysium::Core::Template::Security::Policy::PolicyException???)
				throw 1;
			}
		}
	};

	/// <summary>
	/// 
	/// </summary>
	struct TlsCoupled
	{
		template<class Sink, class Source>
		static constexpr void Validate(Sink& SinkX, Source& SourceX)
		{
			if (SinkX.GetSession() != SourceX.GetSession())
			{	// @ToDo: throw specific exception (Elysium::Core::Template::Security::Policy::PolicyException???)
				throw 1;
			}
		}
	};

	/// <summary>
	/// 
	/// </summary>
	struct QuicCoupled
	{
		template<class Sink, class Source>
		static constexpr void Validate(Sink& SinkX, Source& SourceX)
		{
			if (SinkX.GetConnection() != SourceX.GetConnection() || SinkX.GetStreamId() != SourceX.GetStreamId())
			{	// @ToDo: throw specific exception (Elysium::Core::Template::Security::Policy::PolicyException???)
				throw 1;
			}
		}
	};
	
	// @ToDo: concept for sinks, sources and policies!
	template<class Sink, class Source, class Policy = Independent>
	class InOutStream
	{
	public:
		constexpr InOutStream() noexcept = delete;

		inline constexpr InOutStream(Sink& Sink, Source& Source)
			: _Sink(Sink), _Source(Source)
		{
			Policy::Validate(Sink, Source);
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
