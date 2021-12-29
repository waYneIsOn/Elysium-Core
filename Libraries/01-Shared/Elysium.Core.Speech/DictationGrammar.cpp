#include "DictationGrammar.hpp"

Elysium::Core::Speech::Recognition::DictationGrammar::DictationGrammar()
	: DictationGrammar(u8"")
{ }

Elysium::Core::Speech::Recognition::DictationGrammar::DictationGrammar(const Utf8String& Topic)
	: Elysium::Core::Speech::Recognition::Grammar(),
	_Topic(Topic)
{ }

Elysium::Core::Speech::Recognition::DictationGrammar::~DictationGrammar()
{ }

void Elysium::Core::Speech::Recognition::DictationGrammar::SetDictationContext(const Utf8String& PrecedingText, const Utf8String& SubsequentText)
{
	throw 1;
}
