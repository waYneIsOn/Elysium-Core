#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/DefaultDeleter.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Memory;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Memory
{
	class DeleterLoggerClass
	{
	public:
		DeleterLoggerClass()
		{
			Count++;
			Logger::WriteMessage("called DeleterLoggerClass::DeleterLoggerClass()\r\n");
		}

		~DeleterLoggerClass()
		{
			Count--;
			Logger::WriteMessage("called DeleterLoggerClass::~DeleterLoggerClass()\r\n");
		}

		inline static Elysium::Core::Template::System::int32_t Count = 0;
	};

	TEST_CLASS(DeleterTests)
	{
	public:
		TEST_METHOD(DefaultDeleterTests)
		{
			Logger::WriteMessage("------------------------\r\n");
			DeleterLoggerClass* HeapInstance = new DeleterLoggerClass();
			DefaultDeleter<DeleterLoggerClass> DefaultDeleterInstance = DefaultDeleter<DeleterLoggerClass>();
			DefaultDeleterInstance(nullptr);
			DefaultDeleterInstance(HeapInstance);
			Assert::AreEqual(0, DeleterLoggerClass::Count);
			Logger::WriteMessage("------------------------\r\n");

			DeleterLoggerClass* HeapInstances = new DeleterLoggerClass[24];
			DefaultDeleter<DeleterLoggerClass[]> DefaultDeleterArrayInstance = DefaultDeleter<DeleterLoggerClass[]>();
			DefaultDeleterArrayInstance(nullptr);
			DefaultDeleterArrayInstance(HeapInstances);
			Assert::AreEqual(0, DeleterLoggerClass::Count);
			Logger::WriteMessage("------------------------\r\n");
		}
	};
}