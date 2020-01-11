#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Queue.hpp"

using namespace Elysium::Core::Collections::Template;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Template_Queue)
	{
	public:
		TEST_METHOD(Value)
		{
			int NumberOfElementsToQueue = 64;

			Queue<int> ValueQueue = Queue<int>();
			for (int i = 0; i < NumberOfElementsToQueue; i++)
			{
				ValueQueue.Enqueue(i);
			}
			Assert::AreEqual(static_cast<size_t>(NumberOfElementsToQueue), ValueQueue.GetCount());

			int Result;
			for (int i = 0; i < NumberOfElementsToQueue; i++)
			{
				Result = ValueQueue.Dequeue();
				Assert::AreEqual(i, Result);
			}
		}
	};
}