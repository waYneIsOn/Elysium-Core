#include "ThreadPool.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "Task.hpp"
#endif

Elysium::Core::Threading::ThreadPool::ThreadPool(const bool IsIOPool)
	: Elysium::Core::Threading::ThreadPool::ThreadPool(Environment::ProcessorCount() - 1, IsIOPool)
{ }
Elysium::Core::Threading::ThreadPool::ThreadPool(const size_t NumberOfThreads, const bool IsIOPool)
	: _IsIOPool(IsIOPool), _SomeSocketIOCompletionPortHandle(nullptr),
	_Ids(Elysium::Core::Collections::Template::Array<unsigned long>(NumberOfThreads)),
	_ThreadHandles(Elysium::Core::Collections::Template::Array<ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE>(NumberOfThreads)),
	_ShouldStop(false), _IsRunning(false)
{ }
Elysium::Core::Threading::ThreadPool::~ThreadPool()
{ 
	Stop();
}

const size_t Elysium::Core::Threading::ThreadPool::GetNumberOfThreads() const
{
	return _ThreadHandles.GetLength();
}

void Elysium::Core::Threading::ThreadPool::Start()
{
	if (_IsRunning)
	{
		return;
	}
	_ShouldStop = false;
	LPTHREAD_START_ROUTINE ThreadMainMethod = _IsIOPool ? (LPTHREAD_START_ROUTINE)IOThreadMain : (LPTHREAD_START_ROUTINE)WorkerThreadMain;
	for (size_t i = 0; i < _ThreadHandles.GetLength(); i++)
	{
		_ThreadHandles[i] = ELYSIUM_THREAD_CREATE(nullptr, 0, ThreadMainMethod, this, 0, nullptr);
	}
	_IsRunning = true;
}
void Elysium::Core::Threading::ThreadPool::Stop()
{
	if (_ShouldStop)
	{
		return;
	}
	_ShouldStop = true;
	if (_IsIOPool)
	{
		OVERLAPPED Overlapped = OVERLAPPED();
		ELYSIUM_IOCOMPLETIONPORT_POST_QUEUED_COMPLETION_STATUS(_SomeSocketIOCompletionPortHandle, 0, 0, &Overlapped);
	}
	ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_MULTIPLE_OBJECTS_EX(_ThreadHandles.GetLength(), &_ThreadHandles[0], true, INFINITE, false);
	_IsRunning = false;
}

const bool Elysium::Core::Threading::ThreadPool::BindIOCompletionCallback(const Elysium::Core::Net::Sockets::Socket & Socket)
{
	_SomeSocketIOCompletionPortHandle = (ELYSIUM_IOCOMPLETIONPORT_HANDLE)Socket._CompletionPort;

	return true;
	//return BindIOCompletionCallback((ELYSIUM_IOCOMPLETIONPORT_HANDLE)Socket._WinSocketHandle);
	//return BindIOCompletionCallback((ELYSIUM_IOCOMPLETIONPORT_HANDLE)Socket._CompletionPort);
}

void Elysium::Core::Threading::ThreadPool::WorkerThreadMain(ThreadPool & ThreadPool)
{
	while (!ThreadPool._ShouldStop)
	{
		// wait for available tasks
		ThreadPool._WorkQueue._WorkAvailable.WaitOne();

		// grab the next task and execute it
		Tasks::Task* NextTask = ThreadPool._WorkQueue.GetNextTask();
		if (NextTask != nullptr)
		{
			NextTask->RunSynchronously();
		}
	}
}

void Elysium::Core::Threading::ThreadPool::IOThreadMain(ThreadPool & ThreadPool)
{
	DWORD BytesTransferred = 0;
	DWORD SendBytes;
	DWORD RecvBytes;

	ULONG_PTR CompletionKey = 0;
	LPOVERLAPPED Overlapped;

	while (!ThreadPool._ShouldStop)
	{
		if (ELYSIUM_IOCOMPLETIONPORT_GET_QUEUED_COMPLETION_STATUS(ThreadPool._SomeSocketIOCompletionPortHandle, &BytesTransferred, &CompletionKey, &Overlapped, INFINITE) == 0)
		{	// ERROR
			int lkjasdf = 45;
		}
		else
		{	// SUCCESS
			Elysium::Core::IAsyncResult* AsyncResult = (Elysium::Core::IAsyncResult*)Overlapped->Pointer;
			if (AsyncResult != nullptr)
			{
				const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback = AsyncResult->GetCallback();
				Callback(AsyncResult);

				delete Overlapped;
			}
		}
	}
}

const bool Elysium::Core::Threading::ThreadPool::BindIOCompletionCallback(const ELYSIUM_IOCOMPLETIONPORT_HANDLE IOCompletionPortHandle)
{
	// ToDo: 2nd parameter = callback function
	return ELYSIUM_IOCOMPLETIONPORT_BIND_CALLBACK(IOCompletionPortHandle, nullptr, 0);
}
