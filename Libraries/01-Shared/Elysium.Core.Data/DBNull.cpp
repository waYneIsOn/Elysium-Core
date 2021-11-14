#include "DBNull.hpp"

const Elysium::Core::Data::DBNull Elysium::Core::Data::DBNull::_Value = DBNull();

Elysium::Core::Data::DBNull::DBNull()
{ }

Elysium::Core::Data::DBNull::~DBNull()
{ }

const Elysium::Core::Data::DBNull& Elysium::Core::Data::DBNull::GetValue()
{
	return _Value;
}
