/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREAD
#define ELYSIUM_CORE_TEMPLATE_THREADING_THREAD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FUNCTION
#include "../Container/Function.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE
#include "../Tuple.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_FORWARD
#include "../Functional/Forward.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "../UniquePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INDEXSEQUENCE
#include "../Utility/IndexSequence.hpp"
#endif


#ifdef ELYSIUM_CORE_OS_WINDOWS
	#ifndef _INC_PROCESS
	#include <process.h>
	#endif

#undef Yield
#else
#error "unsupported os"
#endif

extern "C" 
{
	void __cdecl _Thrd_yield() noexcept;
}

namespace Elysium::Core::Template::Threading
{
	class Thread final
	{
	public:
		Thread() noexcept = default;

		Thread(const Thread& Source) = delete;

		Thread(Thread&& Right) noexcept = delete;

		~Thread() noexcept;
	public:
		Thread& operator=(const Thread& Source) = delete;

		Thread& operator=(Thread&& Right) noexcept = delete;
	public:
		//static const Elysium::Core::uint32_t GetCurrentThreadId();
	public:
		//const Elysium::Core::uint32_t GetThreadId() const;
	public:
		//static void Sleep(const TimeSpan& Timeout);

		static void Yield() noexcept;
	public:
		template <class... Args>
		void Start(Elysium::Core::Template::Container::Function<void(*)(Args...) noexcept>&& ThreadStart, Args... Parameters);
		
		template <Elysium::Core::Template::Concepts::CompositeType Type, class ...Args>
		void Start(Elysium::Core::Template::Container::Function<void(Type::*)(Args...) noexcept>&& ThreadStart, Type& Instance, Args... Parameters);
	public:
		void Join();
	private:
#ifdef ELYSIUM_CORE_OS_WINDOWS
		template <class FunctionType, class... Args>
		static DWORD StartInternally(void* Parameters) noexcept;

		/// <summary>
		/// Invokes given parameterless function.
		/// </summary>
		/// <typeparam name="FunctionType"></typeparam>
		/// <param name="Tuple"></param>
		template <class FunctionType>
		static void InvokeFunction(Elysium::Core::Template::Container::Tuple<FunctionType>& Tuple);

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <typeparam name="FunctionType"></typeparam>
		/// <typeparam name="...Index"></typeparam>
		/// <param name="Tuple"></param>
		/// <param name=""></param>
		template <class FunctionType, class... Args, Elysium::Core::Template::System::size... Index>
		static void InvokeFunction(Elysium::Core::Template::Container::Tuple<FunctionType, Args...>& Tuple, Elysium::Core::Template::Utility::IndexSequence<Index...>);
#endif
	private:
		unsigned long _ThreadId;

#ifdef ELYSIUM_CORE_OS_WINDOWS
		HANDLE _ThreadHandle;
#endif
	};

	inline Thread::~Thread() noexcept
	{
		Join();
	}

	inline void Elysium::Core::Template::Threading::Thread::Yield() noexcept
	{
		_Thrd_yield();
	}

	template <class... Args>
	inline void Elysium::Core::Template::Threading::Thread::Start(Elysium::Core::Template::Container::Function<void(*)(Args...) noexcept>&& ThreadStart, Args... Parameters)
	{
#ifdef ELYSIUM_CORE_OS_WINDOWS
		if (nullptr != _ThreadHandle)
		{
			return;
		}

		if(nullptr == ThreadStart._FunctionOrStaticMethod)
		{	// @ToDo:
			throw 1;
		}

		/*
		* As starting a thread from an instance method is slightly more complex than starting from a static method/free function
		* in the way I have written my classes (Thread and Function), please read the comment in the other Thread::Start(...) method
		* if it's unclear, what's happening here!
		*/

		using Tuple = Elysium::Core::Template::Container::Tuple<Elysium::Core::Template::Container::Function<void(*)(Args...) noexcept>, Args...>;

		Tuple* PackedParameters = new Tuple(Elysium::Core::Template::Functional::Move(ThreadStart),
			Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);

		_ThreadHandle = CreateThread(nullptr, 0,
			&StartInternally<Elysium::Core::Template::Container::Function<void(*)(Args...)noexcept>, Args...>,
			PackedParameters, 0, &_ThreadId);
#endif
	}

