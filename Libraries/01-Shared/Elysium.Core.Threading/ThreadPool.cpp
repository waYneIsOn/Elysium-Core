#include "ThreadPool.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "Task.hpp"
#endif

Elysium::Core::Threading::ThreadPool::ThreadPool(const bool IsIOPool)
	: Elysium::Core::Threading::ThreadPool::ThreadPool(Environment::ProcessorCount() - 1, IsIOPool)
{ }
Elysium::Core::Threading::ThreadPool::ThreadPool(const size_t NumberOfThreads, const bool IsIOPool)
	: _IsIOPool(IsIOPool),
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
	ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_MULTIPLE_OBJECTS_EX(_ThreadHandles.GetLength(), &_ThreadHandles[0], true, INFINITE, false);
	_IsRunning = false;
}

const bool Elysium::Core::Threading::ThreadPool::BindIOCompletionCallback(const Elysium::Core::Net::Sockets::Socket & Socket)
{
	_IOCompletionPortHandle = (ELYSIUM_IOCOMPLETIONPORT_HANDLE)Socket._WinSocketHandle;

	return BindIOCompletionCallback((ELYSIUM_IOCOMPLETIONPORT_HANDLE)Socket._WinSocketHandle);
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
	DWORD BytesTransferred;
	DWORD SendBytes;
	DWORD RecvBytes;

	while (!ThreadPool._ShouldStop)
	{
		//ThreadPool._IOCompletionPortHandle
	}
}

const bool Elysium::Core::Threading::ThreadPool::BindIOCompletionCallback(const ELYSIUM_IOCOMPLETIONPORT_HANDLE IOCompletionPortHandle)
{
	// ToDo: 2nd parameter = callback function
	return ELYSIUM_IOCOMPLETIONPORT_BIND_CALLBACK(IOCompletionPortHandle, nullptr, 0);
}
