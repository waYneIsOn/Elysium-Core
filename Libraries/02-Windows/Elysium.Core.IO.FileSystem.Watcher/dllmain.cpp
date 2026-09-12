#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef ELYSIUM_CORE_IO_ERROREVENTARGS
#include "../../01-Shared/Elysium.Core.IO.FileSystem.Watcher/ErrorEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEMEVENTARGS
#include "../../01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemEventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEMWATCHER
#include "../../01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcher.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_RENAMEDEVENTARGS
#include "../../01-Shared/Elysium.Core.IO.FileSystem.Watcher/RenamedEventArgs.hpp"
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
