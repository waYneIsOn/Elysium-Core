#include "FileSystemWatcherAsyncResult.hpp"

#ifndef ELYSIUM_CORE_IO_FILESYSTEMWATCHER
#include "FileSystemWatcher.hpp"
#endif

Elysium::Core::IO::FileSystemWatcherAsyncResult::FileSystemWatcherAsyncResult(const Elysium::Core::Template::System::size BufferSize, const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback, const void* AsyncState, const Elysium::Core::size Position, PTP_IO CompletionPortHandle)
	: Elysium::Core::Internal::AsyncResult(Callback, AsyncState, Position, CompletionPortHandle),
	_InformationBuffer(BufferSize), _BytesTransferred(0)
{ }
