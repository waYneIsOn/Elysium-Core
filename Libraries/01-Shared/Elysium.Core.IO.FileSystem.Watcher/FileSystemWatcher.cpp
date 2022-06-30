#include "FileSystemWatcher.hpp"

Elysium::Core::IO::FileSystemWatcher::FileSystemWatcher(const Utf8String& Path)
	: _Path(Path), _Filter(u8"*.*")
{ }

Elysium::Core::IO::FileSystemWatcher::FileSystemWatcher(const Utf8String& Path, const Utf8String& Filter)
	: _Path(Path), _Filter(Filter)
{ }

Elysium::Core::IO::FileSystemWatcher::~FileSystemWatcher()
{ }
