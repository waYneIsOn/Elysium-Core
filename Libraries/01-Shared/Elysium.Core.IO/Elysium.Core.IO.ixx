module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//import <Windows.h>;
#endif
#else
#error "unsupported os"
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef _NEW_
#include <new>
#endif

export module Elysium.Core.IO;

export
{
	/*
#ifndef ELYSIUM_CORE_IO_BINARYREADER
#include "BinaryReader.hpp"
#endif
	/*
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
#ifndef ELYSIUM_CORE_IO_DIRECTORY
#include "Directory.hpp"
#endif
	*/
}
