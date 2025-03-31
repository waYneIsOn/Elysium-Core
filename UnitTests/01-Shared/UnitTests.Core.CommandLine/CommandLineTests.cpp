#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core.CommandLine/Argument.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.CommandLine/ArgumentArity.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.CommandLine/Command.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.CommandLine/Option.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.CommandLine/RootCommand.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"

using namespace Elysium::Core::CommandLine;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::CommandLine
{
	TEST_CLASS(CommandLineTests)
	{
	public:
		TEST_METHOD(BlaTests)
		{
			RootCommand Root = RootCommand(u8"Runs application bla.exe");
			Command& SudoCommand = Root.AddSubCommand(u8"sudo");

			// bla.exe sudo -u "user@domain"
			Option<char8_t*> UsernameOption = Option<char8_t*>(u8"-u", u8"Represents the user the command is supposed to be executed as.");

			// bla.exe sudo 42 "foo bar"
			// @ToDo: global arguments????
			Argument<int> DelayArgument = Argument<int>(u8"delay", nullptr);	// 42
			Argument<char8_t*> MessageArgument = Argument<char8_t*>(u8"message", nullptr);	// "foo bar"

			// bla.exe sudo apt-get update
			// bla.exe sudo apt-get upgrade
			Command& AptGetCommand = SudoCommand.AddSubCommand(u8"apt-get", nullptr);
			Command& UpdateCommand = SudoCommand.AddSubCommand(u8"update", nullptr);
			Command& UpgradeCommand = SudoCommand.AddSubCommand(u8"upgrade", nullptr);

			/*
			// bla.exe sudo apt list --upgradable
			Command& AptCommand = SudoCommand.AddSubCommand(u8"apt", nullptr);
			Command& ListCommand = SudoCommand.AddSubCommand(u8"list", nullptr);
			Option<bool> UpgradeableOption = Option<bool>(u8"--upgradable");
			*/

			/*
			* @ToDo: Types
			*	- Commands
			*	- Subcommands
			*	- Options
			*	- Arguments
			*
			*	- Aliases (-i and --Install)
			*/

			/*
			* @ToDo: Handle all argument types
			*	- simple flag (-i) :: DONE (ArgumentDescriptor<void>)
			*	- Argument with singular value (--MaxThreads 5) :: DONE (ArgumentDescriptor<int>)
			*	- Argument with multiple values (--asfdd 5 bla 3.7f) :: DONE (ArgumentDescriptor<int, char*, float>)
			*	- Argument with optional values (--Optional/--Optional 5)
			*	- Argument with corresponding functionality (--Help -> List all defined argument descriptors)
			*		-> are there others that even make sense? --Help could be hardcoded
			*	- Argument occurring multiple times (-File xy.zip -File abc.zip)
			*
			* @ToDo: Handle "complex required"
			*	- Installation of an application does not require config-file, running the application does
			*		-> in this case it should be optional and handled by the application?
			*/

			/*
			* HashTable<char8_t*, ArgumentDescriptor<...>> _ArgumentMap:
			*	-h			-> HelpFlagDescriptor
			*	/h			-> HelpFlagDescriptor
			*	--Help		-> HelpFlagDescriptor
			*
			*	-i			-> InstallFlagDescriptor
			*	/i			-> InstallFlagDescriptor
			*	--Install	-> InstallFlagDescriptor
			*
			*	-u			-> UninstallFlagDescriptor
			*	/u			-> UninstallFlagDescriptor
			*	--Uninstall	-> UninstallFlagDescriptor
			*
			*	-c			-> ConsoleFlagDescriptor
			*
			*
			*/
		}
	};
}
