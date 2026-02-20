#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Container/Function.hpp"

#include <iostream>

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void GlobalFunction(const char* Input)
{
	std::cout << "GlobalFunction(" << Input << ")" << std::endl;
}

void GlobalNoexcept(const char* Input) noexcept
{
	std::cout << "GlobalNoexcept(" << Input << ")" << std::endl;
}

void GlobalThrow(const char* Input) noexcept(false)
{
	std::cout << "GlobalThrow(" << Input << ")" << std::endl;
}

namespace UnitTests::Core::Template::Container
{
	void NamespaceFunction(const char* Input)
	{
		std::cout << "Function(" << Input << ")" << std::endl;
	}

	void NamespaceNoexcept(const char* Input) noexcept
	{
		std::cout << "NamespaceNoexcept(" << Input << ")" << std::endl;
	}

	void NamespaceThrow(const char* Input) noexcept(false)
	{
		std::cout << "NamespaceThrow(" << Input << ")" << std::endl;
	}

	class ExampleClass
	{
	public:
		static void StaticMethod(const char* Input)
		{
			std::cout << "StaticMethod(" << Input << ")" << std::endl;
		}

		static void StaticNoexcept(const char* Input) noexcept
		{
			std::cout << "StaticNoexcept(" << Input << ")" << std::endl;
		}

		static void StaticThrow(const char* Input) noexcept(false)
		{
			std::cout << "StaticThrow(" << Input << ")" << std::endl;
		}
	public:
		void InstanceMethod(const char* Input)
		{
			std::cout << "InstanceMethod(" << Input << ")" << std::endl;
		}

		void InstanceLValue(const char* Input)&
		{
			std::cout << "InstanceLValue(" << Input << ")" << std::endl;
		}

		void InstanceRValue(const char* Input)&&
		{
			std::cout << "InstanceRValue(" << Input << ")" << std::endl;
		}

