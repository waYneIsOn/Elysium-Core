#include "FileSystemWatcher.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

Elysium::Core::IO::FileSystemWatcher::FileSystemWatcher(const Utf8String& Path)
	: _NotifyFilters(DefaultNotifyFilters), _IncludeSubdirectories(false),
	_Path(Path), _Filter(u8"*.*")
{ }

Elysium::Core::IO::FileSystemWatcher::FileSystemWatcher(const Utf8String& Path, const Utf8String& Filter)
	: _NotifyFilters(DefaultNotifyFilters), _IncludeSubdirectories(false),
	_Path(Path), _Filter(Filter)
{ }

Elysium::Core::IO::FileSystemWatcher::~FileSystemWatcher()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_DirectoryHandle != nullptr)
	{
		CloseHandle(_DirectoryHandle);
		_DirectoryHandle = nullptr;
	}
#else
#error "undefined os"
#endif
}

const Elysium::Core::Utf8String& Elysium::Core::IO::FileSystemWatcher::GetPath() const
{
	return _Path;
}

const Elysium::Core::Utf8String& Elysium::Core::IO::FileSystemWatcher::GetFilter() const
{
	return _Filter;
}

void Elysium::Core::IO::FileSystemWatcher::BeginInit()
{
	if (_DirectoryHandle != nullptr)
	{
		CloseHandle(_DirectoryHandle);
		_DirectoryHandle = nullptr;
	}

	// ToDo: cast -> encoding
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> WindowsPath = 
		Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&_Path[0], _Path.GetLength());
	_DirectoryHandle = FindFirstChangeNotificationA((char*)&WindowsPath[0], true, static_cast<DWORD>(_NotifyFilters));
}
