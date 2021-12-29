#include "DbCommand.hpp"

Elysium::Core::Data::Common::DbCommand::DbCommand(IDbConnection & Connection)
	: IDbCommand(),
	_Connection(Connection),
	_Transaction(nullptr)
{ }

Elysium::Core::Data::Common::DbCommand::DbCommand(IDbTransaction * Transaction)
	: IDbCommand(),
	_Connection(Transaction->GetConnection()),
	_Transaction(Transaction)
{ }

Elysium::Core::Data::Common::DbCommand::~DbCommand()
{ }

const Elysium::Core::Utf8String& Elysium::Core::Data::Common::DbCommand::GetCommandText() const
{
	return _Text;
}

const Elysium::Core::uint32_t & Elysium::Core::Data::Common::DbCommand::GetConnectionTimeout() const
{
	return _Timeout;
}

const Elysium::Core::Data::CommandType & Elysium::Core::Data::Common::DbCommand::GetCommandType() const
{
	return _Type;
}

void Elysium::Core::Data::Common::DbCommand::SetCommandText(const char8_t* CommandText)
{
	_Text = CommandText;
}

void Elysium::Core::Data::Common::DbCommand::SetCommandText(const Elysium::Core::Utf8String& CommandText)
{
	_Text = CommandText;
}

void Elysium::Core::Data::Common::DbCommand::SetConnectionTimeout(const Elysium::Core::uint32_t Timeout)
{
	_Timeout = Timeout;
}

void Elysium::Core::Data::Common::DbCommand::SetCommandType(CommandType Type)
{
	_Type = Type;
}
