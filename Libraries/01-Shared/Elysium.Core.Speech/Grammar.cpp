#include "Grammar.hpp"

Elysium::Core::Speech::Recognition::Grammar::Grammar()
	: _Name(u8"")
{ }

Elysium::Core::Speech::Recognition::Grammar::Grammar(const String & Path)
	:  _Name(u8"")
{ }

Elysium::Core::Speech::Recognition::Grammar::~Grammar()
{ }

const Elysium::Core::String& Elysium::Core::Speech::Recognition::Grammar::GetName() const
{
	return _Name;
}

void Elysium::Core::Speech::Recognition::Grammar::SetName(const String& Value)
{
	_Name = Value;
}
