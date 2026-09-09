/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMEVENTARGS
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_WATCHERCHANGETYPES
#include "WatcherChangeTypes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../Text/StringView.hpp"
#endif

namespace Elysium::Core::Template::IO::FileSystem
{
	class FileSystemWatcher;
	
	class FileSystemEventArgs
	{
		friend class FileSystemWatcher;
	public:
		constexpr FileSystemEventArgs() = delete;
	protected:
		inline constexpr FileSystemEventArgs(const Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes ChangeType, 
			Elysium::Core::Template::Text::String<char8_t>&& FullPath, Elysium::Core::Template::Text::String<char8_t>&& Name)
			: _ChangeType(ChangeType), _FullPath(Elysium::Core::Template::Functional::Move(FullPath)), _Name(Elysium::Core::Template::Functional::Move(Name))
		{ }
	public:
		FileSystemEventArgs(const FileSystemEventArgs& Source) = delete;

		FileSystemEventArgs(FileSystemEventArgs&& Right) noexcept = delete;

		constexpr virtual ~FileSystemEventArgs() = default;
	public:
		FileSystemEventArgs& operator=(const FileSystemEventArgs& Source) = delete;

		FileSystemEventArgs& operator=(FileSystemEventArgs&& Right) noexcept = delete;
	public:
		inline const Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes GetChangeType() const noexcept
		{
			return _ChangeType;
		}

		inline const Elysium::Core::Template::Text::String<char8_t>& GetFullPath() const noexcept
		{
			return _FullPath;
		}

		inline const Elysium::Core::Template::Text::String<char8_t>& GetName() const noexcept
		{
			return _Name;
		}
	private:
		Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes _ChangeType;
		Elysium::Core::Template::Text::String<char8_t> _FullPath;
		Elysium::Core::Template::Text::String<char8_t> _Name;
	};
}
#endif
