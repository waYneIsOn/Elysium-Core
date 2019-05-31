#include "DbCommand.hpp"

Elysium::Core::Data::Common::DbCommand::DbCommand(IDbConnection * Connection)
	: IDbCommand(),
	_Connection(Connection),
	_Transaction(nullptr)
{
}
Elysium::Core::Data::Common::DbCommand::DbCommand(IDbTransaction * Transaction)
	: IDbCommand(),
	_Connection(Transaction->GetConnection()),
	_Transaction(Transaction)
{
}

const std::wstring Elysium::Core::Data::Common::DbCommand::GetCommandText() const
{
	return _Text;
}
const int & Elysium::Core::Data::Common::DbCommand::GetConnectionTimeout() const
{
	return _Timeout;
}
const Elysium::Core::Data::CommandType & Elysium::Core::Data::Common::DbCommand::GetCommandType() const
{
	return _Type;
}

void Elysium::Core::Data::Common::DbCommand::SetCommandText(std::wstring CommandText)
{
	_Text = CommandText;
}
void Elysium::Core::Data::Common::DbCommand::SetConnectionTimeout(int Timeout)
{
	_Timeout = Timeout;
}
void Elysium::Core::Data::Common::DbCommand::SetCommandType(CommandType Type)
{
	_Type = Type;
}
