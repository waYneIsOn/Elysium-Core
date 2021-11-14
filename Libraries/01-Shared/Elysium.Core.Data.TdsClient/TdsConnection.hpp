/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_TDSCLIENT
#define ELYSIUM_CORE_DATA_TDSCLIENT_TDSCLIENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBCONNECTION
#include "../Elysium.Core.Data/DbConnection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_TDSVERSION
#include "TdsVersion.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "../Elysium.Core.Net/Socket.hpp"
#endif

namespace Elysium::Core::Data::TdsClient
{
	class ELYSIUM_CORE_DATA_TDSCLIENT_API TdsConnection final : public Common::DbConnection
	{
	public:
		TdsConnection(const TdsVersion Version, const Elysium::Core::String& ConnectionString, const Elysium::Core::uint32_t ConnectionTimeout);

		TdsConnection(const TdsConnection& Source) = delete;

		TdsConnection(TdsConnection&& Right) noexcept = delete;

		virtual ~TdsConnection();
	public:
		TdsConnection& operator=(const TdsConnection& Source) = delete;

		TdsConnection& operator=(TdsConnection&& Right) noexcept = delete;
	public:

	public:
		virtual void Open() override;

		virtual void Close() override;
		
		virtual Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbTransaction> BeginTransaction() override;

		virtual Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbTransaction> BeginTransaction(IsolationLevel IsolationLevel) override;

		virtual Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbCommand> CreateCommand() override;
		
		virtual void ChangeDatabase(const String& DatabaseName) override;
	private:
		Elysium::Core::Net::Sockets::Socket _TransportSocket;
		//Elysium::Core::uint16_t _PacketId;
	};
}
#endif