		void InstanceNoexcept(const char* Input) noexcept
		{
			std::cout << "InstanceNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceLValueNoexcept(const char* Input)& noexcept
		{
			std::cout << "InstanceLValueNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceRValueNoexcept(const char* Input)&& noexcept
		{
			std::cout << "InstanceRValueNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceConst(const char* Input) const
		{
			std::cout << "InstanceConst(" << Input << ")" << std::endl;
		}

		void InstanceConstLValue(const char* Input) const&
		{
			std::cout << "InstanceConstLValue(" << Input << ")" << std::endl;
		}

		void InstanceConstRValue(const char* Input) const&&
		{
			std::cout << "InstanceConstRValue(" << Input << ")" << std::endl;
		}

		void InstanceConstNoexcept(const char* Input) const noexcept
		{
			std::cout << "InstanceConstNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceConstLValueNoexcept(const char* Input) const& noexcept
		{
			std::cout << "InstanceConstLValueNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceConstRValueNoexcept(const char* Input) const&& noexcept
		{
			std::cout << "InstanceConstRValueNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceVolatile(const char* Input) volatile
		{
			std::cout << "InstanceVolatile(" << Input << ")" << std::endl;
		}

		void InstanceVolatileLValue(const char* Input) volatile&
		{
			std::cout << "InstanceVolatileLValue(" << Input << ")" << std::endl;
		}

		void InstanceVolatileRValue(const char* Input) volatile&&
		{
			std::cout << "InstanceVolatileRValue(" << Input << ")" << std::endl;
		}

		void InstanceVolatileNoexcept(const char* Input) volatile noexcept
		{
			std::cout << "InstanceVolatileNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceVolatileLValueNoexcept(const char* Input) volatile& noexcept
		{
			std::cout << "InstanceVolatileLValueNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceVolatileRValueNoexcept(const char* Input) volatile&& noexcept
		{
			std::cout << "InstanceVolatileRValueNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceConstVolatile(const char* Input) const volatile
		{
			std::cout << "InstanceConstVolatile(" << Input << ")" << std::endl;
		}

		void InstanceConstVolatileLValue(const char* Input) const volatile&
		{
			std::cout << "InstanceConstVolatileLValue(" << Input << ")" << std::endl;
		}

		void InstanceConstVolatileRValue(const char* Input) const volatile&&
		{
			std::cout << "InstanceConstVolatileRValue(" << Input << ")" << std::endl;
		}

		void InstanceConstVolatileNoexcept(const char* Input) const volatile noexcept
		{
			std::cout << "InstanceConstVolatileNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceConstVolatileLValueNoexcept(const char* Input) const volatile& noexcept
		{
			std::cout << "InstanceConstVolatileLValueNoexcept(" << Input << ")" << std::endl;
		}

		void InstanceConstVolatileRValueNoexcept(const char* Input) const volatile&& noexcept
		{
			std::cout << "InstanceConstVolatileRValueNoexcept(" << Input << ")" << std::endl;
		}
	public:
		void operator()(){ }
	};

	TEST_CLASS(FunctionTests)
	{
	public:
		TEST_METHOD(AllKindsOfFunctionsAndMethods)
		{
			ExampleClass ExampleInstance = ExampleClass();
			auto Lambda = [](const char* Input) -> void { std::cout << "Lambda(" << Input << ")" << std::endl; };
			auto SimpleLambda = []() -> void {};

			// prepare capture of std::cout
			std::ostringstream captureStream;
			std::streambuf* originalCoutBuffer = std::cout.rdbuf();
			std::cout.rdbuf(captureStream.rdbuf());

			// ...
			Function GlobalFunctionDelegate = &GlobalFunction;
			Function GlobalNoexceptDelegate = &GlobalNoexcept;
			Function GlobalThrowDelegate = &GlobalThrow;
			Function NamespaceFunctionDelegate = &NamespaceFunction;
			Function NamespaceNoexceptDelegate = &NamespaceNoexcept;
			Function NamespaceThrowDelegate = &NamespaceThrow;

			Function StaticMethodDelegate = &ExampleClass::StaticMethod;
			Function StaticNoexceptDelegate = &ExampleClass::StaticNoexcept;
			Function StaticThrowDelegate = &ExampleClass::StaticThrow;

			Function InstanceMethodDelegate = &ExampleClass::InstanceMethod;
			Function InstanceLValueDelegate = &ExampleClass::InstanceLValue;
			Function InstanceRValueDelegate = &ExampleClass::InstanceRValue;
			Function InstanceNoexceptDelegate = &ExampleClass::InstanceNoexcept;
			Function InstanceLValueNoexceptDelegate = &ExampleClass::InstanceLValueNoexcept;
			Function InstanceRValueNoexceptDelegate = &ExampleClass::InstanceRValueNoexcept;
			Function InstanceConstDelegate = &ExampleClass::InstanceConst;
			Function InstanceConstLValueDelegate = &ExampleClass::InstanceConstLValue;
			Function InstanceConstRValueDelegate = &ExampleClass::InstanceConstRValue;
			Function InstanceConstNoexceptDelegate = &ExampleClass::InstanceConstNoexcept;
			Function InstanceConstLValueNoexceptDelegate = &ExampleClass::InstanceConstLValueNoexcept;
			Function InstanceConstRValueNoexceptDelegate = &ExampleClass::InstanceConstRValueNoexcept;
			Function InstanceVolatileDelegate = &ExampleClass::InstanceVolatile;
			Function InstanceVolatileLValueDelegate = &ExampleClass::InstanceVolatileLValue;
			Function InstanceVolatileRValueDelegate = &ExampleClass::InstanceVolatileRValue;
			Function InstanceVolatileNoexceptDelegate = &ExampleClass::InstanceVolatileNoexcept;
			Function InstanceVolatileLValueNoexceptDelegate = &ExampleClass::InstanceVolatileLValueNoexcept;
			Function InstanceVolatileRValueNoexceptDelegate = &ExampleClass::InstanceVolatileRValueNoexcept;
			Function InstanceConstVolatileDelegate = &ExampleClass::InstanceConstVolatile;
			Function InstanceConstVolatileLValueDelegate = &ExampleClass::InstanceConstVolatileLValue;
			Function InstanceConstVolatileRValueDelegate = &ExampleClass::InstanceConstVolatileRValue;
			Function InstanceConstVolatileNoexceptDelegate = &ExampleClass::InstanceConstVolatileNoexcept;
			Function InstanceConstVolatileLValueNoexceptDelegate = &ExampleClass::InstanceConstVolatileLValueNoexcept;
			Function InstanceConstVolatileRValueNoexceptDelegate = &ExampleClass::InstanceConstVolatileRValueNoexcept;
			
			Function LambdaDelegate0 = Lambda;	// will use ctor(const L&)
			Function LambdaDelegate1 = 
				[](const char* Input) -> void { std::cout << "Lambda(" << Input << ")" << std::endl; }; // will use ctor(L&&)
			
			// ...
			GlobalFunctionDelegate("GlobalFunction Input");
			GlobalNoexceptDelegate("GlobalNoexcept Input");
			GlobalThrowDelegate("GlobalThrow Input");
			NamespaceFunctionDelegate("NamespaceFunction Input");
			NamespaceNoexceptDelegate("NamespaceNoexcept Input");
			NamespaceThrowDelegate("NamespaceThrow Input");
			std::cout << std::endl;

			StaticMethodDelegate("StaticMethod Input");
			StaticNoexceptDelegate("StaticNoexcept Input");
			StaticThrowDelegate("StaticThrow Input");
			std::cout << std::endl;

			InstanceMethodDelegate(ExampleInstance, "InstanceMethod Input");
			InstanceLValueDelegate(ExampleInstance, "InstanceLValue Input");
			InstanceRValueDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceRValue Input");
			InstanceNoexceptDelegate(ExampleInstance, "InstanceNoexcept Input");
			InstanceLValueNoexceptDelegate(ExampleInstance, "InstanceLValueNoexcept Input");
			InstanceRValueNoexceptDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceRValueNoexcept Input");
			InstanceConstDelegate(ExampleInstance, "InstanceConst Input");
			InstanceConstLValueDelegate(ExampleInstance, "InstanceConstLValue Input");
			InstanceConstRValueDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceConstRValue Input");
			InstanceConstNoexceptDelegate(ExampleInstance, "InstanceConstNoexcept Input");
			InstanceConstLValueNoexceptDelegate(ExampleInstance, "InstanceConstLValueNoexcept Input");
			InstanceConstRValueNoexceptDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceConstRValueNoexcept Input");

			InstanceVolatileDelegate(ExampleInstance, "InstanceVolatile Input");
			InstanceVolatileLValueDelegate(ExampleInstance, "InstanceVolatileLValue Input");
			InstanceVolatileRValueDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceVolatileRValue Input");
			InstanceVolatileNoexceptDelegate(ExampleInstance, "InstanceVolatileNoexcept Input");
			InstanceVolatileLValueNoexceptDelegate(ExampleInstance, "InstanceVolatileLValueNoexcept Input");
			InstanceVolatileRValueNoexceptDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceVolatileRValueNoexcept Input");
			InstanceConstVolatileDelegate(ExampleInstance, "InstanceConstVolatile Input");
			InstanceConstVolatileLValueNoexceptDelegate(ExampleInstance, "InstanceConstVolatileLValue Input");
			InstanceConstVolatileRValueNoexceptDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceConstVolatileRValue Input");
			InstanceConstVolatileNoexceptDelegate(ExampleInstance, "InstanceConstVolatileNoexcept Input");
			InstanceConstVolatileLValueNoexceptDelegate(ExampleInstance, "InstanceConstVolatileLValueNoexcept Input");
			InstanceConstVolatileRValueNoexceptDelegate(Elysium::Core::Template::Functional::Move(ExampleInstance),
				"InstanceConstVolatileRValueNoexcept Input");
			std::cout << std::endl;

			LambdaDelegate0("LambdaMethod Input0");
			LambdaDelegate1("LambdaMethod Input1");
			//LambdaDelegate1("LambdaMethod Input1", "bla");
			
			// capture output and use Logger
			std::cout.rdbuf(originalCoutBuffer);
			std::string capturedOutput = captureStream.str();

			Logger::WriteMessage(&capturedOutput[0]);
		}
	};
}
