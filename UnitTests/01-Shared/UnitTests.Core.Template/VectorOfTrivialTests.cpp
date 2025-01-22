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
	class Trivial
	{
	public:
		Trivial() = default;

		Trivial(float Value)
			: X(Value), Y(Value)
		{ }

		Trivial(float x, double y)
			: X(x), Y(y)
		{ }
	public:
		float X;
		double Y;
	};

	TEST_CLASS(VectorOfTrivialTests)
	{
		TEST_METHOD(Constructors)
		{
			// Default constructor without elements
			Vector<Trivial> EmptyInstance;
			Assert::AreEqual(1ULL, EmptyInstance.GetCapacity());
			Assert::AreEqual(0ULL, EmptyInstance.GetLength());

			// InitializerList
			Vector<Trivial> InitializerListSmallerInstance = { Trivial(), Trivial() };
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetCapacity());
			Assert::AreEqual(2ULL, InitializerListSmallerInstance.GetLength());

			// Default constructor with elements
			Vector<Trivial> Instance = Vector<Trivial>(5);
			Instance.Clear();
			Assert::AreEqual(5ULL, Instance.GetCapacity());
			Assert::AreEqual(0ULL, Instance.GetLength());

			// Copy constructor
			Vector<Trivial> CopiedInstance = Vector<Trivial>(Instance);
			Assert::AreEqual(5ULL, CopiedInstance.GetCapacity());
			Assert::AreEqual(0ULL, CopiedInstance.GetLength());

			// Move constructor
			Vector<Trivial> MovedInstance = Vector<Trivial>(Move(Instance));
			Assert::AreEqual(5ULL, MovedInstance.GetCapacity());
			Assert::AreEqual(0ULL, MovedInstance.GetLength());
		}

		TEST_METHOD(IterationsThroughEmpty)
		{
			Vector<Trivial> EmptyInstance = Vector<Trivial>(0);
			Iterations(EmptyInstance);

			Vector<Trivial> EmptyInstanceThroughInitializerList = Vector<Trivial>({});
			Iterations(EmptyInstanceThroughInitializerList);
		}

		TEST_METHOD(IterationsThroughPopulated)
		{
			Vector<Trivial> Instance = { Trivial(0), Trivial(1), Trivial(2), Trivial(3), Trivial(4) };
			Iterations(Instance);
		}

		TEST_METHOD(Accessing)
		{
			Vector<Trivial> Instance = { Trivial(1), Trivial(2), Trivial(3) };
			const Trivial& Value0 = Instance[0];
			const Trivial& Value1 = Instance[1];
			const Trivial& Value2 = Instance[2];
			const Trivial& Value3 = Instance[3];

			Trivial& At0 = Instance.GetAt(0);
			Trivial& At1 = Instance.GetAt(1);
			Trivial& At2 = Instance.GetAt(2);
			try
			{
				Trivial& At3 = Instance.GetAt(3);
				Assert::Fail();
			}
			catch (const IndexOutOfRangeException& ex)
			{
			}
		}

		TEST_METHOD(Modifiers)
		{
			Vector<Trivial> Instance = Vector<Trivial>(1);
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

			Vector<Trivial> SomeOtherInstance = { Trivial(3), Trivial(4), Trivial(5) };
			Instance.PushBackRange(&SomeOtherInstance[0], 3);
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetCapacity());
			Assert::AreEqual(3.0f, Instance[0].X);
			Assert::AreEqual(4.0f, Instance[1].X);
			Assert::AreEqual(5.0f, Instance[2].X);

			Instance.PushBackRange(&SomeOtherInstance[1], 2);
			Assert::AreEqual(static_cast<Elysium::Core::size>(5), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::AreEqual(3.0f, Instance[0].X);
			Assert::AreEqual(4.0f, Instance[1].X);
			Assert::AreEqual(5.0f, Instance[2].X);
			Assert::AreEqual(4.0f, Instance[3].X);
			Assert::AreEqual(5.0f, Instance[4].X);

			// @ToDo: need to check this block with another T to make sure the item really gets moved
			Instance.PopBack();
			Instance.PopBack();
			Instance.PushBack(Move(SomeOtherInstance.GetAt(0)));
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), Instance.GetCapacity());
			Assert::AreEqual(3.0f, Instance[0].X);
			Assert::AreEqual(4.0f, Instance[1].X);
			Assert::AreEqual(5.0f, Instance[2].X);
			Assert::AreEqual(3.0f, Instance[3].X);
			Assert::AreEqual(3.0f, SomeOtherInstance[0].X);
			Assert::AreEqual(4.0f, SomeOtherInstance[1].X);
			Assert::AreEqual(5.0f, SomeOtherInstance[2].X);

			Instance.Assign(27, 5);
			Assert::AreEqual(static_cast<Elysium::Core::size>(9), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::AreEqual(3.0f, Instance[0].X);
			Assert::AreEqual(4.0f, Instance[1].X);
			Assert::AreEqual(5.0f, Instance[2].X);
			Assert::AreEqual(3.0f, Instance[3].X);
			Assert::AreEqual(27.0f, Instance[4].X);
			Assert::AreEqual(27.0f, Instance[5].X);
			Assert::AreEqual(27.0f, Instance[6].X);
			Assert::AreEqual(27.0f, Instance[7].X);
			Assert::AreEqual(27.0f, Instance[8].X);

			Instance.Insert(4, 33);
			Assert::AreEqual(static_cast<Elysium::Core::size>(10), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::AreEqual(3.0f, Instance[0].X);
			Assert::AreEqual(4.0f, Instance[1].X);
			Assert::AreEqual(5.0f, Instance[2].X);
			Assert::AreEqual(3.0f, Instance[3].X);
			Assert::AreEqual(33.0f, Instance[4].X);
			Assert::AreEqual(27.0f, Instance[5].X);
			Assert::AreEqual(27.0f, Instance[6].X);
			Assert::AreEqual(27.0f, Instance[7].X);
			Assert::AreEqual(27.0f, Instance[8].X);
			Assert::AreEqual(27.0f, Instance[9].X);
			Assert::AreEqual(0.0f, Instance[10].X);

			// insert in between length and capacity
			Instance.Insert(13, 5448);
			Assert::AreEqual(static_cast<Elysium::Core::size>(13), Instance.GetLength());
			Assert::AreEqual(static_cast<Elysium::Core::size>(16), Instance.GetCapacity());
			Assert::AreEqual(3.0f, Instance[0].X);
			Assert::AreEqual(4.0f, Instance[1].X);
			Assert::AreEqual(5.0f, Instance[2].X);
			Assert::AreEqual(3.0f, Instance[3].X);
			Assert::AreEqual(33.0f, Instance[4].X);
			Assert::AreEqual(27.0f, Instance[5].X);
			Assert::AreEqual(27.0f, Instance[6].X);
			Assert::AreEqual(27.0f, Instance[7].X);
			Assert::AreEqual(27.0f, Instance[8].X);
			Assert::AreEqual(27.0f, Instance[9].X);
			Assert::AreEqual(0.0f, Instance[10].X);
			Assert::AreEqual(0.0f, Instance[11].X);
			Assert::AreEqual(0.0f, Instance[12].X);
			Assert::AreEqual(5448.0f, Instance[13].X);
			/*
			// insert behind capacity
			Instance.Insert(17, 5448);
			Assert::Fail();
			*/
		}
	private:
		void Iterations(Vector<Trivial>& Instance)
		{
			const Elysium::Core::size Length = Instance.GetLength();
			const Vector<Trivial>& ConstInstance = Instance;

			// iterate using index/operator
			for (Elysium::Core::size i = 0; i < Instance.GetLength(); i++)
			{
				const Trivial& Element = Instance[i];
				Assert::AreEqual(static_cast<float>(i), Element.X);
			}

			// iterate using index/method
			for (Elysium::Core::size i = 0; i < Instance.GetLength(); i++)
			{
				Trivial& Element = Instance.GetAt(i);
				Assert::AreEqual(static_cast<float>(i), Element.X);
			}

			// iterate using ForwardIterator-class
			uint32_t i = 0;
			for (Vector<Trivial>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				Trivial& Element = *Iterator;
				Assert::AreEqual(static_cast<float>(i++), Element.X);
			}
			Assert::AreEqual(static_cast<uint32_t>(Length), i);

			// iterate using ConstForwardIterator-class
			i = 0;
			for (Vector<Trivial>::ConstIterator Iterator = ConstInstance.GetBegin(); Iterator != ConstInstance.GetEnd(); ++Iterator)
			{
				const Trivial& Element = *Iterator;
				Assert::AreEqual(static_cast<float>(i++), Element.X);
			}
			Assert::AreEqual(static_cast<uint32_t>(Length), i);

			// iterate using BackwardIterator-class
			for (Vector<Trivial>::ReverseIterator Iterator = Instance.GetReverseBegin(); Iterator != Instance.GetReverseEnd(); --Iterator)
			{
				Trivial& Element = *Iterator;
				Assert::AreEqual(static_cast<float>(--i), Element.X);
			}
			Assert::AreEqual(0_ui32, i);

			// iterate using ConstBackwardIterator-class
			i = static_cast<uint32_t>(Length);
			for (Vector<Trivial>::ConstReverseIterator Iterator = ConstInstance.GetReverseBegin(); Iterator != ConstInstance.GetReverseEnd(); --Iterator)
			{
				const Trivial& Element = *Iterator;
				Assert::AreEqual(static_cast<float>(--i), Element.X);
			}
			Assert::AreEqual(0_ui32, i);
		}
	};
}
