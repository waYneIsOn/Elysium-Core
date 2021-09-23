#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/FixedSizeHeapArray.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Mallocator.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Elysium::Core::Template::TypeTraits;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(FixedSizeArrayTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			// Default constructor without elements
			FixedSizeHeapArray<uint32_t, 0> EmptyInstance;
			Assert::AreEqual(0ULL, EmptyInstance.GetSize());

			// InitializerList (smaller than Instance)
			FixedSizeHeapArray<uint32_t, 3> InitializerListSmallerInstance = { 1, 2 };
			Assert::AreEqual(3ULL, InitializerListSmallerInstance.GetSize());
			Assert::AreEqual(1ui32, InitializerListSmallerInstance[0]);
			Assert::AreEqual(2ui32, InitializerListSmallerInstance[1]);
			Assert::AreEqual(3452816845ui32, InitializerListSmallerInstance[2]);

			// InitializerList (larger than Instance)
			FixedSizeHeapArray<uint32_t, 3> InitializerListLargerInstance = { 1, 2, 3, 4 };
			Assert::AreEqual(3ULL, InitializerListLargerInstance.GetSize());
			Assert::AreEqual(1ui32, InitializerListLargerInstance[0]);
			Assert::AreEqual(2ui32, InitializerListLargerInstance[1]);
			Assert::AreEqual(3ui32, InitializerListLargerInstance[2]);

			// InitializerList (same size as Instance)
			FixedSizeHeapArray<uint32_t, 3> InitializerListInstance = { 1, 2, 4 };
			Assert::AreEqual(3ULL, InitializerListInstance.GetSize());
			Assert::AreEqual(1ui32, InitializerListInstance[0]);
			Assert::AreEqual(2ui32, InitializerListInstance[1]);
			Assert::AreEqual(4ui32, InitializerListInstance[2]);

			// Default constructor with elements
			FixedSizeHeapArray<uint32_t, 5> Instance = FixedSizeHeapArray<uint32_t, 5>();
			Instance[0] = 10;
			Instance[1] = 11;
			Instance[2] = 12;
			Instance[3] = 13;
			Instance[4] = 14;
			Assert::AreEqual(5ULL, Instance.GetSize());
			Assert::AreEqual(10_ui32, Instance[0]);
			Assert::AreEqual(11_ui32, Instance[1]);
			Assert::AreEqual(12_ui32, Instance[2]);
			Assert::AreEqual(13_ui32, Instance[3]);
			Assert::AreEqual(14_ui32, Instance[4]);
			
			// Copy constructor
			FixedSizeHeapArray<uint32_t, 5> CopiedInstance = FixedSizeHeapArray<uint32_t, 5>(Instance);
			Assert::AreEqual(5ULL, CopiedInstance.GetSize());
			Assert::AreEqual(10_ui32, CopiedInstance[0]);
			Assert::AreEqual(11_ui32, CopiedInstance[1]);
			Assert::AreEqual(12_ui32, CopiedInstance[2]);
			Assert::AreEqual(13_ui32, CopiedInstance[3]);
			Assert::AreEqual(14_ui32, CopiedInstance[4]);
			
			// Move constructor
			FixedSizeHeapArray<uint32_t, 5> MovedInstance = FixedSizeHeapArray<uint32_t, 5>(Move(CopiedInstance));
			Assert::AreEqual(5ULL, MovedInstance.GetSize());
			Assert::AreEqual(10_ui32, MovedInstance[0]);
			Assert::AreEqual(11_ui32, MovedInstance[1]);
			Assert::AreEqual(12_ui32, MovedInstance[2]);
			Assert::AreEqual(13_ui32, MovedInstance[3]);
			Assert::AreEqual(14_ui32, MovedInstance[4]);

			Assert::AreEqual(5ULL, CopiedInstance.GetSize());
			Assert::AreEqual(0_ui32, CopiedInstance[0]);
			Assert::AreEqual(0_ui32, CopiedInstance[1]);
			Assert::AreEqual(0_ui32, CopiedInstance[2]);
			Assert::AreEqual(0_ui32, CopiedInstance[3]);
			Assert::AreEqual(0_ui32, CopiedInstance[4]);
			
			// Default constructor using MAllocator
			FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>> MAllocInstance = FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>>();
			MAllocInstance[0] = 10;
			MAllocInstance[1] = 11;
			MAllocInstance[2] = 12;
			Assert::AreEqual(3ULL, MAllocInstance.GetSize());
			Assert::AreEqual(10_ui32, MovedInstance[0]);
			Assert::AreEqual(11_ui32, MovedInstance[1]);
			Assert::AreEqual(12_ui32, MovedInstance[2]);

			// Copy constructor for MAllocated-array
			FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>> CopiedMAllocInstance = FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>>(MAllocInstance);
			Assert::AreEqual(3ULL, CopiedMAllocInstance.GetSize());
			Assert::AreEqual(10_ui32, CopiedMAllocInstance[0]);
			Assert::AreEqual(11_ui32, CopiedMAllocInstance[1]);
			Assert::AreEqual(12_ui32, CopiedMAllocInstance[2]);
			
			// Move constructor for MAllocated-array
			FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>> MovedMAllocInstance = FixedSizeHeapArray<uint32_t, 3, MAllocator<uint32_t>>(Move(CopiedMAllocInstance));
			Assert::AreEqual(3ULL, MovedMAllocInstance.GetSize());
			Assert::AreEqual(10_ui32, MovedMAllocInstance[0]);
			Assert::AreEqual(11_ui32, MovedMAllocInstance[1]);
			Assert::AreEqual(12_ui32, MovedMAllocInstance[2]);

			Assert::AreEqual(3ULL, CopiedMAllocInstance.GetSize());
			Assert::AreEqual(0_ui32, CopiedMAllocInstance[0]);
			Assert::AreEqual(0_ui32, CopiedMAllocInstance[1]);
			Assert::AreEqual(0_ui32, CopiedMAllocInstance[2]);
		}

		TEST_METHOD(Iterations)
		{
			const size_t Length = 5;

			// iterate using index/operator
			FixedSizeHeapArray<uint32_t, Length> Instance = { 0, 1, 2, 3, 4 };
			for (size_t i = 0; i < Instance.GetSize(); i++)
			{
				uint32_t& Element = Instance[i];
				Assert::AreEqual(static_cast<uint32_t>(i), Element);
			}
			const FixedSizeHeapArray<uint32_t, Length>& ConstInstance = Instance;

			// iterate using index/method
			for (size_t i = 0; i < Instance.GetSize(); i++)
			{
				uint32_t& Element = Instance.GetAt(i);
				Assert::AreEqual(static_cast<uint32_t>(i), Element);
			}

			// iterate using ForwardIterator-class
			uint32_t i = 0;
			for (FixedSizeHeapArray<uint32_t, Length>::Iterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(i++, Element);
				Element = Length - i;
			}
			Assert::AreEqual(5_ui32, i);
			
			// iterate using ConstForwardIterator-class
			i = 0;
			for (FixedSizeHeapArray<uint32_t, Length>::ConstIterator Iterator = ConstInstance.GetBegin(); Iterator != ConstInstance.GetEnd(); ++Iterator)
			{
				const uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(Length) - ++i, Element);
			}
			Assert::AreEqual(5_ui32, i);
			
			// iterate using BackwardIterator-class
			for (FixedSizeHeapArray<uint32_t, Length>::ReverseIterator Iterator = Instance.GetReverseBegin(); Iterator != Instance.GetReverseEnd(); --Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(Length - i--), Element);
			}
			Assert::AreEqual(0_ui32, i);
			
			// iterate using ConstBackwardIterator-class
			i = static_cast<uint32_t>(Length);
			for (FixedSizeHeapArray<uint32_t, Length>::ConstReverseIterator Iterator = ConstInstance.GetReverseBegin(); Iterator != ConstInstance.GetReverseEnd(); --Iterator)
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
