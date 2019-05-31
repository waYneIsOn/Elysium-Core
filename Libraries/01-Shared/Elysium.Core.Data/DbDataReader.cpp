#include "DbDataReader.hpp"

unsigned long Elysium::Core::Data::Common::DbDataReader::GetDepth() const
{
	return _NumberOfRows;
}
unsigned long Elysium::Core::Data::Common::DbDataReader::GetFieldCount() const
{
	return _FieldCount;
}

long Elysium::Core::Data::Common::DbDataReader::GetRecordsAffected() const
{
	return _RecordsAffected;
}

Elysium::Core::Data::Common::DbDataReader::DbDataReader(unsigned long NumberOfRows, unsigned long FieldCount, long RecordsAffected)
	: IDataReader(),
	_NumberOfRows(NumberOfRows), _FieldCount(FieldCount), _RecordsAffected(RecordsAffected)
{
}
Elysium::Core::Data::Common::DbDataReader::DbDataReader()
	: Elysium::Core::Data::Common::DbDataReader::DbDataReader(0, 0, -1)
{
}
