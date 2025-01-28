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
	TEST_CLASS(VectorOfBoolTests)
	{
		TEST_METHOD(Constructors)
		{
			// Default constructor without elements
			Vector<bool> EmptyInstance;
			Assert::AreEqual(1ULL, EmptyInstance.GetCapacity());
			Assert::AreEqual(0ULL, EmptyInstance.GetLength());

			// InitializerList
			Vector<bool> InitializerListSmallerInstance = { true, false };
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetCapacity());
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetLength());

			// Default constructor with elements
			Vector<bool> Instance = Vector<bool>(5);
			Instance.Clear();
			Assert::AreEqual(5ULL, Instance.GetCapacity());
			Assert::AreEqual(0ULL, Instance.GetLength());

			// Copy constructor
			Vector<bool> CopiedInstance = Vector<bool>(Instance);
			Assert::AreEqual(5ULL, CopiedInstance.GetCapacity());
			Assert::AreEqual(0ULL, CopiedInstance.GetLength());

			// Move constructor
			Vector<bool> MovedInstance = Vector<bool>(Move(Instance));
			Assert::AreEqual(5ULL, MovedInstance.GetCapacity());
			Assert::AreEqual(0ULL, MovedInstance.GetLength());
		}

		TEST_METHOD(IterationsThroughEmpty)
		{
			Vector<bool> EmptyInstance = Vector<bool>(0);
			Iterations(EmptyInstance);

			Vector<bool> EmptyInstanceThroughInitializerList = Vector<bool>({});
			Iterations(EmptyInstanceThroughInitializerList);
		}

		TEST_METHOD(IterationsThroughPopulated)
		{
			Vector<bool> Instance = { false, true, false, true, false };
			Iterations(Instance);
		}

		TEST_METHOD(Accessing)
		{
			Vector<bool> Instance = { true, false, true };
			const bool& Value0 = Instance[0];
			const bool& Value1 = Instance[1];
			const bool& Value2 = Instance[2];
			const bool& Value3 = Instance[3];

			bool& At0 = Instance.GetAt(0);
			bool& At1 = Instance.GetAt(1);
			bool& At2 = Instance.GetAt(2);
			try
			{
				bool& At3 = Instance.GetAt(3);
				Assert::Fail();
			}
			catch (const IndexOutOfRangeException& ex)
			{
			}
		}

		TEST_METHOD(Modifiers)
		{
			Vector<bool> Instance = Vector<bool>(1);
			Instance.Clear();
			Assert::AreEqual(static_cast<Elysium::Core::size>(0), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetCapacity());
			Assert::IsTrue(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(true);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.Reserve(4);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(false);
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(true);
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(false);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsFalse(Instance.GetIsEmpty());
			Assert::IsNotNull(Instance.GetData());

			Instance.PushBack(true);
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

			Instance.PushBack(false);
			Instance.PushBack(true);
			Instance.PushBack(false);
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

			Vector<bool> SomeOtherInstance = { true, false, true };
			Instance.PushBackRange(&SomeOtherInstance[0], 3);
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::IsTrue(Instance[0]);
			Assert::IsFalse(Instance[1]);
			Assert::IsTrue(Instance[2]);

			Instance.PushBackRange(&SomeOtherInstance[1], 2);
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::IsTrue(Instance[0]);
			Assert::IsFalse(Instance[1]);
			Assert::IsTrue(Instance[2]);
			Assert::IsFalse(Instance[3]);
			Assert::IsTrue(Instance[4]);
			
			Instance.PopBack();
			Instance.PopBack();
			Instance.PushBack(Move(SomeOtherInstance.GetAt(0)));
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::IsTrue(Instance[0]);
			Assert::IsFalse(Instance[1]);
			Assert::IsTrue(Instance[2]);
			Assert::IsTrue(Instance[3]);
			Assert::IsTrue(SomeOtherInstance[0]);
			Assert::IsFalse(SomeOtherInstance[1]);
			Assert::IsTrue(SomeOtherInstance[2]);
			
			Instance.Assign(false, 5);
			Assert::AreEqual(static_cast<Elysium::Core::size>(9), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::IsTrue(Instance[0]);
			Assert::IsFalse(Instance[1]);
			Assert::IsTrue(Instance[2]);
			Assert::IsTrue(Instance[3]);
			Assert::IsFalse(Instance[4]);
			Assert::IsFalse(Instance[5]);
			Assert::IsFalse(Instance[6]);
			Assert::IsFalse(Instance[7]);
			Assert::IsFalse(Instance[8]);
			
			Instance.Insert(4, true);
			Assert::AreEqual(static_cast<Elysium::Core::size>(10), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::IsTrue(Instance[0]);
			Assert::IsFalse(Instance[1]);
			Assert::IsTrue(Instance[2]);
			Assert::IsTrue(Instance[3]);
			Assert::IsTrue(Instance[4]);
			Assert::IsFalse(Instance[5]);
			Assert::IsFalse(Instance[6]);
			Assert::IsFalse(Instance[7]);
			Assert::IsFalse(Instance[8]);
			Assert::IsFalse(Instance[9]);
			Assert::IsFalse(Instance[10]);
			
			// insert in between length and capacity
			Instance.Insert(13, true);
			Assert::AreEqual(static_cast<Elysium::Core::size>(13), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::IsTrue(Instance[0]);
			Assert::IsFalse(Instance[1]);
			Assert::IsTrue(Instance[2]);
			Assert::IsTrue(Instance[3]);
			Assert::IsTrue(Instance[4]);
			Assert::IsFalse(Instance[5]);
			Assert::IsFalse(Instance[6]);
			Assert::IsFalse(Instance[7]);
			Assert::IsFalse(Instance[8]);
			Assert::IsFalse(Instance[9]);
			Assert::IsFalse(Instance[10]);
			Assert::IsFalse(Instance[11]);
			Assert::IsFalse(Instance[12]);
			Assert::IsTrue(Instance[13]);
			/*
			// insert behind capacity
			Instance.Insert(17, 5448);
			Assert::Fail();
			*/
		}
	private:
		void Iterations(Vector<bool>& Instance)
		{
			const Elysium::Core::size Length = Instance.GetLength();
			const Vector<bool>& ConstInstance = Instance;

			// iterate using index/operator
			for (Elysium::Core::size i = 0; i < Instance.GetLength(); i++)
			{
				const bool& Element = !Instance[i];
				Assert::AreEqual(i % 2 == 0, Element);
			}

			// iterate using index/method
			for (Elysium::Core::size i = 0; i < Instance.GetLength(); i++)
			{
				const bool& Element = !Instance[i];
				Assert::AreEqual(i % 2 == 0, Element);
			}

			// iterate using ForwardIterator-class
			uint32_t i = 0;
			for (Vector<bool>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				const bool& Element = !*Iterator;
				Assert::AreEqual(i++ % 2 == 0, Element);
			}
			Assert::AreEqual(static_cast<uint32_t>(Length), i);

			// iterate using ConstForwardIterator-class
			i = 0;
			for (Vector<bool>::ConstIterator Iterator = ConstInstance.GetBegin(); Iterator != ConstInstance.GetEnd(); ++Iterator)
			{
				const bool& Element = !*Iterator;
				Assert::AreEqual(i++ % 2 == 0, Element);
			}
			Assert::AreEqual(static_cast<uint32_t>(Length), i);

			// iterate using BackwardIterator-class
			for (Vector<bool>::ReverseIterator Iterator = Instance.GetReverseBegin(); Iterator != Instance.GetReverseEnd(); --Iterator)
			{
				const bool& Element = !*Iterator;
				Assert::AreEqual(--i % 2 == 0, Element);
			}
			Assert::AreEqual(0_ui32, i);

			// iterate using ConstBackwardIterator-class
			i = static_cast<uint32_t>(Length);
			for (Vector<bool>::ConstReverseIterator Iterator = ConstInstance.GetReverseBegin(); Iterator != ConstInstance.GetReverseEnd(); --Iterator)
			{
				const bool& Element = !*Iterator;
				Assert::AreEqual(--i % 2 == 0, Element);
			}
			Assert::AreEqual(0_ui32, i);
		}
	};
}
