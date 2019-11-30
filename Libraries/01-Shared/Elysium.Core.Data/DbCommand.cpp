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

const Elysium::Core::String& Elysium::Core::Data::Common::DbCommand::GetCommandText() const
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

void Elysium::Core::Data::Common::DbCommand::SetCommandText(const char16_t * CommandText)
{
	_Text = String(CommandText);
}
void Elysium::Core::Data::Common::DbCommand::SetCommandText(const Elysium::Core::String& CommandText)
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
