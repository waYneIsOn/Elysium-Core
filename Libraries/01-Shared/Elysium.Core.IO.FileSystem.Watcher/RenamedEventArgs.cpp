#include "RenamedEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::RenamedEventArgs::RenamedEventArgs(const WatcherChangeTypes ChangeType, Utf8String&& FullPath, Utf8String&& Name, Utf8String&& OldName)
	: Elysium::Core::IO::FileSystemEventArgs(ChangeType, Elysium::Core::Template::Functional::Move(FullPath), Elysium::Core::Template::Functional::Move(Name)),
	_OldName(Elysium::Core::Template::Functional::Move(OldName))
{ }

Elysium::Core::IO::RenamedEventArgs::~RenamedEventArgs()
{ }

const Elysium::Core::Utf8String& Elysium::Core::IO::RenamedEventArgs::GetOldName() const
{
	return _OldName;
}
