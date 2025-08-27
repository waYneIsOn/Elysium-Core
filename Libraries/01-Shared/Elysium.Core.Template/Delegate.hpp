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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Threading
{
	class Thread;
}

namespace Elysium::Core::Template::Container
{
	/*
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <class ReturnType, class ...Args>
	class Delegate
	{
		friend class Elysium::Core::Threading::Thread;
		friend class Elysium::Core::Template::Container::Vector<Delegate<ReturnType, Args...>>;
	public:
		constexpr Delegate(ReturnType(*FunctionOrStaticMethod)(Args...)) noexcept;

		constexpr Delegate(const Delegate& Source) noexcept;

		constexpr Delegate(Delegate&& Right) noexcept;

		constexpr ~Delegate() noexcept;
	public:
		constexpr Delegate& operator=(const Delegate& Source) noexcept;

		constexpr Delegate& operator=(Delegate&& Right) noexcept;
	public:
		constexpr const bool operator==(const Delegate& Other) noexcept;

		constexpr const bool operator!=(const Delegate& Other) noexcept;
	public:
		ReturnType operator()(Args... Parameters) const;
	private:
		ReturnType(*_FunctionOrStaticMethod)(Args...);
	};

	template<class ReturnType, class ...Args>
	inline constexpr Delegate<ReturnType, Args...>::Delegate(ReturnType(*FunctionOrStaticMethod)(Args...)) noexcept
		: _FunctionOrStaticMethod(FunctionOrStaticMethod)
	{
		//static_assert(_FunctionOrStaticMethod == nullptr, 
		//	"Elysium::Core::Template::Container::Delegate<Type, ReturnType, ...Args>: FunctionOrStaticMethod is nullptr");
	}
	
	template<class ReturnType, class ...Args>
	inline constexpr Delegate<ReturnType, Args...>::Delegate(const Delegate& Source) noexcept
		: _FunctionOrStaticMethod(Source._FunctionOrStaticMethod)
	{ }

	template<class ReturnType, class ...Args>
	inline constexpr Delegate<ReturnType, Args...>::Delegate(Delegate&& Right) noexcept
		: _FunctionOrStaticMethod(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	
	template<class ReturnType, class ...Args>
	inline constexpr Delegate<ReturnType, Args...>::~Delegate() noexcept
	{
		_FunctionOrStaticMethod = nullptr;
	}
	
	template<class ReturnType, class ...Args>
	inline constexpr Delegate<ReturnType, Args...>& Delegate<ReturnType, Args...>::operator=(const Delegate& Source) noexcept
	{
		if (this != &Source)
		{
			_FunctionOrStaticMethod = Source._FunctionOrStaticMethod;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline constexpr Delegate<ReturnType, Args...>& Delegate<ReturnType, Args...>::operator=(Delegate&& Right) noexcept
	{
		if (this != &Right)
		{
			_FunctionOrStaticMethod = Elysium::Core::Template::Functional::Move(Right._FunctionOrStaticMethod);

			Right._FunctionOrStaticMethod = nullptr;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline constexpr const bool Delegate<ReturnType, Args...>::operator==(const Delegate& Other) noexcept
	{
		return _FunctionOrStaticMethod == Other._FunctionOrStaticMethod;
	}

	template<class ReturnType, class ...Args>
	inline constexpr const bool Delegate<ReturnType, Args...>::operator!=(const Delegate& Other) noexcept
	{
		return _FunctionOrStaticMethod != Other._FunctionOrStaticMethod;
	}

	template<class ReturnType, class ...Args>
	inline ReturnType Delegate<ReturnType, Args...>::operator()(Args ...Parameters) const
	{
		return (*_FunctionOrStaticMethod)(Parameters...);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <class Type, class ReturnType, class ...Args>
	class Delegate<Type, ReturnType(Args...)>
	{
		friend class Elysium::Core::Threading::Thread;
		friend class Elysium::Core::Template::Container::Vector<Delegate<ReturnType, Args...>>;
	public:
		constexpr Delegate(Type* Instance, ReturnType(Type::* Method)(Args...)) noexcept;
		
		constexpr Delegate(const Delegate& Source) noexcept;

		constexpr Delegate(Delegate&& Right) noexcept;
		
		constexpr ~Delegate() noexcept;
	public:
		constexpr Delegate& operator=(const Delegate& Source) noexcept;

		constexpr Delegate& operator=(Delegate&& Right) noexcept;
	public:
		constexpr const bool operator==(const Delegate& Other) noexcept;

		constexpr const bool operator!=(const Delegate& Other) noexcept;
	public:
		template <ReturnType(Type::* Method)(Args...)>
		static Delegate Bind(Type& Target);
	public:
		ReturnType operator()(Args... Parameters) const;
	private:
		Type* _Instance;
		ReturnType(Type::* _Method)(Args...);
	};

	template<class Type, class ReturnType, class ...Args>
	inline constexpr Delegate<Type, ReturnType(Args...)>::Delegate(Type* Instance, ReturnType(Type::* Method)(Args...)) noexcept
		: _Instance(Instance), _Method(Method)
	{
		//static_assert(_Instance == nullptr, "Elysium::Core::Template::Container::Delegate<Type, ReturnType, ...Args>: Instance is nullptr");
		//static_assert(_Method == nullptr, "Elysium::Core::Template::Container::Delegate<Type, ReturnType, ...Args>: Method is nullptr");
	}

	template<class Type, class ReturnType, class ...Args>
	inline constexpr Delegate<Type, ReturnType(Args...)>::Delegate(const Delegate& Source) noexcept
		: _Instance(Source._Instance), _Method(Source._Method)
	{ }

	template<class Type, class ReturnType, class ...Args>
	inline constexpr Delegate<Type, ReturnType(Args...)>::Delegate(Delegate&& Right) noexcept
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<class Type, class ReturnType, class ...Args>
	inline constexpr Delegate<Type, ReturnType(Args...)>::~Delegate() noexcept
	{
		_Method = nullptr;
		_Instance = nullptr;
	}

	template<class Type, class ReturnType, class ...Args>
	inline constexpr Delegate<Type, ReturnType(Args...)>& Delegate<Type, ReturnType(Args...)>::operator=(const Delegate & Source) noexcept
	{
		if (this != &Source)
		{
			_Instance = Source._Instance;
			_Method = Source._Method;
		}
		return *this;
	}

	template<class Type, class ReturnType, class ...Args>
	inline constexpr Delegate<Type, ReturnType(Args...)>& Delegate<Type, ReturnType(Args...)>::operator=(Delegate&& Right) noexcept
	{
		if (this != &Right)
		{
			_Instance = Elysium::Core::Template::Functional::Move(Right._Instance);
			_Method = Elysium::Core::Template::Functional::Move(Right._Method);

			Right._Instance = nullptr;
			Right._Method = nullptr;
		}
		return *this;
	}

	template<class Type, class ReturnType, class ...Args>
	inline constexpr const bool Delegate<Type, ReturnType(Args...)>::operator==(const Delegate& Other) noexcept
	{
		return _Instance == Other._Instance && _Method == Other._Method;
	}

	template<class Type, class ReturnType, class ...Args>
	inline constexpr const bool Delegate<Type, ReturnType(Args...)>::operator!=(const Delegate& Other) noexcept
	{
		return _Instance != Other._Instance || _Method != Other._Method;
	}
	
	template<class Type, class ReturnType, class ...Args>
	template<ReturnType(Type::* Method)(Args...)>
	inline Delegate<Type, ReturnType(Args...)> Delegate<Type, ReturnType(Args...)>::Bind(Type& Target)
	{
		return Delegate(&Target, Method);
	}

	template<class Type, class ReturnType, class ...Args>
	inline ReturnType Delegate<Type, ReturnType(Args...)>::operator()(Args ...Parameters) const
	{
		return (_Instance->*_Method)(Parameters...);
	}
	*/
	
	template <class ReturnType, class ...Args>
	class Delegate
	{
		friend class Elysium::Core::Threading::Thread;
		friend class Elysium::Core::Template::Container::Vector<Delegate<ReturnType, Args...>>;
	private:
		constexpr Delegate() noexcept = default;
	public:
		Delegate(const Delegate& Source);

		Delegate(Delegate&& Right) noexcept;

		constexpr ~Delegate() noexcept = default;
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
	private:
		template<ReturnType(*ActualMethod)(Args...)>
		static ReturnType WrappedMethod(void* NullPointer, Args... Parameters);

		template<class T, ReturnType(T::* ActualMethod)(Args...)>
		static ReturnType WrappedMethod(void* NonSpecificInstance, Args... Parameters);
	};

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
