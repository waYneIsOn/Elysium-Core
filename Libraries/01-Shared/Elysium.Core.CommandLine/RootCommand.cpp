#include "RootCommand.hpp"

const char8_t* Elysium::Core::CommandLine::RootCommand::_ExecutableName = 
	u8"ExecutableName.exe";	// @ToDo: Elysium::Core::Reflection::Assembly

const Elysium::Core::Version Elysium::Core::CommandLine::RootCommand::_Version =
	Elysium::Core::Version(0, 1);	// @ToDo: read from Elysium::Core::Reflection::Assembly -> AssemblyName

Elysium::Core::CommandLine::RootCommand::RootCommand(const char8_t* Description)
	: Elysium::Core::CommandLine::Command::Command(*this, _ExecutableName, Description),
	_CommandArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions::ArenaOptions(sizeof(Command) * 16, 1, false, false)),
	_ArgumentArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions::ArenaOptions(sizeof(Argument<void>) * 16, 1, false, false)),
	_OptionArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions::ArenaOptions(sizeof(Option<void>) * 16, 1, false, false))
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
