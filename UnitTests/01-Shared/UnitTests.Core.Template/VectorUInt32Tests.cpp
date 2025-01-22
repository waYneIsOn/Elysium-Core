#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/IndexOutOfRangeException.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(VectorOfUInt32Tests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			// Default constructor without elements
			Vector<uint32_t> EmptyInstance;
			Assert::AreEqual(1ULL, EmptyInstance.GetCapacity());
			Assert::AreEqual(0ULL, EmptyInstance.GetLength());

			// InitializerList
			Vector<uint32_t> InitializerListSmallerInstance = { 1, 2 };
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetCapacity());
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetLength());

			// Default constructor with elements
			Vector<uint32_t> Instance = Vector<uint32_t>(5);
			Instance.Clear();
			Assert::AreEqual(5ULL, Instance.GetCapacity());
			Assert::AreEqual(0ULL, Instance.GetLength());

			// Copy constructor
			Vector<uint32_t> CopiedInstance = Vector<uint32_t>(Instance);
			Assert::AreEqual(5ULL, CopiedInstance.GetCapacity());
			Assert::AreEqual(0ULL, CopiedInstance.GetLength());

			// Move constructor
			Vector<uint32_t> MovedInstance = Vector<uint32_t>(Move(Instance));
			Assert::AreEqual(5ULL, MovedInstance.GetCapacity());
			Assert::AreEqual(0ULL, MovedInstance.GetLength());
		}

		TEST_METHOD(IterationsThroughEmpty)
		{
			Vector<uint32_t> EmptyInstance = Vector<uint32_t>(0);
			Iterations(EmptyInstance);

			Vector<uint32_t> EmptyInstanceThroughInitializerList = Vector<uint32_t>({});
			Iterations(EmptyInstanceThroughInitializerList);
		}

		TEST_METHOD(IterationsThroughPopulated)
		{
			Vector<uint32_t> Instance = { 0, 1, 2, 3, 4 };
			Iterations(Instance);
		}

		TEST_METHOD(Accessing)
		{
			Vector<uint32_t> Instance = { 1, 2, 3 };
			const uint32_t& Value0 = Instance[0];
			const uint32_t& Value1 = Instance[1];
			const uint32_t& Value2 = Instance[2];
			const uint32_t& Value3 = Instance[3];

			uint32_t& At0 = Instance.GetAt(0);
			uint32_t& At1 = Instance.GetAt(1);
			uint32_t& At2 = Instance.GetAt(2);
			try
			{
				uint32_t& At3 = Instance.GetAt(3);
				Assert::Fail();
			}
			catch (const IndexOutOfRangeException& ex)
			{
			}
		}
		
		TEST_METHOD(Modifiers)
		{
			Vector<uint32_t> Instance = Vector<uint32_t>(1);
			Instance.Clear();
			Assert::AreEqual(static_cast<Elysium::Core::size>(0), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetCapacity());
			Assert::IsTrue(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(25);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.Reserve(4);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(25);
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(25);
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(25);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(25);
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PopBack();
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.ShrinkToFit();
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(25);
			Instance.PushBack(25);
			Instance.PushBack(25);
			Assert::AreEqual(static_cast<Elysium::Core::size>(7), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.ShrinkToFit();
			Assert::AreEqual(static_cast<Elysium::Core::size>(7), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(7), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.Clear();
			Assert::AreEqual(static_cast<Elysium::Core::size>(0), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(7), Instance.GetCapacity());
			Assert::IsTrue(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.ShrinkToFit();
			Assert::AreEqual(static_cast<Elysium::Core::size>(0), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(0), Instance.GetCapacity());
			Assert::IsTrue(Instance.GetIsEmpty());
			Assert::IsNull(Instance.GetData());

			Vector<uint32_t> SomeOtherInstance = { 3, 4, 5 };
			Instance.PushBackRange(&SomeOtherInstance[0], 3);
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::AreEqual(3_ui32, Instance[0]);
			Assert::AreEqual(4_ui32, Instance[1]);
			Assert::AreEqual(5_ui32, Instance[2]);

			Instance.PushBackRange(&SomeOtherInstance[1], 2);
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::AreEqual(3_ui32, Instance[0]);
			Assert::AreEqual(4_ui32, Instance[1]);
			Assert::AreEqual(5_ui32, Instance[2]);
			Assert::AreEqual(4_ui32, Instance[3]);
			Assert::AreEqual(5_ui32, Instance[4]);

			// @ToDo: need to check this block with another T to make sure the item really gets moved
			Instance.PopBack();
			Instance.PopBack();
			Instance.PushBack(Move(SomeOtherInstance.GetAt(0)));
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::AreEqual(3_ui32, Instance[0]);
			Assert::AreEqual(4_ui32, Instance[1]);
			Assert::AreEqual(5_ui32, Instance[2]);
			Assert::AreEqual(3_ui32, Instance[3]);
			Assert::AreEqual(3_ui32, SomeOtherInstance[0]);
			Assert::AreEqual(4_ui32, SomeOtherInstance[1]);
			Assert::AreEqual(5_ui32, SomeOtherInstance[2]);

			Instance.Assign(27, 5);
			Assert::AreEqual(static_cast<Elysium::Core::size>(9), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::AreEqual(3_ui32, Instance[0]);
			Assert::AreEqual(4_ui32, Instance[1]);
			Assert::AreEqual(5_ui32, Instance[2]);
			Assert::AreEqual(3_ui32, Instance[3]);
			Assert::AreEqual(27_ui32, Instance[4]);
			Assert::AreEqual(27_ui32, Instance[5]);
			Assert::AreEqual(27_ui32, Instance[6]);
			Assert::AreEqual(27_ui32, Instance[7]);
			Assert::AreEqual(27_ui32, Instance[8]);

			Instance.Insert(4, 33);
			Assert::AreEqual(static_cast<Elysium::Core::size>(10), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::AreEqual(3_ui32, Instance[0]);
			Assert::AreEqual(4_ui32, Instance[1]);
			Assert::AreEqual(5_ui32, Instance[2]);
			Assert::AreEqual(3_ui32, Instance[3]);
			Assert::AreEqual(33_ui32, Instance[4]);
			Assert::AreEqual(27_ui32, Instance[5]);
			Assert::AreEqual(27_ui32, Instance[6]);
			Assert::AreEqual(27_ui32, Instance[7]);
			Assert::AreEqual(27_ui32, Instance[8]);
			Assert::AreEqual(27_ui32, Instance[9]);
			Assert::AreEqual(0_ui32, Instance[10]);
			
			// insert in between length and capacity
			Instance.Insert(13, 5448);
			Assert::AreEqual(static_cast<Elysium::Core::size>(13), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::AreEqual(3_ui32, Instance[0]);
			Assert::AreEqual(4_ui32, Instance[1]);
			Assert::AreEqual(5_ui32, Instance[2]);
			Assert::AreEqual(3_ui32, Instance[3]);
			Assert::AreEqual(33_ui32, Instance[4]);
			Assert::AreEqual(27_ui32, Instance[5]);
			Assert::AreEqual(27_ui32, Instance[6]);
			Assert::AreEqual(27_ui32, Instance[7]);
			Assert::AreEqual(27_ui32, Instance[8]);
			Assert::AreEqual(27_ui32, Instance[9]);
			Assert::AreEqual(0_ui32, Instance[10]);
			Assert::AreEqual(0_ui32, Instance[11]);
			Assert::AreEqual(0_ui32, Instance[12]);
			Assert::AreEqual(5448_ui32, Instance[13]);
			/*
			// insert behind capacity
			Instance.Insert(17, 5448);
			Assert::Fail();
			*/
		}
	private:
		void Iterations(Vector<uint32_t>& Instance)
		{
			const Elysium::Core::size Length = Instance.GetLength();
			const Vector<uint32_t>& ConstInstance = Instance;

			// iterate using index/operator
			for (Elysium::Core::size i = 0; i < Instance.GetLength(); i++)
			{
				const uint32_t& Element = Instance[i];
				Assert::AreEqual(static_cast<uint32_t>(i), Element);
			}

			// iterate using index/method
			for (Elysium::Core::size i = 0; i < Instance.GetLength(); i++)
			{
				uint32_t& Element = Instance.GetAt(i);
				Assert::AreEqual(static_cast<uint32_t>(i), Element);
			}

			// iterate using ForwardIterator-class
			uint32_t i = 0;
			for (Vector<uint32_t>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(i++, Element);
			}
			Assert::AreEqual(static_cast<uint32_t>(Length), i);

			// iterate using ConstForwardIterator-class
			i = 0;
			for (Vector<uint32_t>::ConstIterator Iterator = ConstInstance.GetBegin(); Iterator != ConstInstance.GetEnd(); ++Iterator)
			{
				const uint32_t& Element = *Iterator;
				Assert::AreEqual(i++, Element);
			}
			Assert::AreEqual(static_cast<uint32_t>(Length), i);

			// iterate using BackwardIterator-class
			for (Vector<uint32_t>::ReverseIterator Iterator = Instance.GetReverseBegin(); Iterator != Instance.GetReverseEnd(); --Iterator)
			{
				uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(--i), Element);
			}
			Assert::AreEqual(0_ui32, i);

			// iterate using ConstBackwardIterator-class
			i = static_cast<uint32_t>(Length);
			for (Vector<uint32_t>::ConstReverseIterator Iterator = ConstInstance.GetReverseBegin(); Iterator != ConstInstance.GetReverseEnd(); --Iterator)
			{
				const uint32_t& Element = *Iterator;
				Assert::AreEqual(static_cast<uint32_t>(--i), Element);
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