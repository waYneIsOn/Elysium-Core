#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Action.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;

namespace UnitTests::Core
{
	float _SomeFloat = 0.0f;

	void FreeAction()
	{
		_SomeFloat = 3.2f;
	}

	struct ActionTestClass
	{
		inline static int _SomeInteger = 23;

		static inline void StaticOneParameter(int x)
		{
			_SomeInteger += x;
		}

		static inline void StaticOneReferenceParameter(int& x)
		{
			x -= 12;
		}

		static inline void StaticOnePointerParameter(int* x)
		{
			*x = 27;
		}

		inline void TwoParameters(int x, int y)
		{
			_SomeInteger = x + y;
		}
	};

	TEST_CLASS(ActionTests)
	{
	public:
		TEST_METHOD(BindActionsTest)
		{
			Action<> Free = Action<>::Bind<&FreeAction>();
			Free();
			Assert::AreEqual(3.2f, _SomeFloat);
			
			Action<int> OneParameters = Action<int>::Bind<&ActionTestClass::StaticOneParameter>();
			OneParameters(27);
			Assert::AreEqual(50, ActionTestClass::_SomeInteger);

			int x = 12;
			Action<int&> OneReference = Action<int&>::Bind<&ActionTestClass::StaticOneReferenceParameter>();
			OneReference(x);
			Assert::AreEqual(0, x);

			Action<int*> OnePointer = Action<int*>::Bind<&ActionTestClass::StaticOnePointerParameter>();
			OnePointer(&x);
			Assert::AreEqual(27, x);

			ActionTestClass Instance = ActionTestClass();
			Action<int, int> TwoParameters = Action<int, int>::Bind<ActionTestClass, &ActionTestClass::TwoParameters>(Instance);
			TwoParameters(27, -17);
			Assert::AreEqual(10, ActionTestClass::_SomeInteger);
		}
	};
}
