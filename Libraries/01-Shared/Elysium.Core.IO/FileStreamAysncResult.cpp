#include "FileStreamAysncResult.hpp"

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../Elysium.Core.Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_INTERNAL_OSTHREADPOOL
#include "../Elysium.Core.Threading/OSThreadPool.hpp"
#endif

Elysium::Core::IO::FileStreamAsyncResult::FileStreamAsyncResult(FileStream& Stream, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* AsyncState, const Elysium::Core::size Position)
	: Elysium::Core::Internal::AsyncResult(Callback, AsyncState, Position, nullptr),
	_Stream(Stream), _BytesTransferred(0)
{ }

Elysium::Core::IO::FileStreamAsyncResult::~FileStreamAsyncResult()
{ }

Elysium::Core::IO::FileStream& Elysium::Core::IO::FileStreamAsyncResult::GetFileStream() const
{
	return _Stream;
}

const Elysium::Core::size Elysium::Core::IO::FileStreamAsyncResult::GetBytesTransferred() const
{
	return _BytesTransferred;
}
