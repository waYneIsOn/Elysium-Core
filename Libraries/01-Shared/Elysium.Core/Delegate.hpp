/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DELEGATE
#define ELYSIUM_CORE_DELEGATE

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

namespace Elysium::Core
{
	template <class ReturnType, class T, class ...Args>
	class Delegate
	{
	public:
		Delegate(const Delegate& Source) = delete;
		Delegate(Delegate&& Right) noexcept = delete;
		virtual ~Delegate();

		Delegate& operator=(const Delegate& Source) = delete;
		Delegate& operator=(Delegate&& Right) noexcept = delete;

		ReturnType operator()(Args... Parameters);
		ReturnType operator()(T& Instance, Args... Parameters);

		Delegate(ReturnType(*StaticMethod)(Args... Parameters));
		Delegate(ReturnType(T::*Method)(Args... Parameters));
	protected:
	private:
		ReturnType(*_StaticMethod)(Args... Parameters);
		ReturnType(T::*_Method)(Args... Parameters);
	};

	template<class ReturnType, class T, class ...Args>
	inline Delegate<ReturnType, T, Args...>::~Delegate()
	{ }

	template<class ReturnType, class T, class ...Args>
	inline ReturnType Delegate<ReturnType, T, Args...>::operator()(Args... Parameters)
	{
		return _StaticMethod(Parameters...);
	}
	template<class ReturnType, class T, class ...Args>
	inline ReturnType Delegate<ReturnType, T, Args...>::operator()(T & Instance, Args... Parameters)
	{
		return (Instance.*_Method)(Parameters...);
	}

	template<class ReturnType, class T, class ...Args>
	inline Delegate<ReturnType, T, Args...>::Delegate(ReturnType(*StaticMethod)(Args...Parameters))
		: _StaticMethod(StaticMethod)
	{ }
	template<class ReturnType, class T, class ...Args>
	inline Delegate<ReturnType, T, Args...>::Delegate(ReturnType(T::* Method)(Args... Parameters))
		: _Method(Method)
	{ }






	class TestClass
	{
	public:
		inline void Test()
		{
			Delegate<void, TestClass> ParameterlessInstance = Delegate<void, TestClass>(&TestClass::Parameterless);
			ParameterlessInstance(*this);

			Delegate<int, TestClass> ParameterlessReturnInstance = Delegate<int, TestClass>(&TestClass::ParameterlessReturn);
			int Result = ParameterlessReturnInstance(*this);
			
			Delegate<float, TestClass, int> OneParameterInstance = Delegate<float, TestClass, int>(&TestClass::OneParameter);
			float Result2 = OneParameterInstance(*this, 5);

			Delegate<void, TestClass> StaticParameterless = Delegate<void, TestClass>(&TestClass::StaticParameterless);
			StaticParameterless();
			
			Delegate<double, TestClass> ParameterlessStaticReturnInstance = Delegate<double, TestClass>(&TestClass::StaticParameterlessReturn);
			double Result3 = ParameterlessStaticReturnInstance();
			
			Delegate<double, TestClass, int> OneParameterStaticReturnInstance = Delegate<double, TestClass, int>(&TestClass::StaticOneParameterReturn);
			double Result4 = OneParameterStaticReturnInstance(23);
		}
	private:
		inline void Parameterless()
		{ }
		inline int ParameterlessReturn()
		{
			return 5;
		}
		inline float OneParameter(int x)
		{ 
			return (float)x;
		}

		inline static void StaticParameterless()
		{ }
		inline static double StaticParameterlessReturn()
		{
			return 0.5;
		}
		inline static double StaticOneParameterReturn(int x)
		{
			return 2 * x;
		}
	};
}
#endif
