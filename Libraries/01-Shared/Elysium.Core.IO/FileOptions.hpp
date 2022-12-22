/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILEOPTIONS
#define ELYSIUM_CORE_IO_FILEOPTIONS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class FileOptions : Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class FileOptions
#else
#error "undefined os"
#endif
	{
		None = 0x00000000,

		Readonly = 0x00000001,

		Hidden = 0x00000002,
		/*
		System = 0x00000004,

		Directory = 0x00000010,

		Archive = 0x00000020,

		Device = 0x00000040,

		Normal = 0x00000080,

		Temporary = 0x00000100,

		SparseFile = 0x00000200,

		ReparsePoint = 0x00000400,

		Compressed = 0x00000800,

		Offline = 0x00001000,

		NotContentIndexed = 0x00002000,

		Encrypted = 0x00004000,

		RandomAccess = 0x10000000,

		NoBuffering = 0x20000000,
		*/
		Asynchronous = 0x40000000,	// FILE_FLAG_OVERLAPPED
		
		Write_Through = 0x80000000,

		DeleteOnClose = 0x04000000,

		SequentialScan = 0x08000000,
		
		BackupSemantics = 0x02000000,	// FILE_FLAG_BACKUP_SEMANTICS
		/*
		PosixSemantics = 0x01000000,

		OpenReparsePoint = 0x00200000,

		OpenNoRecall = 0x00100000,

		FirstPipeInstance = 0x00080000,
		*/
	};

	inline FileOptions operator|(const FileOptions Left, const FileOptions Right)
	{
		return static_cast<FileOptions>(static_cast<Elysium::Core::uint32_t>(Left) | static_cast<Elysium::Core::uint32_t>(Right));
	}

	inline FileOptions operator&(const FileOptions Left, const FileOptions Right)
	{
		return static_cast<FileOptions>(static_cast<Elysium::Core::uint32_t>(Left) & static_cast<Elysium::Core::uint32_t>(Right));
	}
}
#endif
