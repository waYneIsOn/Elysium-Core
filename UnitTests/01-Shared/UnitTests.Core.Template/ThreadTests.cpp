#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../UnitTestExtensions/ThreadsafeLogger.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Exception.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/Thread.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Threading
{
	void Function() noexcept
	{
		ThreadsafeLogger::WriteMessage("parameterless free function\r\n");
	}

	void FunctionX(const char* Text) noexcept
	{
		ThreadsafeLogger::WriteMessage(Text);
	}

	class XY
	{
	public:
		inline static void StaticMethod() noexcept
		{
			ThreadsafeLogger::WriteMessage("parameterless static method\r\n");
		}

		inline static void StaticMethodX(const char* Text) noexcept
		{
			ThreadsafeLogger::WriteMessage(Text);
		}
	public:
		inline void InstanceMethod() noexcept
		{
			ThreadsafeLogger::WriteMessage("parameterless instance method\r\n");
		}

		inline void ConstInstanceMethod() const noexcept
		{
			ThreadsafeLogger::WriteMessage("const parameterless instance method\r\n");
		}

		inline void InstanceMethodX(const char* Text) noexcept
		{
			ThreadsafeLogger::WriteMessage(Text);
		}

		inline void ConstInstanceMethodX(const char* Text) const noexcept
		{
			ThreadsafeLogger::WriteMessage(Text);
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

				Thread0.Start(Elysium::Core::Template::Functional::Move(FreeFunction));
				Thread1.Start(Elysium::Core::Template::Functional::Move(FreeFunctionWithParams), ">> free function with params\r\n");
			}

			// static methods
			{
				Elysium::Core::Template::Threading::Thread Thread0 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread1 = Elysium::Core::Template::Threading::Thread();

				Elysium::Core::Template::Container::Function StaticMethod = &XY::StaticMethod;
				Elysium::Core::Template::Container::Function StaticMethodWithParams = &XY::StaticMethodX;

				Thread0.Start(Elysium::Core::Template::Functional::Move(StaticMethod));
				Thread1.Start(Elysium::Core::Template::Functional::Move(StaticMethodWithParams), ">> static method with params\r\n");
			}

			// instance methods
			{
				XY Instance = XY();

				Elysium::Core::Template::Threading::Thread Thread0 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread1 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread2 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread3 = Elysium::Core::Template::Threading::Thread();

				Elysium::Core::Template::Container::Function InstanceMethod = &XY::InstanceMethod;
				Elysium::Core::Template::Container::Function ConstInstanceMethod = &XY::ConstInstanceMethod;
				Elysium::Core::Template::Container::Function InstanceMethodWithParams = &XY::InstanceMethodX;
				Elysium::Core::Template::Container::Function ConstInstanceMethodWithParams = &XY::ConstInstanceMethodX;

				Thread0.Start(Elysium::Core::Template::Functional::Move(InstanceMethod), Instance);
				//Thread1.Start(Elysium::Core::Template::Functional::Move(InstanceMethod), ConstInstanceMethod);
				Thread2.Start(Elysium::Core::Template::Functional::Move(InstanceMethodWithParams), Instance, ">> instance method with params\r\n");
				//Thread3.Start(Elysium::Core::Template::Functional::Move(ConstInstanceMethodWithParams), Instance, ">> const instance method with params\r\n");
			}

			// lambdas
			{
				Elysium::Core::Template::Threading::Thread Thread0 = Elysium::Core::Template::Threading::Thread();
				Elysium::Core::Template::Threading::Thread Thread1 = Elysium::Core::Template::Threading::Thread();

				Elysium::Core::Template::Container::Function Lambda0 = []() 
					{ ThreadsafeLogger::WriteMessage("parameterless lambda\r\n"); };
				Elysium::Core::Template::Container::Function Lambda1 = [](const char* Text)
					{ ThreadsafeLogger::WriteMessage(Text); };

				Thread0.Start(Elysium::Core::Template::Functional::Move(Lambda0));
				Thread1.Start(Elysium::Core::Template::Functional::Move(Lambda1), ">> lambda with params\r\n");
			}
		}
	};
}
