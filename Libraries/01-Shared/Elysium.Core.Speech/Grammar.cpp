#include "Grammar.hpp"

Elysium::Core::Speech::Recognition::Grammar::Grammar()
	: _Name(u8"")
{ }

Elysium::Core::Speech::Recognition::Grammar::Grammar(const Utf8String& Path, const Utf8String& RuleName)
	:  _Name(u8"")
{ }

Elysium::Core::Speech::Recognition::Grammar::~Grammar()
{ }

const Elysium::Core::Utf8String& Elysium::Core::Speech::Recognition::Grammar::GetName() const
{
	return _Name;
}

void Elysium::Core::Speech::Recognition::Grammar::SetName(const Utf8String& Value)
{
	_Name = Value;
}
