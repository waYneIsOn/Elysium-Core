#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Exception.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/CallOnce.hpp"
#include "../UnitTestExtensions/ThreadsafeLogger.hpp"

#include <iostream>
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Threading
{
	TEST_CLASS(CallOnceTests)
	{
	public:
		TEST_METHOD(SimpleTest)
		{
			std::thread SimpleThread0(CallOnceTests::SimpleDoOnce);
			std::thread SimpleThread1(CallOnceTests::SimpleDoOnce);

			SimpleThread0.join();
			SimpleThread1.join();
			
			std::thread Thread0(CallOnceTests::DoOnce, true);
			std::thread Thread1(CallOnceTests::DoOnce, true);
			std::thread Thread2(CallOnceTests::DoOnce, false);
			std::thread Thread3(CallOnceTests::DoOnce, true);

			Thread0.join();
			Thread1.join();
			Thread2.join();
			Thread3.join();
		}
	private:
		static void SimpleDoOnce()
		{
			_Flag0([]() { ThreadsafeLogger::WriteMessage("Simple example : called once\r\n"); });
		}

		static void MayThrow(bool ShouldThrow)
		{
			if (ShouldThrow)
			{
				ThreadsafeLogger::WriteMessage("Throw. CallOnce will retry.\r\n");
				throw Elysium::Core::Template::Exceptions::Exception();
			}
			ThreadsafeLogger::WriteMessage("Did not throw. CallOnce will NOT attempt again.\n\n");
		}

		static void DoOnce(bool ShouldThrow)
		{
			try
			{
				_Flag1(CallOnceTests::MayThrow, ShouldThrow);
			}
			catch(...)
			{ }
		}
	private:
		inline static Elysium::Core::Template::Threading::CallOnce _Flag0;
		inline static Elysium::Core::Template::Threading::CallOnce _Flag1;
	};
}
