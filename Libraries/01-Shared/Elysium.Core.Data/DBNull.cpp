#include "DBNull.hpp"

Elysium::Core::Data::DBNull::DBNull()
{ }

Elysium::Core::Data::DBNull::~DBNull()
{ }

const Elysium::Core::Data::DBNull& Elysium::Core::Data::DBNull::GetValue()
{
	static const DBNull Value = DBNull();
	return Value;
}
