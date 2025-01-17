/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FUNCTION
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_FUNCTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COMPOSITETYPE
#include "../Concepts/CompositeType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_LAMBDA
#include "../Concepts/Lambda.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_FORWARD
#include "../Functional/Forward.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	class Thread;
}

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// Generic implementation for a typesafe container for all kinds of function.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class Function
	{
	private:
		constexpr Function(const T& Input) noexcept;
	public:
		constexpr Function(const Function& Source) noexcept = delete;

		constexpr Function(Function&& Right) noexcept = delete;

		constexpr ~Function() noexcept;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = delete;

		constexpr Function& operator=(Function&& Right) noexcept = delete;
	};

	template<class T>
	inline constexpr Function<T>::Function(const T& Input) noexcept
	{
		// This constructor needs to be here for type deduction to work! It's ok for it to be private though.
	}

	template<class T>
	inline constexpr Function<T>::~Function() noexcept
	{ }

	/// <summary>
	/// Typesafe container for a function or static-method.
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <class ReturnType, class ...Args>
	class Function<ReturnType(*)(Args...)>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType, Args...>>;
	public:
		constexpr Function(ReturnType(*FunctionOrStaticMethod)(Args...)) noexcept;

		constexpr Function(const Function& Source) noexcept;

		constexpr Function(Function&& Right) noexcept;

		constexpr ~Function() noexcept;
	public:
		constexpr Function& operator=(const Function& Source) noexcept;

		constexpr Function& operator=(Function&& Right) noexcept;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(Args... Parameters) const;
	private:
		ReturnType (*_FunctionOrStaticMethod)(Args...);
	};

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)>::Function(ReturnType(*FunctionOrStaticMethod)(Args...)) noexcept
		: _FunctionOrStaticMethod(FunctionOrStaticMethod)
	{
		/*
		assert(_FunctionOrStaticMethod == nullptr, 
			"Elysium::Core::Template::Container::Function<ReturnType, ...Args>: FunctionOrStaticMethod is nullptr");
		*/
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)>::Function(const Function& Source) noexcept
		: _FunctionOrStaticMethod(Source._FunctionOrStaticMethod)
	{ }

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)>::Function(Function&& Right) noexcept
		: _FunctionOrStaticMethod(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)>::~Function() noexcept
	{
		_FunctionOrStaticMethod = nullptr;
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)>& Function<ReturnType(*)(Args...)>::operator=(const Function& Source) noexcept
	{
		if (this != &Source)
		{
			_FunctionOrStaticMethod = Source._FunctionOrStaticMethod;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)>& Function<ReturnType(*)(Args...)>::operator=(Function&& Right) noexcept
	{
		if (this != &Right)
		{
			_FunctionOrStaticMethod = Elysium::Core::Template::Functional::Move(Right._FunctionOrStaticMethod);

			Right._FunctionOrStaticMethod = nullptr;
		}
		return *this;
	}
	
	template<class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(*)(Args...)>::operator()(Args ...Parameters) const
	{
		return _FunctionOrStaticMethod(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Typesafe container specialization for a lambda-expression.
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <Elysium::Core::Template::Concepts::Lambda L>
	class Function<L>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<L>>;
	public:
		//using ReturnType = decltype(L);
		//using Args... = const char*;
	public:
		constexpr Function(const L& LambdaExpression) noexcept;

		constexpr Function(L&& LambdaExpression) noexcept;

		constexpr Function(const Function& Source) noexcept;

		constexpr Function(Function&& Right) noexcept;

		constexpr ~Function() noexcept;
	public:
		constexpr Function& operator=(const Function& Source) noexcept;

		constexpr Function& operator=(Function&& Right) noexcept;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		template <typename... Args>
		decltype(auto) operator()(Args&&... Parameters);
	private:
		L _LambdaExpression;
	};

	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>::Function(const L& LambdaExpression) noexcept
		: _LambdaExpression(LambdaExpression)
	{ }

	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>::Function(L&& LambdaExpression) noexcept
		: _LambdaExpression(Elysium::Core::Template::Functional::Forward<L>(LambdaExpression))
	{ }

	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>::Function(const Function& Source) noexcept
		: _LambdaExpression(Source._LambdaExpression)
	{ }

	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>::Function(Function&& Right) noexcept
		: _LambdaExpression()
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	
	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>::~Function() noexcept
	{ }

	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>& Function<L>::operator=(const Function& Source) noexcept
	{
		if (this != &Source)
		{
			_LambdaExpression = Source._LambdaExpression;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>& Function<L>::operator=(Function&& Right) noexcept
	{
		if (this != &Right)
		{
			_LambdaExpression = Elysium::Core::Template::Functional::Move(Right._LambdaExpression);

			Right._LambdaExpression = nullptr;
		}
		return *this;
	}
	
	template<Elysium::Core::Template::Concepts::Lambda L>
	template<typename ...Args>
	inline decltype(auto) Function<L>::operator()(Args && ...Parameters)
	{
		return _LambdaExpression(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Typesafe container specialization for an instance-method.
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	class Function<ReturnType(Type::*)(Args...)>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType(Type::*)(Args...)>>;
	public:
		constexpr Function(Type* Instance, ReturnType(Type::* Method)(Args...)) noexcept;

		constexpr Function(const Function& Source) noexcept;

		constexpr Function(Function&& Right) noexcept;

		constexpr ~Function() noexcept;
	public:
		constexpr Function& operator=(const Function& Source) noexcept;

		constexpr Function& operator=(Function&& Right) noexcept;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(Args... Parameters) const;
	private:
		Type* _Instance;
		ReturnType (Type::* _Method)(Args...);
	};

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>::Function(Type* Instance, ReturnType(Type::* Method)(Args...)) noexcept
		: _Instance(Instance), _Method(Method)
	{
		/*
		assert(Instance == nullptr, "Elysium::Core::Template::Container::Function<Type, ReturnType, ...Args>: Instance is nullptr");
		assert(Method == nullptr, "Elysium::Core::Template::Container::Function<Type, ReturnType, ...Args>: Method is nullptr");
		*/
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>::Function(const Function& Source) noexcept
		: _Instance(Source._Instance), _Method(Source._Method)
	{ }

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>::Function(Function&& Right) noexcept
		: _Instance(nullptr), _Method(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	
	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>::~Function() noexcept
	{
		_Method = nullptr;
		_Instance = nullptr;
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>& Function<ReturnType(Type::*)(Args...)>::operator=(const Function& Source) noexcept
	{
		if (this != &Source)
		{
			_Instance = Source._Instance;
			_Method = Source._Method;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>& Function<ReturnType(Type::*)(Args...)>::operator=(Function&& Right) noexcept
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
	
	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(Type::*)(Args...)>::operator()(Args ...Parameters) const
	{
		return (_Instance->*_Method)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Template deduction guide for an instance-method.
	/// </summary>
	template <Elysium::Core::Template::Concepts::CompositeType Type, typename ReturnType, typename... Args>
	Function(Type* Instance, ReturnType(Type::* Method)(Args...))
		-> Function<ReturnType(Type::*)(Args...)>;
}
#endif
