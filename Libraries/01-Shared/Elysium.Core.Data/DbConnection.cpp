#include "DbConnection.hpp"

Elysium::Core::Data::Common::DbConnection::DbConnection(const Elysium::Core::String& ConnectionString, const Elysium::Core::uint32_t ConnectionTimeout)
	: IDbConnection(),
	_ConnectionString(ConnectionString), _ConnectionTimeout(ConnectionTimeout), _Database(), _ConnectionState(ConnectionState::Closed)
{ }

Elysium::Core::Data::Common::DbConnection::~DbConnection()
{ }

const Elysium::Core::String & Elysium::Core::Data::Common::DbConnection::GetConnectionString() const
{
	return _ConnectionString;
}

const Elysium::Core::uint32_t& Elysium::Core::Data::Common::DbConnection::GetConnectionTimeout() const
{
	return _ConnectionTimeout;
}

const Elysium::Core::String & Elysium::Core::Data::Common::DbConnection::GetDatabase() const
{
	return _Database;
}

const Elysium::Core::Data::ConnectionState & Elysium::Core::Data::Common::DbConnection::GetState() const
{
	return _ConnectionState;
}

void Elysium::Core::Data::Common::DbConnection::SetConnectionString(const Elysium::Core::String & ConnectionString)
{
	_ConnectionString = ConnectionString;
}
