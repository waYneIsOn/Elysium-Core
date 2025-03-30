#include "RootCommand.hpp"

const char8_t* Elysium::Core::CommandLine::RootCommand::_ExecutableName = u8"ExecutableName.exe";	// @ToDo

Elysium::Core::CommandLine::RootCommand::RootCommand(const char8_t* Description)
	: Elysium::Core::CommandLine::Command::Command(_ExecutableName, Description)
{ }
