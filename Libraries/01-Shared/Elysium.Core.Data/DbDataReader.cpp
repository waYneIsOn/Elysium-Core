#include "DbDataReader.hpp"

size_t Elysium::Core::Data::Common::DbDataReader::GetDepth() const
{
	return _NumberOfRows;
}
size_t Elysium::Core::Data::Common::DbDataReader::GetFieldCount() const
{
	return _FieldCount;
}

size_t Elysium::Core::Data::Common::DbDataReader::GetRecordsAffected() const
{
	return _RecordsAffected;
}

Elysium::Core::Data::Common::DbDataReader::DbDataReader(size_t NumberOfRows, size_t FieldCount, size_t RecordsAffected)
	: IDataReader(),
	_NumberOfRows(NumberOfRows), _FieldCount(FieldCount), _RecordsAffected(RecordsAffected)
{
}
Elysium::Core::Data::Common::DbDataReader::DbDataReader()
	: Elysium::Core::Data::Common::DbDataReader::DbDataReader(0, 0, -1)
{
}
