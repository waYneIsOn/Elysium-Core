#include "SqlNativeParameter.hpp"

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeParameter::~SqlNativeParameter()
{
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeParameter::SqlNativeParameter(const SqlNativeCommand * const Command)
	: Elysium::Core::Data::Common::DbParameter(Command)
{
}
