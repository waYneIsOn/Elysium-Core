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
	};

	TEST_CLASS(FunctionTests)
	{
	public:
		TEST_METHOD(AllKindsOfFunctionsAndMethods)
		{
			ExampleClass ExampleInstance = ExampleClass();
			auto Lambda = [](const char* Input) -> void { std::cout << "Lambda(" << Input << ")" << std::endl; };
			
			// prepare capture of std::cout
			std::ostringstream captureStream;
			std::streambuf* originalCoutBuffer = std::cout.rdbuf();
			std::cout.rdbuf(captureStream.rdbuf());

			// ...
			Function GlobalFunctionDelegate = &GlobalFunction;
			Function FunctionDelegate = &NamespaceFunction;
			Function StaticMethodDelegate = &ExampleClass::StaticMethod;
			//Function<void, const char*> LambdaDelegate = reinterpret_cast<void(*)(const char*)>(Lambda);
			Function LambdaDelegate = Function<void, const char*>(Lambda);
			Function<ExampleClass, void(const char*)> InstanceMethodDelegate =
				Function<ExampleClass, void(const char*)>(&ExampleInstance, &ExampleClass::InstanceMethod);

			GlobalFunctionDelegate("GlobalFunction Input");
			FunctionDelegate("Function Input");
			StaticMethodDelegate("StaticMethod Input");
			LambdaDelegate("LambdaMethod Input");
			InstanceMethodDelegate("InstanceMethod Input");

			// capture output and use Logger
			std::cout.rdbuf(originalCoutBuffer);
			std::string capturedOutput = captureStream.str();

			Logger::WriteMessage(&capturedOutput[0]);
		}
	};
}
