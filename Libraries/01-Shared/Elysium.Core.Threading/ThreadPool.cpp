#include "ThreadPool.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

const Elysium::Core::Threading::ThreadPool Elysium::Core::Threading::ThreadPool::_Instance = Elysium::Core::Threading::ThreadPool();

const Elysium::Core::Threading::ThreadPool & Elysium::Core::Threading::ThreadPool::GetThreadPool()
{
	return _Instance;
}

Elysium::Core::Threading::ThreadPool::~ThreadPool()
{
}

Elysium::Core::Threading::ThreadPool::ThreadPool()
	//: _WorkerThreads(Elysium::Core::Collections::Template::List<Thread>(4)),
	//_IOThreads(Elysium::Core::Collections::Template::List<Thread>(4))
{
	
	//void (Elysium::Core::Threading::ThreadPool::*StartX)() = &RunWorker;
	//void (*Start)(void*) = this->RunWorker;

	//for (size_t i = 0; i < _WorkerThreads.GetCount(); i++)
	{
		//_WorkerThreads[i] = std::move(Thread(this->RunWorker));
		//_WorkerThreads[i] = Thread(Start);
	}
}

void Elysium::Core::Threading::ThreadPool::RunWorker()
{
}
void Elysium::Core::Threading::ThreadPool::RunIO()
{
}