	template <Elysium::Core::Template::Concepts::CompositeType Type, class ...Args>
	inline void Elysium::Core::Template::Threading::Thread::Start(Elysium::Core::Template::Container::Function<void(Type::*)(Args...) noexcept>&& ThreadStart, Type& Instance, Args... Parameters)
	{
#ifdef ELYSIUM_CORE_OS_WINDOWS
		if (nullptr != _ThreadHandle)
		{
			return;
		}

		if (nullptr == ThreadStart._Method)
		{	// @ToDo:
			throw 1;
		}

		/*
		* Granted, I didn't have a lot of contiguous time working on this but looking at how long it took me to implement 
		* this particular "setup", the time I spent clearly sheds a light on my current knowledge of templates (or the lack thereof), 
		* meaning I should probably explain to my future self what's going on here ^^
		* - CreateThread(...) expects a function like so: DWORD SomeFunction(void*)
		* - I want to be able to use any function/static method like "void AnyFunction(WhateverArguments)" however.
		* - Also I want to be able to use any member-method like "void MyClass::AnyMethod(WhateverArguments)".
		* - To make up for the difference in return type and signatures, a wrapper/trampoline is required: StartInternally(...)!
		* - It has the "correct" signature and input (function + args) for the OS to be used to start a thread and the
		*	parameters - due to the "templated form" - inside of that static method can be used precisely as required.
		* - Since this wrapper does neither know about the return type (even though it could bc of limiting it to void) and 
		*	signature, nor the actual arguments, some consideration has to be taken about how to provide that input and make it usable:
		*		- ALL input (function, optionally instance and parmeters) need to be stored in a single "package" so it makes sense
		*		  to use Elysium::Core::Template::Container::Tuple<...> for it.
		*		- The first parameter of that tuple - the functiopn - needs to be callable no matter the signature.
		*		- Finally CreateThread(...) only tells the OS to start a thread but doesn't wait for that to actually happen.
		*		  Hence given input (function and parameters) need to be stored on the heap meaning it's
		*		  StartInternally(...)'s responsibility to clean up that data.
		*/

		using Tuple = Elysium::Core::Template::Container::Tuple<Elysium::Core::Template::Container::Function<void(Type::*)(Args...) noexcept>,
			Type&, Args...>;

		Tuple* PackedParameters = new Tuple(Elysium::Core::Template::Functional::Move(ThreadStart), 
			Elysium::Core::Template::Functional::Forward<Type&>(Instance),
			Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);

		// https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
		_ThreadHandle = CreateThread(nullptr, 0,
			&StartInternally<Elysium::Core::Template::Container::Function<void(Type::*)(Args...)noexcept>, Type&, Args...>,
			PackedParameters, 0, &_ThreadId);
#endif
	}

	inline void Elysium::Core::Template::Threading::Thread::Join()
	{
#ifdef ELYSIUM_CORE_OS_WINDOWS
		if (nullptr != _ThreadHandle)
		{
			//terminate();
			bool SignalReceived = WaitForSingleObject(_ThreadHandle, INFINITE) == WAIT_OBJECT_0;
			_ThreadHandle = nullptr;
		}
#endif
	}

#ifdef ELYSIUM_CORE_OS_WINDOWS
	template<class FunctionType, class ...Args>
	inline DWORD Thread::StartInternally(void* Parameters) noexcept
	{
		/*
		* Tuple contains the following elements:
		* - Elysium::Core::Template::Container::Function.
		* - [OPTIONALLY] A pointer to the instance of the method that should be called.
		* - All parameters required to call the underlying function.
		*
		* Since I'm using Elysium::Core::Template::Container::Tuple<...> to wrap these values, I need to invoke the function
		* using a helper-function - Thread::InvokeFunction(...) - and an IndexSequence.
		*/

		using Tuple = Elysium::Core::Template::Container::Tuple<FunctionType, Args...>;

		Tuple* RawInput = static_cast<Tuple*>(Parameters);
		const Elysium::Core::Template::Memory::UniquePointer<Tuple> CleanUpInput = RawInput;
		
		if constexpr (sizeof...(Args) == 0)
		{
			InvokeFunction(*RawInput);
		}
		else if constexpr (sizeof...(Args) > 0)
		{
			InvokeFunction(*RawInput, Elysium::Core::Template::Utility::MakeIndexSequence<sizeof...(Args)>{});
		}
		else
		{	// Shouldn't ever happen but make sure to force an error regardless!
			static_assert(false, "Elysium::Core::Template::Threading::Thread::StartInternally(...): Negative number of parameters!");
		}
		
		return 0;
	}

	template<class FunctionType>
	inline void Thread::InvokeFunction(Elysium::Core::Template::Container::Tuple<FunctionType>& Tuple)
	{
		FunctionType& Function = Tuple.GetFirst();
		Function();
	}

	template<class FunctionType, class ...Args, Elysium::Core::Template::System::size ...Index>
	inline void Thread::InvokeFunction(Elysium::Core::Template::Container::Tuple<FunctionType, Args...>& Tuple,
		Elysium::Core::Template::Utility::IndexSequence<Index...>)
	{
		FunctionType& Function = Tuple.GetFirst();
		Function(Tuple.GetAt<Index + 1>()...);
	}
#endif
}
#endif
