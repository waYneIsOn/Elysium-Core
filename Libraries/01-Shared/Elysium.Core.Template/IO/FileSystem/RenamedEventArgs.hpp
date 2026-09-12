/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_RENAMEDEVENTARGS
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_RENAMEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMEVENTARGS
#include "FileSystemEventArgs.hpp"
#endif

namespace Elysium::Core::Template::IO::FileSystem
{
	template <class = void>
	class FileSystemWatcher;

	template <class = void>
	class RenamedEventArgs
		: public FileSystemEventArgs<>
	{
		friend class FileSystemWatcher<>;
	public:
		constexpr RenamedEventArgs() = delete;
	protected:
		inline constexpr RenamedEventArgs(const Elysium::Core::Template::IO::FileSystem::WatcherChangeTypes ChangeType, Elysium::Core::Template::Text::String<char8_t>&& FullPath,
			Elysium::Core::Template::Text::String<char8_t>&& Name, Elysium::Core::Template::Text::String<char8_t>&& OldName)
			: Elysium::Core::Template::IO::FileSystem::FileSystemEventArgs<>(ChangeType, Elysium::Core::Template::Functional::Move(FullPath), Elysium::Core::Template::Functional::Move(Name)),
			_OldName(Elysium::Core::Template::Functional::Move(OldName))
		{ }
	public:
		constexpr RenamedEventArgs(const RenamedEventArgs& Source) = delete;

		constexpr RenamedEventArgs(RenamedEventArgs&& Right) noexcept = delete;

		constexpr virtual ~RenamedEventArgs() = default;
	public:
		constexpr RenamedEventArgs& operator=(const RenamedEventArgs& Source) = delete;

		constexpr RenamedEventArgs& operator=(RenamedEventArgs&& Right) noexcept = delete;
	public:
		//inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetOldFullPath() const noexcept

		inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetOldName() const noexcept
		{
			return _OldName;
		}
	private:
		Elysium::Core::Template::Text::String<char8_t> _OldName;
	};
}
#endif
