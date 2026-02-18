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
	public:
		constexpr Function(const T& Input) noexcept = delete;

		constexpr Function(const Function& Source) noexcept = delete;

		constexpr Function(Function&& Right) noexcept = delete;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = delete;

		constexpr Function& operator=(Function&& Right) noexcept = delete;
	};

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
		using Pointer = ReturnType(*)(Args...);
	public:
		constexpr Function(ReturnType(*FunctionOrStaticMethod)(Args...)) noexcept;

		constexpr Function(const Function& Source) noexcept = default;

		constexpr Function(Function&& Right) noexcept = default;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = default;

		constexpr Function& operator=(Function&& Right) noexcept = default;
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
	inline ReturnType Function<ReturnType(*)(Args...)>::operator()(Args ...Parameters) const
	{
		return _FunctionOrStaticMethod(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Typesafe container for a function or static-method declared as noexcept.
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <class ReturnType, class ...Args>
	class Function<ReturnType(*)(Args...) noexcept>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType, Args...>>;
	public:
		constexpr Function(ReturnType(*FunctionOrStaticMethod)(Args...) noexcept) noexcept;

		constexpr Function(const Function& Source) noexcept = default;

		constexpr Function(Function&& Right) noexcept = default;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = default;

		constexpr Function& operator=(Function&& Right) noexcept = default;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(Args... Parameters) const noexcept;
	private:
		ReturnType(*_FunctionOrStaticMethod)(Args...) noexcept;
		//ReturnType(*_FunctionOrStaticMethod)(Args...);	// store without noexcept-qualifier
	};

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)noexcept>::Function(ReturnType(*FunctionOrStaticMethod)(Args...) noexcept) noexcept
		: _FunctionOrStaticMethod(FunctionOrStaticMethod)
	{ }

	template<class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(*)(Args...)noexcept>::operator()(Args ...Parameters) const noexcept
	{
		return _FunctionOrStaticMethod(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
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
		constexpr Function(ReturnType(Type::* Method)(Args...)) noexcept;

		constexpr Function(const Function& Source) noexcept = default;

		constexpr Function(Function&& Right) noexcept = default;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = default;

		constexpr Function& operator=(Function&& Right) noexcept = default;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(Type& Instance, Args... Parameters) const;
	private:
		ReturnType (Type::* _Method)(Args...);
	};

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>::Function(ReturnType(Type::* Method)(Args...)) noexcept
		: _Method(Method)
	{
		//assert(Method == nullptr, "Elysium::Core::Template::Container::Function<ReturnType(Type::*)(Args...)>: Method is nullptr");
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(Type::*)(Args...)>::operator()(Type& Instance, Args ...Parameters) const
	{
		return (Instance.*_Method)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Typesafe container specialization for an instance-method declared as noexcept.
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <typeparam name="Type"></typeparam>
	template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	class Function<ReturnType(Type::*)(Args...) noexcept>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType(Type::*)(Args...)>>;
	public:
		constexpr Function(ReturnType(Type::* Method)(Args...) noexcept) noexcept;

		constexpr Function(const Function& Source) noexcept = default;

		constexpr Function(Function&& Right) noexcept = default;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = default;

		constexpr Function& operator=(Function&& Right) noexcept = default;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(Type& Instance, Args... Parameters) const noexcept;
	private:
		ReturnType(Type::* _Method)(Args...) noexcept;
	};

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)noexcept>::Function(ReturnType(Type::* Method)(Args...)noexcept) noexcept
		: _Method(Method)
	{
		//assert(Method == nullptr, "Elysium::Core::Template::Container::Function<ReturnType(Type::*)(Args...) noexcept>: Method is nullptr");
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(Type::*)(Args...)noexcept>::operator()(Type& Instance, Args ...Parameters) const noexcept
	{
		return (Instance.*_Method)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Typesafe container specialization for an instance-method declared as const.
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	class Function<ReturnType(Type::*)(Args...) const>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType(Type::*)(Args...)>>;
	public:
		constexpr Function(ReturnType(Type::* Method)(Args...) const) noexcept;

		constexpr Function(const Function& Source) noexcept = default;

		constexpr Function(Function&& Right) noexcept = default;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = default;

		constexpr Function& operator=(Function&& Right) noexcept = default;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(const Type& Instance, Args... Parameters) const;
	private:
		ReturnType(Type::* _Method)(Args...) const;
	};

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)const>::Function(ReturnType(Type::* Method)(Args...) const) noexcept
		: _Method(Method)
	{
		//assert(Method == nullptr, "Elysium::Core::Template::Container::Function<ReturnType(Type::*)(Args...) const>: Method is nullptr");
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(Type::*)(Args...)const>::operator()(const Type& Instance, Args ...Parameters) const
	{
		return (Instance.*_Method)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Typesafe container specialization for an instance-method declared as const and noexcept.
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	class Function<ReturnType(Type::*)(Args...) const noexcept>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType(Type::*)(Args...)>>;
	public:
		constexpr Function(ReturnType(Type::* Method)(Args...) const noexcept) noexcept;

		constexpr Function(const Function& Source) noexcept = default;

		constexpr Function(Function&& Right) noexcept = default;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = default;

		constexpr Function& operator=(Function&& Right) noexcept = default;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(const Type& Instance, Args... Parameters) const noexcept;
	private:
		ReturnType(Type::* _Method)(Args...) const noexcept;
	};

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)const noexcept>::Function(ReturnType(Type::* Method)(Args...) const noexcept) noexcept
		: _Method(Method)
	{
		//assert(Method == nullptr, "Elysium::Core::Template::Container::Function<ReturnType(Type::*)(Args...) const noexcept>: Method is nullptr");
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(Type::*)(Args...)const noexcept>::operator()(const Type& Instance, Args ...Parameters) const noexcept
	{
		return (Instance.*_Method)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
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

		constexpr Function(const Function& Source) noexcept = default;

		constexpr Function(Function&& Right) noexcept = default;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept = default;

		constexpr Function& operator=(Function&& Right) noexcept = default;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		template <class... Args>
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
	template<typename ...Args>
	inline decltype(auto) Function<L>::operator()(Args && ...Parameters)
	{
		return _LambdaExpression(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}
	
	/// <summary>
	/// Template deduction guide for an instance-method.
	/// </summary>
	template <Elysium::Core::Template::Concepts::CompositeType Type, typename ReturnType, typename... Args>
	Function(Type* Instance, ReturnType(Type::* Method)(Args...))
		-> Function<ReturnType(Type::*)(Args...)>;
}
#endif
