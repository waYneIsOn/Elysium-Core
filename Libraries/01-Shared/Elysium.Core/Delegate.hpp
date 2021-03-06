/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DELEGATE
#define ELYSIUM_CORE_DELEGATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

namespace Elysium::Core
{
	namespace Threading
	{
		class Thread;
	}

	namespace Collections::Template
	{
		template <typename T>
		class List;
	}

	template <class ReturnType, class ...Args>
	class Delegate final
	{
		friend class Collections::Template::List<Delegate<ReturnType, Args...>>;
		friend class Threading::Thread;
	public:
		Delegate(const Delegate& Source);
		Delegate(Delegate&& Right) noexcept;
		virtual ~Delegate();

		Delegate& operator=(const Delegate& Source);
		Delegate& operator=(Delegate&& Right) noexcept;

		const bool operator==(const Delegate& Other);
		const bool operator!=(const Delegate& Other);

		ReturnType operator()(Args... Parameters) const;

		template <ReturnType(*ActualMethod)(Args...)>
		static Delegate CreateDelegate();
		template <class T, ReturnType(T::*ActualMethod)(Args...)>
		static Delegate CreateDelegate(T& Target);
	protected:
		template<ReturnType(*ActualMethod)(Args...)>
		static ReturnType WrapMethod(void* NullPointer, Args ...Parameters);
		template<class T, ReturnType(T::* ActualMethod)(Args...)>
		static ReturnType WrapMethod(void* NonSpecificInstance, Args ...Parameters);
	private:
		Delegate();

		void* _Target;
		ReturnType(*_Method)(void* NonSpecificInstance, Args...);
	};

	template<class ReturnType, class ...Args>
	inline Elysium::Core::Delegate<ReturnType, Args...>::Delegate(const Delegate & Source)
		: _Target(Source._Target), _Method(Source._Method)
	{ }
	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>::Delegate(Delegate && Right) noexcept
		: _Target(nullptr), _Method(nullptr)
	{
		*this = std::move(Right);
	}
	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>::~Delegate()
	{ }

	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...> & Delegate<ReturnType, Args...>::operator=(const Delegate & Source)
	{
		if (this != &Source)
		{
			_Target = Source._Target;
			_Method = Source._Method;
		}
		return *this;
	}
	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...> & Delegate<ReturnType, Args...>::operator=(Delegate && Right) noexcept
	{
		if (this != &Right)
		{
			_Target = std::move(Right._Target);
			_Method = std::move(Right._Method);

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
	inline Delegate<ReturnType, Args...> Delegate<ReturnType, Args...>::CreateDelegate()
	{
		Delegate<ReturnType, Args...> Instance;
		Instance._Target = nullptr;
		Instance._Method = &WrapMethod<ActualMethod>;

		return Instance;
	}
	template<class ReturnType, class ...Args>
	template<class T, ReturnType(T::* ActualMethod)(Args...)>
	inline Delegate<ReturnType, Args...> Delegate<ReturnType, Args...>::CreateDelegate(T & Target)
	{
		Delegate<ReturnType, Args...> Instance;
		Instance._Target = &Target;
		Instance._Method = &WrapMethod<T, ActualMethod>;

		return Instance;
	}
	template<class ReturnType, class ...Args>
	template<ReturnType(*ActualMethod)(Args...)>
	inline ReturnType Delegate<ReturnType, Args...>::WrapMethod(void * NullPointer, Args ...Parameters)
	{
		return (*ActualMethod)(Parameters...);
	}
	template<class ReturnType, class ...Args>
	template<class T, ReturnType(T::* ActualMethod)(Args...)>
	inline ReturnType Delegate<ReturnType, Args...>::WrapMethod(void * NonSpecificInstance, Args ...Parameters)
	{
		T* SpecificInstance = static_cast<T*>(NonSpecificInstance);
		return (SpecificInstance->*ActualMethod)(Parameters...);
	}

	template<class ReturnType, class ...Args>
	inline Delegate<ReturnType, Args...>::Delegate()
		: _Target(nullptr), _Method(nullptr)
	{ }
}
#endif
