#include "SqlNativeException.hpp"

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeException::SqlNativeException(const Elysium::Core::int32_t ErrorCode, IUnknown* ErrorObject)
	: Elysium::Core::Data::Common::DbException(ErrorCode),
	_Errors(SqlNativeErrorCollection(ErrorObject))
{ }
Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeException::~SqlNativeException()
{ }

const Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeException::GetErrors() const
{
	return _Errors;
}
