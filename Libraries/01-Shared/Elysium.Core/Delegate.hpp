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
	class ELYSIUM_CORE_API Delegate
	{
	public:
		Delegate(const Delegate& Source) = delete;
		Delegate(Delegate&& Right) noexcept = delete;
		virtual ~Delegate();

		Delegate& operator=(const Delegate& Source) = delete;
		Delegate& operator=(Delegate&& Right) noexcept = delete;

		ReturnType operator()(Args... Parameters);

		Delegate(ReturnType(*StaticMethod)(Args... Parameters));
		Delegate(T* Instance, ReturnType(T::*Method)(Args... Parameters));
	protected:
	private:
		ReturnType(*_StaticMethod)(Args... Parameters);

		T* _Instance;
		ReturnType(T::*_Method)(Args... Parameters);
	};

	template<class ReturnType, class T, class ...Args>
	inline Delegate<ReturnType, T, Args...>::~Delegate()
	{ }

	template<class ReturnType, class T, class ...Args>
	inline ReturnType Delegate<ReturnType, T, Args...>::operator()(Args... Parameters)
	{
		if (_StaticMethod != nullptr)
		{
			return _StaticMethod(Parameters...);
		}
		return (_Instance->*_Method)(Parameters...);
	}

	template<class ReturnType, class T, class ...Args>
	inline Delegate<ReturnType, T, Args...>::Delegate(ReturnType(*StaticMethod)(Args...Parameters))
		: _StaticMethod(StaticMethod)
	{ }
	template<class ReturnType, class T, class ...Args>
	inline Delegate<ReturnType, T, Args...>::Delegate(T * Instance, ReturnType(T::* Method)(Args... Parameters))
		: _Instance(Instance), _Method(Method)
	{ }






	class TestClass
	{
	public:
		inline void Test()
		{
			Delegate<void, TestClass> ParameterlessInstance = Delegate<void, TestClass>(this, &TestClass::Parameterless);
			ParameterlessInstance();

			Delegate<int, TestClass> ParameterlessReturnInstance = Delegate<int, TestClass>(this, &TestClass::ParameterlessReturn);
			int Result = ParameterlessReturnInstance();
			
			Delegate<float, TestClass, int> OneParameterInstance = Delegate<float, TestClass, int>(this, &TestClass::OneParameter);
			float Result2 = OneParameterInstance(5);

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
