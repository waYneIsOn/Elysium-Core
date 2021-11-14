#include "TdsConnection.hpp"

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "../Elysium.Core/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_TDSCONNECTIONSTRINGBUILDER
#include "TdsConnectionStringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "../Elysium.Core.Net/SocketException.hpp"
#endif

Elysium::Core::Data::TdsClient::TdsConnection::TdsConnection(const TdsVersion Version, const Elysium::Core::String& ConnectionString, const Elysium::Core::uint32_t ConnectionTimeout)
	: DbConnection(ConnectionString, ConnectionTimeout),
	_TransportSocket(Net::Sockets::AddressFamily::InterNetwork, Net::Sockets::SocketType::Stream, Net::Sockets::ProtocolType::Tcp)
{ }

Elysium::Core::Data::TdsClient::TdsConnection::~TdsConnection()
{ }

void Elysium::Core::Data::TdsClient::TdsConnection::Open()
{
	if (_ConnectionState == ConnectionState::Closed)
	{
		try
		{
			TdsConnectionStringBuilder ConnectionStringBuilder = TdsConnectionStringBuilder();
			ConnectionStringBuilder.SetConnectionString(_ConnectionString);

			const String& Server = ConnectionStringBuilder.GetServer();
			const Elysium::Core::size IndexOfPort = Server.IndexOf(u8',');
			const StringView Host = IndexOfPort == -1 ? StringView(Server) : StringView(Server, IndexOfPort);
			const Elysium::Core::uint16_t Port = IndexOfPort == -1 ? 1433 : Convert::ToUInt16(&Server[IndexOfPort + 1], 10);

			_ConnectionState = ConnectionState::Connecting;
			_TransportSocket.Connect(Host, Port);

			if (ConnectionStringBuilder.GetIsTrustedConnection())
			{

			}
			else
			{

			}

			/*
			// ...
			Elysium::Core::byte PreLoginRequest[47] = { 
				0x12, 0x01, 0x00, 0x2F, 0x00, 0x00, 0x01, 0x00, 
				0x00, 0x00, 0x1A, 0x00, 0x06, 0x01, 0x00, 0x20, 0x00, 0x01, 0x02, 0x00, 0x21, 0x00, 0x01, 0x03, 
				0x00, 0x22, 0x00, 0x04, 0x04, 0x00, 0x26, 0x00, 0x01, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x01, 0x00, 0xB8, 0x0D, 0x00, 0x00, 0x01 };
			//PreLoginRequest[0] = 0x12;	// Type
			//PreLoginRequest[1] = 0x00;	// Status
			// [2] & [3]	// Length
			// [4] & [5]	// SPID
			// [6]	// PacketId
			// [7]	// Window
			const Elysium::Core::size BytesSent = _TransportSocket.Send(&PreLoginRequest[0], 47);

			Elysium::Core::byte Buffer[1024];
			const Elysium::Core::size BytesReceived = _TransportSocket.Receive(&Buffer[0], 1024);
			*/
			_ConnectionState = ConnectionState::Open;
		}
		catch (Net::Sockets::SocketException& Ex)
		{
			_ConnectionState = ConnectionState::Broken;
			throw Ex;
		}
	}
}

void Elysium::Core::Data::TdsClient::TdsConnection::Close()
{
	if (_ConnectionState == ConnectionState::Closed)
	{
		_TransportSocket.Close();
		_ConnectionState = ConnectionState::Closed;
	}
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbTransaction> Elysium::Core::Data::TdsClient::TdsConnection::BeginTransaction()
{
	throw 1;
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbTransaction> Elysium::Core::Data::TdsClient::TdsConnection::BeginTransaction(IsolationLevel IsolationLevel)
{
	throw 1;
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbCommand> Elysium::Core::Data::TdsClient::TdsConnection::CreateCommand()
{
	throw 1;
}

void Elysium::Core::Data::TdsClient::TdsConnection::ChangeDatabase(const String& DatabaseName)
{
	throw 1;
}
