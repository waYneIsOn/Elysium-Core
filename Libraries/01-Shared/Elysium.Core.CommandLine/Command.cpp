#include "Command.hpp"

Elysium::Core::CommandLine::Command::Command(const char8_t* Name, const char8_t* Description)
	: Elysium::Core::CommandLine::Symbol(Name, Description)
{ }

void Elysium::Core::CommandLine::Command::AddAlias(const char8_t* Alias)
{
	// @ToDo
}

Elysium::Core::CommandLine::Command& Elysium::Core::CommandLine::Command::AddSubCommand(const char8_t* Name, const char8_t* Description) noexcept
{
	//return Command(Name, Description);
	throw 1;
}

void Elysium::Core::CommandLine::Command::Add(const Command& SubCommand)
{
	// @ToDo
}