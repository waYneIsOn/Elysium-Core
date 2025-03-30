#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core.CommandLine/ArgumentDescriptor.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.CommandLine/Argument.hpp"
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
			RootCommand Root = RootCommand(nullptr);

			Command SudoCommand = Command(u8"sudo");

			Command AptGetCommand = Command(u8"apt-get");
			Command UpdateCommand = Command(u8"update");
			Command UpgradeCommand = Command(u8"upgrade");

			Command AptCommand = Command(u8"apt");
			Command ListCommand = Command(u8"list");
			Option<void> UpgradeableOption = Option<void>(u8"--upgradable");

			ListCommand.Add<void>(UpgradeableOption);
			AptCommand.Add(ListCommand);
			AptGetCommand.Add(UpdateCommand);
			AptGetCommand.Add(UpgradeCommand);
			SudoCommand.Add(AptCommand);
			SudoCommand.Add(AptGetCommand);
			Root.Add(SudoCommand);

			//Option<int> IntOption = Option<int>(u8"");
		}

		TEST_METHOD(zzzzsdfsdfdTests)
		{
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

			// define flag descriptors
			ArgumentDescriptor<void> HelpFlagDescriptor = ArgumentDescriptor<void>(u8"-h", u8"Help",
				u8"Lists all available arguments and their descriptions.");
			Assert::IsTrue(HelpFlagDescriptor.IsFlag());

			ArgumentDescriptor<void> InstallFlagDescriptor = ArgumentDescriptor<void>(u8"-i", u8"Install",
				u8"Starts the installation process of the service.");
			Assert::IsTrue(InstallFlagDescriptor.IsFlag());

			ArgumentDescriptor<void> UninstallFlagDescriptor = ArgumentDescriptor<void>(u8"-u", u8"Uninstall",
				u8"Starts the uninstallation process of the service.");
			Assert::IsTrue(UninstallFlagDescriptor.IsFlag());

			ArgumentDescriptor<bool> QuietFlagDescriptor = ArgumentDescriptor<bool>(u8"-q", u8"Quiet",
				u8"...");
			Assert::IsTrue(QuietFlagDescriptor.IsFlag());

			ArgumentDescriptor<void> ConsoleFlagDescriptor = ArgumentDescriptor<void>(u8"-c", u8"Console",
				u8"Runs the service as a normal console application.");
			Assert::IsTrue(ConsoleFlagDescriptor.IsFlag());

			ArgumentDescriptor<void> RequiredFlagDescriptor = ArgumentDescriptor<void>(u8"--rf", u8"RequiredFlag",
				u8"While a required flag makes no sense in the real world (as it should simple be set by the application), I still want to test it as well.",
				true);
			Assert::IsTrue(RequiredFlagDescriptor.IsFlag());

			// define arguments with a single value
			ArgumentDescriptor<Elysium::Core::Template::System::int8_t> ConfigFileDescriptor =
				ArgumentDescriptor<Elysium::Core::Template::System::int8_t>(u8"--cfg", u8"Config", u8"Defines the FQPN to the configuration file.");
			Assert::IsFalse(ConfigFileDescriptor.IsFlag());

			// define arguments with a multiple values
			ArgumentDescriptor<char*, char*> CopyFileDescriptor = ArgumentDescriptor<char*, char*>(u8"--cp", u8"Copy",
				u8"Copies given source file to given target.");
			//Assert::IsFalse(CopyFileDescriptor.IsFlag());


			// ...


			bool bla = false;
		}
	};
}
