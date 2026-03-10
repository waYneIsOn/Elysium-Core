#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../UnitTestExtensions/ThreadsafeLogger.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Exceptions/Exception.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/CallOnce.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/Thread.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Threading
{
	TEST_CLASS(CallOnceTests)
	{
	public:
		TEST_METHOD(SimpleTest)
		{
			//Elysium::Core::Template::Threading::Thread SimpleThread0(CallOnceTests::SimpleDoOnce);
			//Elysium::Core::Template::Threading::Thread SimpleThread1(CallOnceTests::SimpleDoOnce);
			Elysium::Core::Template::Threading::Thread SimpleThread0;
			Elysium::Core::Template::Threading::Thread SimpleThread1;

			SimpleThread0.Start(Elysium::Core::Template::Container::Function(&CallOnceTests::SimpleDoOnce));
			SimpleThread0.Start(Elysium::Core::Template::Container::Function(&CallOnceTests::SimpleDoOnce));
			
			SimpleThread0.Join();
			SimpleThread1.Join();

			//Elysium::Core::Template::Threading::Thread Thread0(CallOnceTests::DoOnce, true);
			//Elysium::Core::Template::Threading::Thread Thread1(CallOnceTests::DoOnce, true);
			//Elysium::Core::Template::Threading::Thread Thread2(CallOnceTests::DoOnce, false);
			//Elysium::Core::Template::Threading::Thread Thread3(CallOnceTests::DoOnce, true);
			Elysium::Core::Template::Threading::Thread Thread0;
			Elysium::Core::Template::Threading::Thread Thread1;
			Elysium::Core::Template::Threading::Thread Thread2;
			Elysium::Core::Template::Threading::Thread Thread3;

			Thread0.Start(Elysium::Core::Template::Container::Function(&CallOnceTests::DoOnce), true);
			Thread1.Start(Elysium::Core::Template::Container::Function(&CallOnceTests::DoOnce), true);
			Thread2.Start(Elysium::Core::Template::Container::Function(&CallOnceTests::DoOnce), false);
			Thread3.Start(Elysium::Core::Template::Container::Function(&CallOnceTests::DoOnce), true);

			Thread0.Join();
			Thread1.Join();
			Thread2.Join();
			Thread3.Join();
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
