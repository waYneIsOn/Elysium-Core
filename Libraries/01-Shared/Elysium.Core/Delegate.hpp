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
	template <class ReturnType, class T>
	class ELYSIUM_CORE_API Delegate
	{
	public:
		Delegate(const Delegate& Source) = delete;
		Delegate(Delegate&& Right) noexcept = delete;
		virtual ~Delegate();

		Delegate& operator=(const Delegate& Source) = delete;
		Delegate& operator=(Delegate&& Right) noexcept = delete;

		ReturnType operator()() const;

		//Delegate(const Return(T::*Method)());
		Delegate(T* Instance, ReturnType(T::*Method)());
	protected:
	private:
		T* _Instance;
		ReturnType(T::*_Method)();
	};

	template<class ReturnType, class T>
	inline Delegate<ReturnType, T>::~Delegate()
	{ }

	template<class ReturnType, class T>
	inline ReturnType Delegate<ReturnType, T>::operator()() const
	{
		/*
		if (_Instance == nullptr)
		{
			*_Method();
		}
		*/
		return (_Instance->*_Method)();
	}

	template<class ReturnType, class T>
	inline Delegate<ReturnType, T>::Delegate(T * Instance, ReturnType(T::* Method)())
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

			//Delegate<void, TestClass> OneParameterInstance = Delegate<void, TestClass>(this, &TestClass::OneParameter);

			//Delegate<double, TestClass> ParameterlessStaticReturnInstance = Delegate<double, TestClass>(nullptr, &TestClass::StaticParameterlessReturn);
			//double Result2 = ParameterlessStaticReturnInstance();
		}
	private:
		inline void Parameterless()
		{ }
		inline int ParameterlessReturn()
		{
			return 5;
		}

		inline void OneParameter(int x)
		{ }

		inline static double StaticParameterlessReturn()
		{
			return 0.5;
		}
	};
}
#endif
