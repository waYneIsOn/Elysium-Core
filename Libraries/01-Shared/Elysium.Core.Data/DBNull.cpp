#include "DBNull.hpp"

// define static DBNull fields
const Elysium::Core::Data::DBNull Elysium::Core::Data::DBNull::_Value = DBNull::DBNull();

const Elysium::Core::Data::DBNull * Elysium::Core::Data::DBNull::Value()
{
	return &_Value;
}

Elysium::Core::Data::DBNull::DBNull()
{
}
Elysium::Core::Data::DBNull::DBNull(const DBNull & Source)
{
}
Elysium::Core::Data::DBNull::~DBNull()
{
}
