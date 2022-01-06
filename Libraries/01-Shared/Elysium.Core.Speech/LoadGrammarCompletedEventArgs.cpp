#include "LoadGrammarCompletedEventArgs.hpp"

Elysium::Core::Speech::Recognition::LoadGrammarCompletedEventArgs::LoadGrammarCompletedEventArgs(const Grammar& Grammar)
	: Elysium::Core::EventArgs(),
	_Grammar(Grammar)
{ }

Elysium::Core::Speech::Recognition::LoadGrammarCompletedEventArgs::~LoadGrammarCompletedEventArgs()
{ }

const Elysium::Core::Speech::Recognition::Grammar& Elysium::Core::Speech::Recognition::LoadGrammarCompletedEventArgs::GetGrammar() const
{
	return _Grammar;
}
