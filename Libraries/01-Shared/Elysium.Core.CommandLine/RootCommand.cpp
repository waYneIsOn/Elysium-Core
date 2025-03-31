#include "RootCommand.hpp"

const char8_t* Elysium::Core::CommandLine::RootCommand::_ExecutableName = u8"ExecutableName.exe";	// @ToDo: Elysium::Core::Reflection::Assembly

Elysium::Core::CommandLine::RootCommand::RootCommand(const char8_t* Description)
	: Elysium::Core::CommandLine::Command::Command(_ExecutableName, Description),
	_CommandArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions::ArenaOptions(sizeof(Command) * 16, 1, false, false)),
	_ArgumentArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions::ArenaOptions(sizeof(Argument<void>) * 16, 1, false, false)),
	_OptionArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions::ArenaOptions(sizeof(Option<void>) * 16, 1, false, false))
{ }
