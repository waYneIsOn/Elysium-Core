#include "DbDataReader.hpp"

const size_t Elysium::Core::Data::Common::DbDataReader::GetDepth() const
{
	return _NumberOfRows;
}

const size_t Elysium::Core::Data::Common::DbDataReader::GetFieldCount() const
{
	return _FieldCount;
}

const size_t Elysium::Core::Data::Common::DbDataReader::GetRecordsAffected() const
{
	return _RecordsAffected;
}

Elysium::Core::Data::Common::DbDataReader::DbDataReader(const size_t NumberOfRows, const size_t FieldCount, const size_t RecordsAffected)
	: IDataReader(),
	_NumberOfRows(NumberOfRows), _FieldCount(FieldCount), _RecordsAffected(RecordsAffected)
{ }
Elysium::Core::Data::Common::DbDataReader::DbDataReader()
	: Elysium::Core::Data::Common::DbDataReader::DbDataReader(0, 0, -1)
{ }
