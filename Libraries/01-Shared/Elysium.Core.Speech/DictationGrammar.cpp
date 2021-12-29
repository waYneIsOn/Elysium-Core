#include "DictationGrammar.hpp"

Elysium::Core::Speech::Recognition::DictationGrammar::DictationGrammar()
	: DictationGrammar(u8"")
{ }

Elysium::Core::Speech::Recognition::DictationGrammar::DictationGrammar(const String& Topic)
	: Elysium::Core::Speech::Recognition::Grammar(),
	_Topic(Topic)
{ }

Elysium::Core::Speech::Recognition::DictationGrammar::~DictationGrammar()
{ }

void Elysium::Core::Speech::Recognition::DictationGrammar::SetDictationContext(const String & PrecedingText, const String & SubsequentText)
{
	throw 1;
}
