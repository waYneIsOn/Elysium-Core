#include "DbConnection.hpp"

Elysium::Core::Data::Common::DbConnection::DbConnection()
	: IDbConnection(),
	_ConnectionState(ConnectionState::Closed)
{
}
Elysium::Core::Data::Common::DbConnection::DbConnection(std::wstring ConnectionString)
	: IDbConnection(),
	_ConnectionString(ConnectionString),
	_ConnectionState(ConnectionState::Closed)
{
}

const std::wstring & Elysium::Core::Data::Common::DbConnection::GetConnectionString() const
{
	return _ConnectionString;
}
const int & Elysium::Core::Data::Common::DbConnection::GetConnectionTimeout() const
{
	return _ConnectionTimeout;
}
const std::wstring & Elysium::Core::Data::Common::DbConnection::GetDatabase() const
{
	return _Database;
}
const Elysium::Core::Data::ConnectionState & Elysium::Core::Data::Common::DbConnection::GetState() const
{
	return _ConnectionState;
}

void Elysium::Core::Data::Common::DbConnection::SetConnectionString(std::wstring ConnectionString)
{
	_ConnectionString = ConnectionString;
}
