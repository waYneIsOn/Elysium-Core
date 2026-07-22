#include "RootCommand.hpp"

Elysium::Core::CommandLine::RootCommand::RootCommand(const char8_t* Description)
	: Elysium::Core::CommandLine::Command::Command(*this, _ExecutableName, Description),
	_CommandArena(), _ArgumentArena(), _OptionArena()
{
	Command& HelpCommand = AddSubCommand(u8"--help", u8"Displays help for command line arguments.");
	HelpCommand.AddAlias(u8"-h");
	HelpCommand.AddAlias(u8"/h");
	HelpCommand.AddAlias(u8"-?");
	HelpCommand.AddAlias(u8"/?");

	Command& VersionCommand = AddSubCommand(u8"--version", u8"Displays version of current assembly");
	HelpCommand.AddAlias(u8"-v");
	HelpCommand.AddAlias(u8"/v");
}

Elysium::Core::CommandLine::RootCommand::~RootCommand() noexcept
{
	// Need to call these methods explicitly here or the arenas will run out of scope before the objects are destructed.
	CleanUpArguments();
	CleanupOptions();
	CleanUpSubCommands();
}
