#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../UnitTestExtensions/ThreadsafeLogger.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Exception.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/Thread.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Threading
{
	void Function()
	{
		ThreadsafeLogger::WriteMessage("parameterless free function\r\n");
	}

	void FunctionX(const char* Text)
	{
		ThreadsafeLogger::WriteMessage(Text);
	}

	class XY
	{
	public:
		inline static void StaticMethod()
		{
			ThreadsafeLogger::WriteMessage("parameterless static method\r\n");
		}

		inline static void StaticMethodX(const char* Text)
		{
			ThreadsafeLogger::WriteMessage(Text);
		}
	public:
		inline void InstanceMethod()
		{
			ThreadsafeLogger::WriteMessage("parameterless instance method\r\n");
		}

		inline void InstanceMethodX(const char* Text)
		{
			ThreadsafeLogger::WriteMessage(Text);
		}

		inline void Blub() noexcept
		{

		}
	};

	TEST_CLASS(ThreadTests)
	{
	public:
		TEST_METHOD(Start)
		{
			// free functions
			{
				Elysium::Core::Template::Threading::Thread Thread0 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread1 = Elysium::Core::Template::Threading::Thread();

				Elysium::Core::Template::Container::Function FreeFunction = &Function;
				Elysium::Core::Template::Container::Function FreeFunctionWithParams = &FunctionX;

				//Thread0.Start(Elysium::Core::Template::Functional::Move(FreeFunction));
				Thread1.Start(Elysium::Core::Template::Functional::Move(FreeFunctionWithParams), ">> free function with params\r\n");
			}

			// static methods
			{
				Elysium::Core::Template::Threading::Thread Thread0 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread1 = Elysium::Core::Template::Threading::Thread();

				Elysium::Core::Template::Container::Function StaticMethod = &XY::StaticMethod;
				Elysium::Core::Template::Container::Function StaticMethodWithParams = &XY::StaticMethodX;

				//Thread0.Start(Elysium::Core::Template::Functional::Move(StaticMethod));
				Thread1.Start(Elysium::Core::Template::Functional::Move(StaticMethodWithParams), ">> static method with params\r\n");
			}

			// instance methods
			{
				XY Instance = XY();

				Elysium::Core::Template::Threading::Thread Thread0 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread1 = Elysium::Core::Template::Threading::Thread();

				Elysium::Core::Template::Container::Function InstanceMethod = &XY::InstanceMethod;
				Elysium::Core::Template::Container::Function InstanceMethodWithParams = &XY::InstanceMethodX;

				Thread0.Start(Elysium::Core::Template::Functional::Move(InstanceMethod), Instance);
				Thread1.Start(Elysium::Core::Template::Functional::Move(InstanceMethodWithParams), Instance, ">> instance method with params\r\n");
			}
		}
	};
}
