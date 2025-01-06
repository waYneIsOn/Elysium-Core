#include "SqlNativeError.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::SqlNativeError() 
	: _ErrorSpecificErrorCode(), _ProviderSpecificErrorCode(), _ClassId(), _InterfaceId(), _DisplayId(), _Description(), _GUID(), _HelpContext(),
	_HelpFile(), _Source(), _SqlState(), _ErrorCode(), _SSError(), _Server(), _Procedure(), _Number(), _State(), _ErrorSeverity(), _LineNumber()
{ }

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

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::SqlNativeError(const SqlNativeError & Source)
	: _ErrorSpecificErrorCode(Source._ErrorSpecificErrorCode), _ProviderSpecificErrorCode(Source._ProviderSpecificErrorCode), 
	_ClassId(Source._ClassId), _InterfaceId(Source._InterfaceId), _DisplayId(Source._DisplayId), _Description(Source._Description),
	_GUID(Source._GUID), _HelpContext(Source._HelpContext), _HelpFile(Source._HelpFile), _Source(Source._Source), _SqlState(Source._SqlState), 
	_ErrorCode(Source._ErrorCode), _SSError(Source._SSError), _Server(Source._Server), _Procedure(Source._Procedure), _Number(Source._Number),
	_State(Source._State), _ErrorSeverity(Source._ErrorSeverity), _LineNumber(Source._LineNumber)
{ }

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::SqlNativeError(SqlNativeError && Right) noexcept
	: _ErrorSpecificErrorCode(), _ProviderSpecificErrorCode(), _ClassId(), _InterfaceId(), _DisplayId(), _Description(), _GUID(), _HelpContext(),
	_HelpFile(), _Source(), _SqlState(), _ErrorCode(), _SSError(), _Server(), _Procedure(), _Number(), _State(), _ErrorSeverity(), _LineNumber()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::~SqlNativeError()
{ }

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError& Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::operator=(const SqlNativeError & Source)
{
	if (this != &Source)
	{
		_ErrorSpecificErrorCode = Source._ErrorSpecificErrorCode;
		_ProviderSpecificErrorCode = Source._ProviderSpecificErrorCode;
		_ClassId = Source._ClassId;
		_InterfaceId = Source._InterfaceId;
		_DisplayId = Source._DisplayId;
		_Description = Source._Description;
		_GUID = Source._GUID;
		_HelpContext = Source._HelpContext;
		_HelpFile = Source._HelpFile;
		_Source = Source._Source;
		_SqlState = Source._SqlState;
		_ErrorCode = Source._ErrorCode;
		_SSError = Source._SSError;
		_Server = Source._Server;
		_Procedure = Source._Procedure;
		_Number = Source._Number;
		_State = Source._State;
		_ErrorSeverity = Source._ErrorSeverity;
		_LineNumber = Source._LineNumber;
	}
	return *this;
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError& Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::operator=(SqlNativeError&& Right) noexcept
{
	if (this != &Right)
	{
		_ErrorSpecificErrorCode = Elysium::Core::Template::Functional::Move(Right._ErrorSpecificErrorCode);
		_ProviderSpecificErrorCode = Elysium::Core::Template::Functional::Move(Right._ProviderSpecificErrorCode);
		_ClassId = Elysium::Core::Template::Functional::Move(Right._ClassId);
		_InterfaceId = Elysium::Core::Template::Functional::Move(Right._InterfaceId);
		_DisplayId = Elysium::Core::Template::Functional::Move(Right._DisplayId);
		_Description = Elysium::Core::Template::Functional::Move(Right._Description);
		_GUID = Elysium::Core::Template::Functional::Move(Right._GUID);
		_HelpContext = Elysium::Core::Template::Functional::Move(Right._HelpContext);
		_HelpFile = Elysium::Core::Template::Functional::Move(Right._HelpFile);
		_Source = Elysium::Core::Template::Functional::Move(Right._Source);
		_SqlState = Elysium::Core::Template::Functional::Move(Right._SqlState);
		_ErrorCode = Elysium::Core::Template::Functional::Move(Right._ErrorCode);
		_SSError = Elysium::Core::Template::Functional::Move(Right._SSError);
		_Server = Elysium::Core::Template::Functional::Move(Right._Server);
		_Procedure = Elysium::Core::Template::Functional::Move(Right._Procedure);
		_Number = Elysium::Core::Template::Functional::Move(Right._Number);
		_State = Elysium::Core::Template::Functional::Move(Right._State);
		_ErrorSeverity = Elysium::Core::Template::Functional::Move(Right._ErrorSeverity);
		_LineNumber = Elysium::Core::Template::Functional::Move(Right._LineNumber);
	}
	return *this;
}

bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::operator==(const SqlNativeError& Other) const
{
	return false;
}

bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError::operator!=(const SqlNativeError& Other) const
{
	return false;
}

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
