#include "FileSystemEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::FileSystemEventArgs::FileSystemEventArgs(const WatcherChangeTypes ChangeType, Elysium::Core::Utf8String&& FullPath, Elysium::Core::Utf8String&& Name)
	: Elysium::Core::EventArgs(),
	_ChangeType(ChangeType), _FullPath(Elysium::Core::Template::Functional::Move(FullPath)), 
	_Name(Elysium::Core::Template::Functional::Move(Name))
{ }

Elysium::Core::IO::FileSystemEventArgs::~FileSystemEventArgs()
{ }

const Elysium::Core::IO::WatcherChangeTypes Elysium::Core::IO::FileSystemEventArgs::GetChangeType() const
{
	return _ChangeType;
}

const Elysium::Core::Utf8String& Elysium::Core::IO::FileSystemEventArgs::GetFullPath() const
{
	return _FullPath;
}

const Elysium::Core::Utf8String& Elysium::Core::IO::FileSystemEventArgs::GetName() const
{
	return _Name;
}
