#include "FileSystemEventArgs.hpp"

Elysium::Core::IO::FileSystemEventArgs::FileSystemEventArgs(const WatcherChangeTypes ChangeType, const char8_t* FullPath, const char8_t* Name)
	: _ChangeType(ChangeType), _FullPath(FullPath), _Name(Name)
{ }

Elysium::Core::IO::FileSystemEventArgs::~FileSystemEventArgs()
{ }

const Elysium::Core::IO::WatcherChangeTypes Elysium::Core::IO::FileSystemEventArgs::GetChangeType() const
{
	return _ChangeType;
}

const Elysium::Core::Utf8String Elysium::Core::IO::FileSystemEventArgs::GetFullPath() const
{
	return _FullPath;
}

const Elysium::Core::Utf8String Elysium::Core::IO::FileSystemEventArgs::GetName() const
{
	return _Name;
}
