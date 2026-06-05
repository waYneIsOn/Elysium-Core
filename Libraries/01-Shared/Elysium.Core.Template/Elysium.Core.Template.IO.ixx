module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os regarding filesystem"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEACCESS
#include "IO/FileAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEMODE
#include "IO/FileMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEOPTIONS
#include "IO/FileOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESHARE
#include "IO/FileShare.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM
#include "IO/FileSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_INOUTSTREAM
#include "IO/InOutStream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_INSTREAM
#include "IO/InStream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_OUTSTREAM
#include "IO/OutStream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_SEEKORIGIN
#include "IO/SeekOrigin.hpp"
#endif

export module Elysium.Core.Template.IO;

export
{
	using Elysium::Core::Template::IO::FileAccess;
	using Elysium::Core::Template::IO::FileMode;
	using Elysium::Core::Template::IO::FileOptions;
	using Elysium::Core::Template::IO::FileShare;
	using Elysium::Core::Template::IO::FileSystem;
	using Elysium::Core::Template::IO::InOutStream;
	using Elysium::Core::Template::IO::InStream;
	using Elysium::Core::Template::IO::OutStream;
	using Elysium::Core::Template::IO::SeekOrigin;
}
