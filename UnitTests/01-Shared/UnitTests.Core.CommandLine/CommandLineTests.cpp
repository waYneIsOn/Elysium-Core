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
			/*
			CommandLine:
				MyApplication.exe --Silent true compress fast --SourceDirectory "../some folder" --TargetArchive "some.zip"
				MyApplication.exe compress fast --SourceDirectory "../some folder" 1024 --TargetArchive "some.zip" --Silent true

			- RootCommand "MyApplication.exe"
				- Global Option "--Silent" ("true" being it's Argument (=value?))
				- Command "compress"
					- Command "fast"
					- Option for compress "--SourceDirectory"
						- Argument<Utf8StringView> "../some folder"
					- Option for compress "--TargetArchive" ("some.zip" being it's  value).
						- Argument<Utf8StringView> "some.zip"
			*/
			RootCommand Root = RootCommand(u8"Runs application MyApplication.exe");

			Option<bool>& GlobalOptionSilent = Root.AddOption<bool>(u8"--Silent", u8"Runs the application in silent mode.");
			//GlobalOptionSilent.AddAlias()

			Command& SubCommandCompress = Root.AddSubCommand(u8"compress", u8"...");

			Option<Elysium::Core::Template::Text::StringView<char8_t>>& OptionSourceDirectory = 
				SubCommandCompress.AddOption<Elysium::Core::Template::Text::StringView<char8_t>>(u8"--SourceDirectory", u8"");
			OptionSourceDirectory.GetArity().SetMinimumNumberOfValues(1);
			OptionSourceDirectory.GetArity().SetMaximumNumberOfValues(1);
			
			Option<Elysium::Core::Template::Text::StringView<char8_t>>& OptionTargetArchive =
				SubCommandCompress.AddOption<Elysium::Core::Template::Text::StringView<char8_t>>(u8"--TargetArchive", u8"");
			OptionTargetArchive.GetArity().SetMinimumNumberOfValues(1);
			OptionTargetArchive.GetArity().SetMaximumNumberOfValues(1);

			Command& CommandCompressionStrengthFast = SubCommandCompress.AddSubCommand(u8"fast", u8"...");
			Command& CommandCompressionStrengthNormal = SubCommandCompress.AddSubCommand(u8"normal", u8"...");
			Command& CommandCompressionStrengthOptimal = SubCommandCompress.AddSubCommand(u8"optimal", u8"...");
			


			Argument<bool>& TestArg = SubCommandCompress.AddArgument<bool>(u8"test");











			/*
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
			*/
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
			*/
		}
	private:
		void PrepareGenericService()
		{
			RootCommand Root = RootCommand(u8"Runs service MyService.exe");
			Command& InstallCommand = Root.AddSubCommand(u8"--install", u8"Runs the installation process.");
			InstallCommand.AddAlias(u8"-i");
			InstallCommand.AddAlias(u8"/i");

			Command& UninstallCommand = Root.AddSubCommand(u8"--uninstall", u8"Runs the uninstallation process.");
			UninstallCommand.AddAlias(u8"-u");
			UninstallCommand.AddAlias(u8"/u");

			Command& ConsoleCommand = Root.AddSubCommand(u8"--console", u8"Runs the service as a normal console application.");
			ConsoleCommand.AddAlias(u8"-c");
			ConsoleCommand.AddAlias(u8"/c");

			Command& Dunno = ConsoleCommand.AddSubCommand(u8"--bla", u8"...");

			//return Root;
		}
		
	private:
		//RootCommand _Root;
	};
}
