#include "Command.hpp"

#ifndef ELYSIUM_CORE_COMMANDLINE_ROOTCOMMAND
#include "RootCommand.hpp"
#endif

Elysium::Core::CommandLine::Command::Command(RootCommand& RootCommand, const char8_t* Name, const char8_t* Description)
	: Elysium::Core::CommandLine::Symbol(Name, Description),
	_RootCommand(RootCommand), _Arguments(3), _Options(3), _SubCommands(3)
{ }

Elysium::Core::CommandLine::Command::~Command() noexcept
{ 
	CleanUpArguments();
	CleanupOptions();
	CleanUpSubCommands();
}

void Elysium::Core::CommandLine::Command::AddAlias(const char8_t* Alias)
{
	// @ToDo
}

Elysium::Core::CommandLine::Command& Elysium::Core::CommandLine::Command::AddSubCommand(const char8_t* Name, const char8_t* Description) noexcept
{
	void* AllocatedMemory = _RootCommand._CommandArena.Push(sizeof(Command));
	Command* SubCommand = ::new (AllocatedMemory) Command(_RootCommand, Name, Description);

	_SubCommands.Set(SubCommand->GetName(), SubCommand);
	
	return *SubCommand;
}

void Elysium::Core::CommandLine::Command::CleanUpArguments()
{
	for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Utf8String, IArgument*>::FIterator Iterator = _Arguments.GetBegin();
		Iterator != _Arguments.GetEnd(); ++Iterator)
	{
		Elysium::Core::Template::Container::LinkedListNode<
			Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, IArgument*>>*Node = *Iterator;
		Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, IArgument*>& Item = Node->GetItem();

		IArgument*& Value = Item.GetValue();
		Value->~IArgument();
	}

	_Arguments.Clear();
}

void Elysium::Core::CommandLine::Command::CleanupOptions()
{
	for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Utf8String, IOption*>::FIterator Iterator = _Options.GetBegin();
		Iterator != _Options.GetEnd(); ++Iterator)
	{
		Elysium::Core::Template::Container::LinkedListNode<
			Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, IOption*>>*Node = *Iterator;
		Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, IOption*>& Item = Node->GetItem();

		IOption*& Value = Item.GetValue();
		Value->~IOption();
	}

	_Options.Clear();
}

void Elysium::Core::CommandLine::Command::CleanUpSubCommands()
{
	for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Utf8String, Command*>::FIterator Iterator = _SubCommands.GetBegin();
		Iterator != _SubCommands.GetEnd(); ++Iterator)
	{
		Elysium::Core::Template::Container::LinkedListNode<
			Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, Command*>>*Node = *Iterator;
		Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, Command*>& Item = Node->GetItem();

		Command*& Value = Item.GetValue();
		Value->~Command();
	}

	_SubCommands.Clear();
}

void* Elysium::Core::CommandLine::Command::AllocatedMemoryForArgument(const Elysium::Core::Template::System::size Size)
{
	return _RootCommand._ArgumentArena.Push(Size);
}

void* Elysium::Core::CommandLine::Command::AllocatedMemoryForOption(const Elysium::Core::Template::System::size Size)
{
	return _RootCommand._OptionArena.Push(Size);
}