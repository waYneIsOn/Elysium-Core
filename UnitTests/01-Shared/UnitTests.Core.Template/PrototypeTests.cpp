#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Action.hpp"

#include <iostream>

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void GlobalFunction(const char* Input) 
{ 
	std::cout << "GlobalFunction(" << Input << ")" << std::endl;
}

namespace Prototype
{
	void Function(const char* Input)
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

	template <class ReturnType, class ...Args>
	class TestDelegate
	{
	public:
		TestDelegate(ReturnType(*FunctionOrStaticMethod)(Args...))
			: _FunctionOrStaticMethod(FunctionOrStaticMethod)
		{ }

		~TestDelegate()
		{ }
	public:
		TestDelegate& operator=(ReturnType(*FunctionOrStaticMethod)(Args...))
		{
			return TestDelegate(FunctionOrStaticMethod);
		}
	public:
		ReturnType operator()(Args... Parameters) const
		{
			return (*_FunctionOrStaticMethod)(Parameters...);
		}
	private:
		ReturnType(*_FunctionOrStaticMethod)(Args...);
	};

	template <class Type, class ReturnType, class ...Args>
	class TestDelegate<Type, ReturnType(Args...)>
	{ 
	public:
		TestDelegate(Type* Instance, ReturnType(Type::* Method)(Args...))
			: _Instance(Instance), _Method(Method)
		{ }

		~TestDelegate()
		{ }
	public:
		ReturnType operator()(Args... Parameters) const
		{
			return (_Instance->*_Method)(Parameters...);
		}
	private:
		Type* _Instance;
		ReturnType(Type::* _Method)(Args...);
	};

	TEST_CLASS(PrototypeTests)
	{
	public:
		TEST_METHOD(Example)
		{  
			// prepare capture of std::cout
			std::ostringstream captureStream;
			std::streambuf* originalCoutBuffer = std::cout.rdbuf();
			std::cout.rdbuf(captureStream.rdbuf());

			// ...
			//TestDelegate GlobalFunctionDelegate = TestDelegate<void>::Bind<GlobalFunction>();
			TestDelegate GlobalFunctionDelegate = &GlobalFunction;
			GlobalFunctionDelegate("GlobalFunction Input");

			// ...
			TestDelegate FunctionDelegate = &Function;
			FunctionDelegate("Function Input");

			// ...
			TestDelegate StaticMethodDelegate = &ExampleClass::StaticMethod;
			StaticMethodDelegate("StaticMethod Input");

			// ...
			TestDelegate LambdaDelegate = TestDelegate<float, int>( [](int x) -> float { return (float)x * x; });
			float x = LambdaDelegate(2);

			// ...
			ExampleClass ExampleInstance = ExampleClass();
			TestDelegate InstanceMethodDelegate = TestDelegate<ExampleClass, void(const char*)>(&ExampleInstance, &ExampleClass::InstanceMethod);
			InstanceMethodDelegate("InstanceMethod Input");

			// capture output and use Logger
			std::cout.rdbuf(originalCoutBuffer);
			std::string capturedOutput = captureStream.str();

			Logger::WriteMessage(&capturedOutput[0]);
		}
	};
}
