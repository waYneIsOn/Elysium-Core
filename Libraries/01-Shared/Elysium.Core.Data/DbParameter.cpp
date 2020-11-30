#include "DbParameter.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

const Elysium::Core::Data::DbType Elysium::Core::Data::Common::DbParameter::GetDbType() const
{
	return _DbType;
}

const Elysium::Core::Data::ParameterDirection Elysium::Core::Data::Common::DbParameter::GetDirection() const
{
	return _Direction;
}

const bool Elysium::Core::Data::Common::DbParameter::GetIsNullable() const
{
	return _IsNullable;
}

const Elysium::Core::String Elysium::Core::Data::Common::DbParameter::GetParameterName() const
{
	return _ParameterName;
}

const Elysium::Core::String Elysium::Core::Data::Common::DbParameter::GetSourceColumn() const
{
	return _SourceColumn;
}

const Elysium::Core::Data::DataRowVersion Elysium::Core::Data::Common::DbParameter::GetSourceVersion() const
{
	return _SourceVersion;
}

const Elysium::Core::byte * Elysium::Core::Data::Common::DbParameter::GetValue() const
{
	return _Data.data();
}

const size_t Elysium::Core::Data::Common::DbParameter::GetSize() const
{
	return _Data.size();
}

const bool Elysium::Core::Data::Common::DbParameter::GetIsDBNull() const
{
	return (_DBNullPointer != nullptr);
}

void Elysium::Core::Data::Common::DbParameter::SetDbType(const DbType Type)
{
	_DbType = Type;
}
void Elysium::Core::Data::Common::DbParameter::SetDirection(const ParameterDirection Direction)
{
	_Direction = Direction;
}
void Elysium::Core::Data::Common::DbParameter::SetIsNullable(const bool IsNullable)
{
	_IsNullable = IsNullable;
}
void Elysium::Core::Data::Common::DbParameter::SetParameterName(const Elysium::Core::String & ParameterName)
{
	_ParameterName = ParameterName;
}
void Elysium::Core::Data::Common::DbParameter::SetSourceColumn(const Elysium::Core::String& SourceColumn)
{
	_SourceColumn = SourceColumn;
}
void Elysium::Core::Data::Common::DbParameter::SetSourceVersion(const DataRowVersion Version)
{
	_SourceVersion = Version;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const DBNull & Value)
{
	_DBNullPointer = &Value;
	_DbType = DbType::Boolean;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const bool Value)
{
	size_t Size = sizeof(bool);
	_DbType = DbType::Boolean;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const byte Value)
{
	size_t Size = sizeof(byte);
	_DbType = DbType::Byte;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const byte * Value, const size_t Length)
{
	size_t Size = sizeof(byte) * Length;
	_DbType = DbType::Byte;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value[0], Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const char8_t Value)
{
	size_t Size = sizeof(char);
	_DbType = DbType::AnsiString;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const char8_t * Value, const size_t Length)
{
	size_t Size = sizeof(char) * Length;
	_DbType = DbType::AnsiString;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value[0], Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::String & Value)
{
	SetValue(&Value[0], Value.GetLength());
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const DateTime & Value)
{
	size_t Size = sizeof(DateTime);
	_DbType = DbType::DateTime;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const DateTimeOffset & Value)
{
	size_t Size = sizeof(DateTimeOffset);
	_DbType = DbType::DateTimeOffset;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const TimeSpan & Value)
{
	size_t Size = sizeof(TimeSpan);
	_DbType = DbType::Time;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Decimal & Value)
{
	size_t Size = sizeof(Elysium::Core::Decimal);
	_DbType = DbType::Decimal;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const double Value)
{
	size_t Size = sizeof(double);
	_DbType = DbType::Double;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const float Value)
{
	size_t Size = sizeof(float);
	_DbType = DbType::Single;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Guid& Value)
{
	size_t Size = sizeof(Guid);
	_DbType = DbType::Guid;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::int16_t Value)
{
	size_t Size = sizeof(__int16);
	_DbType = DbType::Int16;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::int32_t Value)
{
	size_t Size = sizeof(__int32);
	_DbType = DbType::Int32;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::int64_t Value)
{
	size_t Size = sizeof(__int64);
	_DbType = DbType::Int64;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::uint16_t Value)
{
	size_t Size = sizeof(unsigned __int16);
	_DbType = DbType::UInt16;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::uint32_t Value)
{
	size_t Size = sizeof(unsigned __int32);
	_DbType = DbType::UInt32;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::uint64_t Value)
{
	size_t Size = sizeof(unsigned __int64);
	_DbType = DbType::UInt64;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}
void Elysium::Core::Data::Common::DbParameter::SetValue(const Elysium::Core::IO::Stream & Value)
{
	size_t Size = sizeof(void*);
	_DbType = DbType::Binary;
	_Data.resize(Size);
	memcpy(&_Data[0], &Value, Size);
	_DBNullPointer = nullptr;
}

Elysium::Core::Data::Common::DbParameter::DbParameter(const DbCommand* Command)
	: Elysium::Core::Data::IDataParameter(),
	_Command(Command), _DbType(DbType::Binary), _SourceVersion(), _DBNullPointer(nullptr)
{ }
