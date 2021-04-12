#include "WindowFinder.hpp"

const void* Elysium::Core::Diagnostics::Internal::WindowFinder::GetMainWindowHandle(const Elysium::Core::uint32_t ProcessId)
{
	WindowHandleData HandleData = WindowHandleData();
	HandleData.ProcessId = ProcessId;
	HandleData.WindowHandle = nullptr;
	while (EnumWindows(GetMainWindowHandleCallback, (LPARAM)&HandleData))
	{ }

	return HandleData.WindowHandle;
}

Elysium::Core::int32_t Elysium::Core::Diagnostics::Internal::WindowFinder::GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter)
{
	WindowHandleData* HandleData = (WindowHandleData*)Parameter;

	unsigned long ProcessId;
	GetWindowThreadProcessId(WindowHandle, &ProcessId);
	if (HandleData->ProcessId != ProcessId || !IsMainWindow(WindowHandle))
	{
		return 1;
	}

	HandleData->WindowHandle = WindowHandle;
	return 0;
}

const bool Elysium::Core::Diagnostics::Internal::WindowFinder::IsMainWindow(HWND WindowHandle)
{
	return GetWindow(WindowHandle, GW_OWNER) == (HWND)0 && IsWindowVisible(WindowHandle);
}
