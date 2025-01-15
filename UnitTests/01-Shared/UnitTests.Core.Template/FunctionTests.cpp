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

namespace UnitTests::Core::Template::Container
{
	void NamespaceFunction(const char* Input)
	{
		std::cout << "Function(" << Input << ")" << std::endl;
	}

	class ExampleClass
	{
	public:
		static void StaticMethod(const char* Input)
		{
			std::cout << "StaticMethod(" << Input << ")" << std::endl;
		}

		void InstanceMethod(const char* Input)
		{
			std::cout << "InstanceMethod(" << Input << ")" << std::endl;
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
			Function FunctionDelegate = &NamespaceFunction;
			Function StaticMethodDelegate = &ExampleClass::StaticMethod;
			Function LambdaDelegate0 = Lambda;	// will use ctor(const L&)
			Function LambdaDelegate1 = 
				[](const char* Input) -> void { std::cout << "Lambda(" << Input << ")" << std::endl; }; // will use ctor(L&&)
			Function InstanceMethodDelegate (&ExampleInstance, &ExampleClass::InstanceMethod);
			
			GlobalFunctionDelegate("GlobalFunction Input");
			FunctionDelegate("Function Input");
			StaticMethodDelegate("StaticMethod Input");
			LambdaDelegate0("LambdaMethod Input0");
			LambdaDelegate1("LambdaMethod Input1");
			//LambdaDelegate1("LambdaMethod Input1", "bla");
			InstanceMethodDelegate("InstanceMethod Input");
			
			// capture output and use Logger
			std::cout.rdbuf(originalCoutBuffer);
			std::string capturedOutput = captureStream.str();

			Logger::WriteMessage(&capturedOutput[0]);
		}
	};
}
