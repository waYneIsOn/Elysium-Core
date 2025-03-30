#include "Command.hpp"

Elysium::Core::CommandLine::Command::Command(const char8_t* Name, const char8_t* Description)
	: Elysium::Core::CommandLine::Symbol(Name, Description),
	_OptionsArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions::ArenaOptions(sizeof(Command) * 16, 1, false, false))
{ }

void Elysium::Core::CommandLine::Command::AddAlias(const char8_t* Alias)
{
	// @ToDo
}

void Elysium::Core::CommandLine::Command::Add(const Command& SubCommand)
{
	// @ToDo
}