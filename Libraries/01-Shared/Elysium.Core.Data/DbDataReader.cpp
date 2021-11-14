#include "DbDataReader.hpp"

Elysium::Core::Data::Common::DbDataReader::DbDataReader(const Elysium::Core::size NumberOfRows, const Elysium::Core::size FieldCount, const Elysium::Core::size RecordsAffected)
	: IDataReader(),
	_NumberOfRows(NumberOfRows), _FieldCount(FieldCount), _RecordsAffected(RecordsAffected)
{ }

Elysium::Core::Data::Common::DbDataReader::DbDataReader()
	: Elysium::Core::Data::Common::DbDataReader::DbDataReader(0, 0, -1)
{ }

Elysium::Core::Data::Common::DbDataReader::~DbDataReader()
{ }

const Elysium::Core::size Elysium::Core::Data::Common::DbDataReader::GetDepth() const
{
	return _NumberOfRows;
}

const Elysium::Core::size Elysium::Core::Data::Common::DbDataReader::GetFieldCount() const
{
	return _FieldCount;
}

const Elysium::Core::size Elysium::Core::Data::Common::DbDataReader::GetRecordsAffected() const
{
	return _RecordsAffected;
}
