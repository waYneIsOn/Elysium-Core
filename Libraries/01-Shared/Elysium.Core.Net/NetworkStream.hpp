/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#define ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "Socket.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				/// <summary>
				/// 
				/// </summary>
				class ELYSIUM_CORE_NET_API NetworkStream : public Elysium::Core::IO::Stream
				{
				public:
					// constructors & destructor
					NetworkStream(Socket* Socket);
					NetworkStream(Socket* Socket, bool OwnsSocket);
					~NetworkStream();

					// properties - getter
					virtual bool GetCanRead() const override;
					virtual bool GetCanSeek() const override;
					virtual bool GetCanTimeout() const override;
					virtual bool GetCanWrite() const override;

					virtual size_t GetLength() override;
					virtual __int64 GetPosition() override;
					virtual int GetReadTimeout() const override;
					virtual int GetWriteTimeout() const override;

					// properties - setter
					virtual void SetLength(size_t Value) override;
					virtual void SetPosition(__int64 Position) override;
					virtual void SetReadTimeout(int Value) override;
					virtual void SetWriteTimeout(int Value) override;

					// methods
					virtual void Close() override;
					virtual void Flush() override;
					virtual void Seek(const __int64 Offset, const Elysium::Core::IO::SeekOrigin Origin) override;
					virtual size_t Read(byte* Buffer, const size_t Count) override;
					virtual void Write(const byte* Buffer, const size_t Count) override;
				private:
					// fields
					Socket* _Socket;
					bool _OwnsSocket;
				};
			}
		}
	}
}
#endif
