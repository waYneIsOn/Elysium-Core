#include "FileSystemWatcherAsyncResult.hpp"

#ifndef ELYSIUM_CORE_IO_FILESYSTEMWATCHER
#include "FileSystemWatcher.hpp"
#endif

Elysium::Core::IO::FileSystemWatcherAsyncResult::FileSystemWatcherAsyncResult(FileSystemWatcher& Watcher, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* AsyncState, const Elysium::Core::size Position, PTP_IO CompletionPortHandle)
	: Elysium::Core::Internal::AsyncResult(Callback, AsyncState, Position, CompletionPortHandle),
	_Watcher(Watcher), _BytesTransferred(0), _InformationBuffer()
{ }

Elysium::Core::IO::FileSystemWatcherAsyncResult::~FileSystemWatcherAsyncResult()
{ }

constexpr const Elysium::Core::IO::FileSystemWatcher& Elysium::Core::IO::FileSystemWatcherAsyncResult::GetWatcher() const
{
	return _Watcher;
}
