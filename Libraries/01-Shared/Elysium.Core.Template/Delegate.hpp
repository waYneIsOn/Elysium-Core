/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core
{
	namespace Collections::Template
	{
		template <typename T>
		class List;
	}

	namespace Threading
	{
		class Thread;
	}
}

namespace Elysium::Core::Template::Container
{
	template <class ReturnType, class ...Args>
	class Delegate
	{
		friend class Collections::Template::List<Delegate<ReturnType, Args...>>;
		friend class Threading::Thread;
	private:
		Delegate();
	public:
		Delegate(const Delegate& Source);

		Delegate(Delegate&& Right) noexcept;

		~Delegate();
	public:
		Delegate& operator=(const Delegate& Source);

		Delegate& operator=(Delegate&& Right) noexcept;
	public:
		const bool operator==(const Delegate& Other);

		const bool operator!=(const Delegate& Other);

		ReturnType operator()(Args... Parameters) const;
	public:
		template <ReturnType(*ActualMethod)(Args...)>
		static Delegate Bind();

		template <class T, ReturnType(T::* ActualMethod)(Args...)>
		static Delegate Bind(T& Target);
	private:
		void* _Target;
		ReturnType(*_Method)(void* NonSpecificInstance, Args...);

		template<ReturnType(*ActualMethod)(Args...)>
		static ReturnType WrappedMethod(void* NullPointer, Args... Parameters);

		template<class T, ReturnType(T::* ActualMethod)(Args...)>
		static ReturnType WrappedMethod(void* NonSpecificInstance, Args... Parameters);
	};

	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>::Delegate()
		: _Target(nullptr), _Method(nullptr)
	{ }
	
	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>::Delegate(const Delegate& Source)
		: _Target(Source._Target), _Method(Source._Method)
	{ }

	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>::Delegate(Delegate&& Right) noexcept
		: _Target(nullptr), _Method(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>::~Delegate()
	{ }

	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>& Delegate<ReturnType, Args...>::operator=(const Delegate& Source)
	{
		if (this != &Source)
		{
			_Target = Source._Target;
			_Method = Source._Method;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>& Delegate<ReturnType, Args...>::operator=(Delegate&& Right) noexcept
	{
		if (this != &Right)
		{
			_Target = Elysium::Core::Template::Functional::Move(Right._Target);
			_Method = Elysium::Core::Template::Functional::Move(Right._Method);

			Right._Target = nullptr;
			Right._Method = nullptr;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline const bool Delegate<ReturnType, Args...>::operator==(const Delegate& Other)
	{
		return _Target == Other._Target && _Method == Other._Method;
	}

	template<class ReturnType, class ...Args>
	inline const bool Delegate<ReturnType, Args...>::operator!=(const Delegate& Other)
	{
		return _Target != Other._Target || _Method != Other._Method;
	}

	template<class ReturnType, class ...Args>
	inline ReturnType Delegate<ReturnType, Args...>::operator()(Args ...Parameters) const
	{
		return (*_Method)(_Target, Parameters...);
	}

	template<class ReturnType, class ...Args>
	template<ReturnType(*ActualMethod)(Args...)>
	inline Delegate<ReturnType, Args...> Delegate<ReturnType, Args...>::Bind()
	{
		Delegate<ReturnType, Args...> Instance;
		Instance._Target = nullptr;
		Instance._Method = &WrappedMethod<ActualMethod>;

		return Instance;
	}

	template<class ReturnType, class ...Args>
	template<class T, ReturnType(T::* ActualMethod)(Args...)>
	inline Delegate<ReturnType, Args...> Delegate<ReturnType, Args...>::Bind(T& Target)
	{
		Delegate<ReturnType, Args...> Instance;
		Instance._Target = &Target;
		Instance._Method = &WrappedMethod<T, ActualMethod>;

		return Instance;
	}

	template<class ReturnType, class ...Args>
	template<ReturnType(*ActualMethod)(Args...)>
	inline ReturnType Delegate<ReturnType, Args...>::WrappedMethod(void* NullPointer, Args... Parameters)
	{
		return (*ActualMethod)(Parameters...);
	}

	template<class ReturnType, class ...Args>
	template<class T, ReturnType(T::* ActualMethod)(Args...)>
	inline ReturnType Delegate<ReturnType, Args...>::WrappedMethod(void* NonSpecificInstance, Args... Parameters)
	{
		T* SpecificInstance = static_cast<T*>(NonSpecificInstance);
		return (SpecificInstance->*ActualMethod)(Parameters...);
	}
}
#endif
