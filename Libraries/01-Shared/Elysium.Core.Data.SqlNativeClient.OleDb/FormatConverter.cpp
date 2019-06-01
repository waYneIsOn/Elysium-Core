#include "FormatConverter.hpp"

#ifndef RC_INVOKED
#include <stdint.h>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif
/*
long Elysium::Core::Data::SqlNativeClient::OleDb::FormatConverter::Translate(IsolationLevel IsolationLevel)
{
	switch (IsolationLevel)
	{
	case Elysium::Core::Data::IsolationLevel::Unspecified:
		return 0xffffffff;
	case Elysium::Core::Data::IsolationLevel::Chaos:
		return 0x10;	// DBPROPVAL_TI_CHAOS?
	case Elysium::Core::Data::IsolationLevel::ReadUncommitted:
		return 0x100;
	case Elysium::Core::Data::IsolationLevel::ReadCommitted:
		return 0x1000;
	case Elysium::Core::Data::IsolationLevel::RepeatableRead:
		return 0x10000;
	case Elysium::Core::Data::IsolationLevel::Serializable:
		return 0x100000;
	case Elysium::Core::Data::IsolationLevel::Snapshot:
		throw NotImplementedException("unhandled IsolationLevel 'Snapshot': might be 0x1000 (ISOLATIONLEVEL_CURSORSTABILITY) or 0x100000 (ISOLATIONLEVEL_ISOLATED)");
	default:
		throw NotImplementedException("unhandled IsolationLevel");
	}
}
*/
DBTYPEENUM Elysium::Core::Data::SqlNativeClient::OleDb::FormatConverter::Translate(DbType DbType)
{
	// https://docs.microsoft.com/en-us/dotnet/framework/data/adonet/ole-db-data-type-mappings
	switch (DbType)
	{
	case Elysium::Core::Data::DbType::AnsiString:
		return DBTYPE_STR;
	case Elysium::Core::Data::DbType::Binary:
		return DBTYPE_IUNKNOWN;
	case Elysium::Core::Data::DbType::Byte:
		return DBTYPE_BYTES;
	case Elysium::Core::Data::DbType::Boolean:
		return DBTYPE_BOOL;
		/*
	case Elysium::Core::Data::DbType::Currency:
		return DBTYPE_;
		*/
	case Elysium::Core::Data::DbType::Date:
		return DBTYPE_DBDATE;
	case Elysium::Core::Data::DbType::DateTime:
		return DBTYPE_DBTIMESTAMP;
	case Elysium::Core::Data::DbType::Decimal:
		return DBTYPE_NUMERIC;
	case Elysium::Core::Data::DbType::Double:
		return DBTYPE_R8;
	case Elysium::Core::Data::DbType::Guid:
		return DBTYPE_GUID;
	case Elysium::Core::Data::DbType::Int16:
		return DBTYPE_I2;
	case Elysium::Core::Data::DbType::Int32:
		return DBTYPE_I4;
	case Elysium::Core::Data::DbType::Int64:
		return DBTYPE_I8;
		/*
	case Elysium::Core::Data::DbType::Object:
	case Elysium::Core::Data::DbType::SByte:
		return DBTYPE_;
		*/
	case Elysium::Core::Data::DbType::Single:
		return DBTYPE_R4;
	case Elysium::Core::Data::DbType::String:
		return DBTYPE_WSTR;
	case Elysium::Core::Data::DbType::Time:
		return DBTYPE_DBTIME2;
	case Elysium::Core::Data::DbType::UInt16:
		return DBTYPE_UI1;	// tinyint
		/*
	case Elysium::Core::Data::DbType::UInt32:
		return DBTYPE_;
	case Elysium::Core::Data::DbType::UInt64:
		return DBTYPE_;
	case Elysium::Core::Data::DbType::VarNumeric:
		return DBTYPE_;
	case Elysium::Core::Data::DbType::AnsiStringFixedLength:
		return DBTYPE_;
	case Elysium::Core::Data::DbType::StringFixedLength:
		return DBTYPE_;
	case Elysium::Core::Data::DbType::Xml:
		return DBTYPE_;
		*/
	case Elysium::Core::Data::DbType::DateTime2:
		return DBTYPE_DBTIMESTAMP;
	case Elysium::Core::Data::DbType::DateTimeOffset:
		return DBTYPE_DBTIMESTAMPOFFSET;
	default:
		throw NotImplementedException(L"unhandled DbType in DBTYPEENUM Elysium::Core::Data::SqlNativeClient::OleDb::FormatConverter::Translate(DbType DbType)");
	}
}

DBPARAMIOENUM Elysium::Core::Data::SqlNativeClient::OleDb::FormatConverter::Translate(ParameterDirection ParameterDirection)
{
	switch (ParameterDirection)
	{
	case ParameterDirection::Input:
		return DBPARAMIO_INPUT;
	case ParameterDirection::Output:
		return DBPARAMIO_OUTPUT;
		/*
	case ParameterDirection::InputOutput:
		return DBPARAMIO_INPUT | DBPARAMIO_OUTPUT;
	case ParameterDirection::ReturnValue:
		return DBPARAMIO_OUTPUT;
		*/
	default:
		throw NotImplementedException(L"unhandled ParameterDirection in DBPARAMIOENUM Elysium::Core::Data::SqlNativeClient::OleDb::FormatConverter::Translate(ParameterDirection ParameterDirection)");
	}
}

Elysium::Core::Data::SqlNativeClient::OleDb::FormatConverter::FormatConverter()
{
}
Elysium::Core::Data::SqlNativeClient::OleDb::FormatConverter::~FormatConverter()
{
}
