#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/FixedSizeHeapArray.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Mallocator.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Collections;
using namespace Elysium::Core::Template::TypeTraits;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template
{
	TEST_CLASS(FixedSizeHeapArrayTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			// Default constructor without elements
			FixedSizeHeapArray<uint32_t, 0> EmptyInstance;
			Assert::AreEqual(0ULL, EmptyInstance.GetLength());

			// Default constructor with elements (and memset)
			FixedSizeHeapArray<uint32_t, 5> Instance = FixedSizeHeapArray<uint32_t, 5>(true);
			Instance[0] = 10;
			Instance[1] = 11;
			Instance[2] = 12;
			Instance[3] = 13;
			Instance[4] = 14;
			Assert::AreEqual(5ULL, Instance.GetLength());
			Assert::AreEqual(10ui32, Instance[0]);
			Assert::AreEqual(11ui32, Instance[1]);
			Assert::AreEqual(12ui32, Instance[2]);
			Assert::AreEqual(13ui32, Instance[3]);
			Assert::AreEqual(14ui32, Instance[4]);
			
			// Copy constructor
			FixedSizeHeapArray<uint32_t, 5> CopiedInstance = FixedSizeHeapArray<uint32_t, 5>(Instance);
			Assert::AreEqual(5ULL, CopiedInstance.GetLength());
			Assert::AreEqual(10ui32, CopiedInstance[0]);
			Assert::AreEqual(11ui32, CopiedInstance[1]);
			Assert::AreEqual(12ui32, CopiedInstance[2]);
			Assert::AreEqual(13ui32, CopiedInstance[3]);
			Assert::AreEqual(14ui32, CopiedInstance[4]);
			
			// Move constructor
			FixedSizeHeapArray<uint32_t, 5> MovedInstance = FixedSizeHeapArray<uint32_t, 5>(Move(CopiedInstance));
			Assert::AreEqual(5ULL, MovedInstance.GetLength());
			Assert::AreEqual(10ui32, MovedInstance[0]);
			Assert::AreEqual(11ui32, MovedInstance[1]);
			Assert::AreEqual(12ui32, MovedInstance[2]);
			Assert::AreEqual(13ui32, MovedInstance[3]);
			Assert::AreEqual(14ui32, MovedInstance[4]);

			Assert::AreEqual(5ULL, CopiedInstance.GetLength());
			Assert::AreEqual(0ui32, CopiedInstance[0]);
			Assert::AreEqual(0ui32, CopiedInstance[1]);
			Assert::AreEqual(0ui32, CopiedInstance[2]);
			Assert::AreEqual(0ui32, CopiedInstance[3]);
			Assert::AreEqual(0ui32, CopiedInstance[4]);
			
			// Default constructor using MAllocator
			FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>> MAllocInstance = FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>>(true);
			MAllocInstance[0] = 10;
			MAllocInstance[1] = 11;
			MAllocInstance[2] = 12;
			Assert::AreEqual(3ULL, MAllocInstance.GetLength());
			Assert::AreEqual(10ui32, MovedInstance[0]);
			Assert::AreEqual(11ui32, MovedInstance[1]);
			Assert::AreEqual(12ui32, MovedInstance[2]);

			// Copy constructor for MAllocated-array
			FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>> CopiedMAllocInstance = FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>>(MAllocInstance);
			Assert::AreEqual(3ULL, CopiedMAllocInstance.GetLength());
			Assert::AreEqual(10ui32, CopiedMAllocInstance[0]);
			Assert::AreEqual(11ui32, CopiedMAllocInstance[1]);
			Assert::AreEqual(12ui32, CopiedMAllocInstance[2]);
			
			// Move constructor for MAllocated-array
			FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>> MovedMAllocInstance = FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>>(Move(CopiedMAllocInstance));
			Assert::AreEqual(3ULL, MovedMAllocInstance.GetLength());
			Assert::AreEqual(10ui32, MovedMAllocInstance[0]);
			Assert::AreEqual(11ui32, MovedMAllocInstance[1]);
			Assert::AreEqual(12ui32, MovedMAllocInstance[2]);

			Assert::AreEqual(3ULL, CopiedMAllocInstance.GetLength());
			Assert::AreEqual(0ui32, CopiedMAllocInstance[0]);
			Assert::AreEqual(0ui32, CopiedMAllocInstance[1]);
			Assert::AreEqual(0ui32, CopiedMAllocInstance[2]);
		}

		TEST_METHOD(Iteratorions)
		{
			const size_t Length = 5;

			// iterate using index
			FixedSizeHeapArray<uint32_t, Length> Instance = FixedSizeHeapArray<uint32_t, Length>(true);
			for (size_t i = 0; i < Instance.GetLength(); i++)
			{
				Instance[i] = static_cast<uint32_t>(i);
			}
			
			// iterate using ForwardIterator-class
			uint32_t i = 0;
			for (FixedSizeHeapArray<uint32_t, Length>::Iterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(i++, Element);
				Element = Length - i;
			}
			Assert::AreEqual(5ui32, i);
			
			// iterate using BackwardIterator-class
			for (FixedSizeHeapArray<uint32_t, Length>::ReverseIterator Iterator = Instance.GetReverseBegin(); Iterator != Instance.GetReverseEnd(); --Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(Length - i--), Element);
			}
			Assert::AreEqual(0ui32, i);
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
