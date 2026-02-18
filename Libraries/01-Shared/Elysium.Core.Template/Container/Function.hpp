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
		static constexpr bool IsConst = false;
		static constexpr bool IsNoexcept = false;
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
		static constexpr bool IsConst = false;
		static constexpr bool IsNoexcept = false;
	public:
		constexpr Function(ReturnType(*FunctionOrStaticMethod)(Args...)) noexcept;

		constexpr Function(const Function& Source) noexcept;

		constexpr Function(Function&& Right) noexcept;

		constexpr ~Function() noexcept = default;
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
	/// Typesafe container for a function or static-method that is marked as noexcept.
	/// </summary>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	template <class ReturnType, class ...Args>
	class Function<ReturnType(*)(Args...) noexcept>
	{
		friend class Elysium::Core::Template::Threading::Thread;
		//friend class Elysium::Core::Template::Container::Vector<Function<ReturnType, Args...>>;
	public:
		constexpr Function(ReturnType(*FunctionOrStaticMethod)(Args...)noexcept ) noexcept;

		constexpr Function(const Function& Source) noexcept;

		constexpr Function(Function&& Right) noexcept;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept;

		constexpr Function& operator=(Function&& Right) noexcept;
	public:
		constexpr const bool operator==(const Function& Other) noexcept = delete;

		constexpr const bool operator!=(const Function& Other) noexcept = delete;
	public:
		ReturnType operator()(Args... Parameters) const noexcept;
	private:
		ReturnType(*_FunctionOrStaticMethod)(Args...) noexcept;
	};

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)noexcept>::Function(ReturnType(*FunctionOrStaticMethod)(Args...) noexcept) noexcept
		: _FunctionOrStaticMethod(FunctionOrStaticMethod)
	{ }

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)noexcept>::Function(const Function& Source) noexcept
		: _FunctionOrStaticMethod(Source._FunctionOrStaticMethod)
	{ }

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)noexcept>::Function(Function&& Right) noexcept
		: _FunctionOrStaticMethod(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)noexcept>& Function<ReturnType(*)(Args...)noexcept>::operator=(const Function& Source) noexcept
	{
		if (this != &Source)
		{
			_FunctionOrStaticMethod = Source._FunctionOrStaticMethod;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(*)(Args...)noexcept>& Function<ReturnType(*)(Args...)noexcept>::operator=(Function&& Right) noexcept
	{
		if (this != &Right)
		{
			_FunctionOrStaticMethod = Elysium::Core::Template::Functional::Move(Right._FunctionOrStaticMethod);

			Right._FunctionOrStaticMethod = nullptr;
		}
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(*)(Args...)noexcept>::operator()(Args ...Parameters) const noexcept
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

		constexpr ~Function() noexcept = default;
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
		constexpr Function(ReturnType(Type::* Method)(Args...)) noexcept;

		constexpr Function(const Function& Source) noexcept;

		constexpr Function(Function&& Right) noexcept;

		constexpr ~Function() noexcept = default;
	public:
		constexpr Function& operator=(const Function& Source) noexcept;

		constexpr Function& operator=(Function&& Right) noexcept;
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
		/*
		assert(Instance == nullptr, "Elysium::Core::Template::Container::Function<Type, ReturnType, ...Args>: Instance is nullptr");
		assert(Method == nullptr, "Elysium::Core::Template::Container::Function<Type, ReturnType, ...Args>: Method is nullptr");
		*/
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>::Function(const Function& Source) noexcept
		: _Method(Source._Method)
	{ }

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>::Function(Function&& Right) noexcept
		: _Method(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	
	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>& Function<ReturnType(Type::*)(Args...)>::operator=(const Function& Source) noexcept
	{
		if (this != &Source)
		{
			_Method = Source._Method;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline constexpr Function<ReturnType(Type::*)(Args...)>& Function<ReturnType(Type::*)(Args...)>::operator=(Function&& Right) noexcept
	{
		if (this != &Right)
		{
			_Method = Elysium::Core::Template::Functional::Move(Right._Method);

			Right._Method = nullptr;
		}
		return *this;
	}
	
	template<Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
	inline ReturnType Function<ReturnType(Type::*)(Args...)>::operator()(Type& Instance, Args ...Parameters) const
	{
		return (Instance.*_Method)(Elysium::Core::Template::Functional::Forward<Args>(Parameters)...);
	}

	/// <summary>
	/// Template deduction guide for an instance-method.
	/// </summary>
	template <Elysium::Core::Template::Concepts::CompositeType Type, typename ReturnType, typename... Args>
	Function(Type* Instance, ReturnType(Type::* Method)(Args...))
		-> Function<ReturnType(Type::*)(Args...)>;
}
#endif
