#include "DbTransaction.hpp"

const Elysium::Core::Data::IDbConnection & Elysium::Core::Data::Common::DbTransaction::GetConnection() const
{
	return _Connection;
}
const Elysium::Core::Data::IsolationLevel Elysium::Core::Data::Common::DbTransaction::GetIsolationLevel() const
{
	return _IsolationLevel;
}

Elysium::Core::Data::Common::DbTransaction::DbTransaction(IDbConnection & Connection, IsolationLevel IsolationLevel)
	: IDbTransaction(),
	_Connection(Connection), _IsolationLevel(IsolationLevel)
{ }
