#include "DbConnection.hpp"

const Elysium::Core::String & Elysium::Core::Data::Common::DbConnection::GetConnectionString() const
{
	return _ConnectionString;
}
const int & Elysium::Core::Data::Common::DbConnection::GetConnectionTimeout() const
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

Elysium::Core::Data::Common::DbConnection::DbConnection()
	: IDbConnection(),
	_ConnectionState(ConnectionState::Closed)
{
}
Elysium::Core::Data::Common::DbConnection::DbConnection(const Elysium::Core::String & ConnectionString)
	: IDbConnection(),
	_ConnectionString(ConnectionString),
	_ConnectionState(ConnectionState::Closed)
{
}
