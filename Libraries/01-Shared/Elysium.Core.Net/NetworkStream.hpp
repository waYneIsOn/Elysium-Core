/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#define ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "Socket.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
	class ELYSIUM_CORE_NET_API NetworkStream : public Elysium::Core::IO::Stream
	{
	public:
		NetworkStream(Socket& Socket);
		NetworkStream(Socket& Socket, bool OwnsSocket);
		virtual ~NetworkStream();

		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const Elysium::Core::size GetLength() const override;
		virtual const Elysium::Core::uint64_t GetPosition() const override;
		virtual const Elysium::Core::uint32_t GetReadTimeout() const override;
		virtual const Elysium::Core::uint32_t GetWriteTimeout() const override;

		virtual const Socket& GetSocket() const;

		virtual void SetLength(const Elysium::Core::size Value) override;
		virtual void SetPosition(const Elysium::Core::uint64_t  Position) override;
		virtual void SetReadTimeout(const Elysium::Core::uint32_t Value) override;
		virtual void SetWriteTimeout(const Elysium::Core::uint32_t Value) override;

		virtual void Close()  override;
		virtual void Flush() override;
		virtual const Elysium::Core::size Seek(const __int64 Offset, const Elysium::Core::IO::SeekOrigin Origin) override;
		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
	private:
		Socket& _Socket;
		bool _OwnsSocket;
	};
}
#endif
