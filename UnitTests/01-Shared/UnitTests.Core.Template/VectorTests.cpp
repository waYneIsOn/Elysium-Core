#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(VectorTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			// Default constructor without elements
			Vector<uint32_t> EmptyInstance;
			Assert::AreEqual(0ULL, EmptyInstance.GetCapacity());
			Assert::AreEqual(0ULL, EmptyInstance.GetSize());

			// InitializerList
			Vector<uint32_t> InitializerListSmallerInstance = { 1, 2 };
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetCapacity());
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetSize());

			// Default constructor with elements
			Vector<uint32_t> Instance = Vector<uint32_t>(5);
			Assert::AreEqual(5ULL, Instance.GetCapacity());
			Assert::AreEqual(0ULL, Instance.GetSize());

			// Copy constructor
			Vector<uint32_t> CopiedInstance = Vector<uint32_t>(Instance);
			Assert::AreEqual(5ULL, CopiedInstance.GetCapacity());
			Assert::AreEqual(0ULL, CopiedInstance.GetSize());

			// Move constructor
			Vector<uint32_t> MovedInstance = Vector<uint32_t>(Move(Instance));
			Assert::AreEqual(5ULL, MovedInstance.GetCapacity());
			Assert::AreEqual(0ULL, MovedInstance.GetSize());
		}

		TEST_METHOD(Iterations)
		{
			// iterate using index/operator
			Vector<uint32_t> Instance = { 0, 1, 2, 3, 4 };
			for (size_t i = 0; i < Instance.GetSize(); i++)
			{
				uint32_t& Element = Instance[i];
				Assert::AreEqual(static_cast<uint32_t>(i), Element);
			}
			const size_t Length = Instance.GetSize();
			const Vector<uint32_t>& ConstInstance = Instance;

			// iterate using index/method
			for (size_t i = 0; i < Instance.GetSize(); i++)
			{
				uint32_t& Element = Instance.GetAt(i);
				Assert::AreEqual(static_cast<uint32_t>(i), Element);
			}

			// iterate using ForwardIterator-class
			uint32_t i = 0;
			for (Vector<uint32_t>::Iterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(i++, Element);
				Element = Length - i;
			}
			Assert::AreEqual(5_ui32, i);

			// iterate using ConstForwardIterator-class
			i = 0;
			for (Vector<uint32_t>::ConstIterator Iterator = ConstInstance.GetBegin(); Iterator != ConstInstance.GetEnd(); ++Iterator)
			{
				const uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(Length) - ++i, Element);
			}
			Assert::AreEqual(5_ui32, i);

			// iterate using BackwardIterator-class
			for (Vector<uint32_t>::ReverseIterator Iterator = Instance.GetReverseBegin(); Iterator != Instance.GetReverseEnd(); --Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(Length - i--), Element);
			}
			Assert::AreEqual(0_ui32, i);

			// iterate using ConstBackwardIterator-class
			i = static_cast<uint32_t>(Length);
			for (Vector<uint32_t>::ConstReverseIterator Iterator = ConstInstance.GetReverseBegin(); Iterator != ConstInstance.GetReverseEnd(); --Iterator)
			{
				const uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(Length - i--), Element);
			}
			Assert::AreEqual(0_ui32, i);

			/*
			// iterate using range-based-for-loop
			for (const uint32_t& Element : Instance)
			{
				Assert::AreEqual(i, Instance[i]);
				i++;
			}

			// iterate using foreach and lambda
			i = 0;
			foreach(Instance.GetFirst(), Instance.GetLast(),
				[](const uint32_t& Element)
			{
				// ...
			});
			*/
		}
	};
}