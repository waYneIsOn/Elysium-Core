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

namespace Elysium::Core::Template::IO
{
	// @ToDo: concept for sinks and sources!
	template<class Sink, class Source>
	class InOutStream
	{
	public:
		constexpr InOutStream() noexcept = delete;

		inline constexpr InOutStream(Sink& Sink, Source& Source) noexcept
			: _Sink(Sink), _Source(Source)
		{ }

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
		inline const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
		{
			return _Source.Read(Buffer, Count);
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
	using FileStream = InOutStream<BufferedSink<FileSink>, BufferedSource<FileSource>>;
	using MemoryStream = InOutStream<BufferedSink<MemorySink>, BufferedSource<MemorySource>>;
	using NetworkStream = InOutStream<BufferedSink<SocketSink>, BufferedSource<SocketSource>>;

	using GZipFileStream = InOutStream<BufferedSink<GZipSink<FileSink>>, BufferedSource<GZipSource<FileSource>>>;
	*/
}
#endif
