#include "String.hpp"

Elysium::Core::String::String(const ElysiumChar* Value)
	: _Length(0), _Data()
{
}
Elysium::Core::String::~String()
{
	delete(_Data);
}
