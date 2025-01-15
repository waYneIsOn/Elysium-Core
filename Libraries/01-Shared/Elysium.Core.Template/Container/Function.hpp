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

namespace Elysium::Core::Template::Container
{
	/*
	template <class...>
	class Function
	{ };
	*/


	/// <summary>
	/// Typesafe container for a function or static-method.
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <class ReturnType, class ...Args>
	class Function
	{
		//friend class Elysium::Core::Threading::Thread;
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
		constexpr const bool operator==(const Function& Other) noexcept;

		constexpr const bool operator!=(const Function& Other) noexcept;
	public:
		ReturnType operator()(Args... Parameters) const;
	private:
		ReturnType (*_FunctionOrStaticMethod)(Args...);
	};

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType, Args...>::Function(ReturnType(*FunctionOrStaticMethod)(Args...)) noexcept
		: _FunctionOrStaticMethod(FunctionOrStaticMethod)
	{
		/*
		assert(_FunctionOrStaticMethod == nullptr, 
			"Elysium::Core::Template::Container::Function<ReturnType, ...Args>: FunctionOrStaticMethod is nullptr");
		*/
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType, Args...>::Function(const Function& Source) noexcept
		: _FunctionOrStaticMethod(Source._FunctionOrStaticMethod)
	{ }

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType, Args...>::Function(Function&& Right) noexcept
		: _FunctionOrStaticMethod(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType, Args...>::~Function() noexcept
	{
		_FunctionOrStaticMethod = nullptr;
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType, Args...>& Function<ReturnType, Args...>::operator=(const Function& Source) noexcept
	{
		if (this != &Source)
		{
			_FunctionOrStaticMethod = Source._FunctionOrStaticMethod;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType, Args...>& Function<ReturnType, Args...>::operator=(Function&& Right) noexcept
	{
		if (this != &Right)
		{
			_FunctionOrStaticMethod = Elysium::Core::Template::Functional::Move(Right._FunctionOrStaticMethod);

			Right._FunctionOrStaticMethod = nullptr;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline constexpr const bool Function<ReturnType, Args...>::operator==(const Function& Other) noexcept
	{
		return _FunctionOrStaticMethod == Other._FunctionOrStaticMethod;
	}

	template<class ReturnType, class ...Args>
	inline constexpr const bool Function<ReturnType, Args...>::operator!=(const Function& Other) noexcept
	{
		return _FunctionOrStaticMethod != Other._FunctionOrStaticMethod;
	}

	template<class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType, Args...>::operator()(Args ...Parameters) const
	{
		return (*_FunctionOrStaticMethod)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}
	
	/// <summary>
	/// Typesafe container specialization for a lambda-expression.
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <Elysium::Core::Template::Concepts::Lambda L>
	class Function<L>
	{
		//friend class Elysium::Core::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType, Args...>>;
	public:
		constexpr Function(L& LambdaExpression) noexcept;

		constexpr Function(const Function& Source) noexcept = delete;

		constexpr Function(Function&& Right) noexcept = delete;

		constexpr ~Function() noexcept;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = delete;

		constexpr Function& operator=(Function&& Right) noexcept = delete;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		//ReturnType operator()(Args... Parameters) const;
	private:
		L _LambdaExpression;
	};
	
	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>::Function(L& LambdaExpression) noexcept
		: _LambdaExpression(Elysium::Core::Template::Functional::Forward<L>(LambdaExpression))
	{ }
	
	template<Elysium::Core::Template::Concepts::Lambda L>
	inline constexpr Function<L>::~Function() noexcept
	{ }
	
	/// <summary>
	/// Typesafe container specialization for an instance-method.
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	class Function<Type, ReturnType(Args...)>
	{
		//friend class Elysium::Core::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType, Args...>>;
	public:
		constexpr Function(Type* Instance, ReturnType(Type::* Method)(Args...)) noexcept;

		constexpr Function(const Function& Source) noexcept;

		constexpr Function(Function&& Right) noexcept;

		constexpr ~Function() noexcept;
	public:
		constexpr Function& operator=(const Function& Source) noexcept;

		constexpr Function& operator=(Function&& Right) noexcept;
	public:
		constexpr const bool operator==(const Function& Other) noexcept;

		constexpr const bool operator!=(const Function& Other) noexcept;
	public:
		ReturnType operator()(Args... Parameters) const;
	private:
		Type* _Instance;
		ReturnType (Type::* _Method)(Args...);
	};

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<Type, ReturnType(Args...)>::Function(Type* Instance, ReturnType(Type::* Method)(Args...)) noexcept
		: _Instance(Instance), _Method(Method)
	{
		/*
		assert(Instance == nullptr, "Elysium::Core::Template::Container::Function<Type, ReturnType, ...Args>: Instance is nullptr");
		assert(Method == nullptr, "Elysium::Core::Template::Container::Function<Type, ReturnType, ...Args>: Method is nullptr");
		*/
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<Type, ReturnType(Args...)>::Function(const Function& Source) noexcept
		: _Instance(Source._Instance), _Method(Source._Method)
	{ }

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<Type, ReturnType(Args...)>::Function(Function&& Right) noexcept
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<Type, ReturnType(Args...)>::~Function() noexcept
	{
		_Method = nullptr;
		_Instance = nullptr;
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<Type, ReturnType(Args...)>& Function<Type, ReturnType(Args...)>::operator=(const Function& Source) noexcept
	{
		if (this != &Source)
		{
			_Instance = Source._Instance;
			_Method = Source._Method;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<Type, ReturnType(Args...)>& Function<Type, ReturnType(Args...)>::operator=(Function&& Right) noexcept
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
	inline constexpr const bool Function<Type, ReturnType(Args...)>::operator==(const Function& Other) noexcept
	{
		return _Instance == Other._Instance && _Method == Other._Method;
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr const bool Function<Type, ReturnType(Args...)>::operator!=(const Function& Other) noexcept
	{
		return _Instance != Other._Instance || _Method != Other._Method;
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline ReturnType Function<Type, ReturnType(Args...)>::operator()(Args ...Parameters) const
	{
		return (_Instance->*_Method)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}
}
#endif
