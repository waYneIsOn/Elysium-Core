#include "SqlNativeError.hpp"

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::SqlNativeError(long ErrorSpecificErrorCode, unsigned long ProviderSpecificErrorCode, GUID ClassId, GUID InterfaceId, long DisplayId,
	wchar_t* Description, GUID GUID, unsigned long HelpContext, wchar_t* HelpFile, wchar_t* Source,
	wchar_t* SqlState, long ErrorCode, wchar_t* SSError, wchar_t* Server, wchar_t* Procedure, long Number, byte State, byte ErrorSeverity, unsigned short LineNumber)
	: _ErrorSpecificErrorCode(ErrorSpecificErrorCode),
	_ProviderSpecificErrorCode(ProviderSpecificErrorCode),
	_ClassId(ClassId),
	_InterfaceId(InterfaceId),
	_DisplayId(DisplayId),
	_Description(Description),
	_GUID(GUID),
	_HelpContext(HelpContext),
	_HelpFile(HelpFile == nullptr ? L"" : HelpFile),
	_Source(Source),
	_SqlState(SqlState == nullptr ? L"" : SqlState),
	_ErrorCode(ErrorCode),
	_SSError(SSError == nullptr ? L"" : SSError),
	_Server(Server == nullptr ? L"" : Server),
	_Procedure(Procedure == nullptr ? L"" : Procedure),
	_Number(Number),
	_State(State),
	_ErrorSeverity(ErrorSeverity),
	_LineNumber(LineNumber)
{ }
Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::~SqlNativeError()
{ }

const long & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetErrorSpecificErrorCode() const
{
	return (long&)_ErrorSpecificErrorCode;
}
const unsigned long & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetProviderSpecificErrorCode() const
{
	return (unsigned long&)_ProviderSpecificErrorCode;
}
const GUID & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetClassId() const
{
	return (GUID&)_ClassId;
}
const GUID & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetInterfaceId() const
{
	return (GUID&)_InterfaceId;
}
const long & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetDisplayId() const
{
	return (long&)_DisplayId;
}

const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetDescription() const
{
	return (std::wstring&)_Description;
}
const GUID & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetGUID() const
{
	return (GUID&)_GUID;
}
const unsigned long & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetHelpContext() const
{
	return (unsigned long&)_HelpContext;
}
const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetHelpFile() const
{
	return (std::wstring&)_HelpFile;
}
const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetSource() const
{
	return (std::wstring&)_Source;
}

const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetSqlState() const
{
	return (std::wstring&)_SqlState;
}
const long & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetErrorCode() const
{
	return (long&)_ErrorCode;
}
const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetSSError() const
{
	return (std::wstring&)_SSError;
}
const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetServer() const
{
	return (std::wstring&)_Server;
}
const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetProcedure() const
{
	return (std::wstring&)_Procedure;
}
const long & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetNumber() const
{
	return (long&)_Number;
}
const Elysium::Core::byte & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetState() const
{
	return (byte&)_State;
}
const Elysium::Core::byte & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetErrorSeverity() const
{
	return (byte&)_ErrorSeverity;
}
const unsigned short & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::GetLineNumber() const
{
	return (unsigned short&)_LineNumber;
}
