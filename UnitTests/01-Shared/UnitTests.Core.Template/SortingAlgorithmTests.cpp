#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Algorithms.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Greater.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Less.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Tuple.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template;
using namespace Elysium::Core::Template::Algorithms::Sorting;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Algorithms
{
	template<template <class, class> class T, class T1, class T2>
	struct Tuple2Item1Greater
	{
		bool operator()(const T<T1, T2>& Value1, const T<T1, T2>& Value2) const
		{
			return Value1.GetItem1() > Value2.GetItem1();
		}
	};

	template<template <class, class> class T, class T1, class T2>
	struct Tuple2Item2Less
	{
		bool operator()(const T<T1, T2>& Value1, const T<T1, T2>& Value2) const
		{
			return Value1.GetItem2() < Value2.GetItem2();
		}
	};

	TEST_CLASS(SortingAlgorithmTests)
	{
	public:
		TEST_METHOD(BubbleSortBytes)
		{
			byte UnsortedData[4];

			// test function with signature "const T First, const Elysium::Core::size Count"
			std::memcpy(&UnsortedData[0], &_UnsortedBytes[0], 4);
			BubbleSort(&UnsortedData[0], 4);

			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(1), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[2]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[3]);
			
			// test function with signature "const T First, const T Last"
			std::memcpy(&UnsortedData[0], &_UnsortedBytes[0], 4);
			BubbleSort(&UnsortedData[0], &UnsortedData[3]);

			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(1), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[2]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[3]);
		}

		TEST_METHOD(BubbleSortTuple)
		{
			Tuple<int, int> UnsortedData[3] =
			{
				Tuple<int, int>(3, 5),
				Tuple<int, int>(21, 67),
				Tuple<int, int>(-5, 9)
			};

			// sorty by item1 ascending
			Tuple2Item1Greater<Tuple, int, int> Comparer1 = Tuple2Item1Greater<Tuple, int, int>();
			BubbleSort(&UnsortedData[0], 3, Comparer1);

			Assert::AreEqual(-5, UnsortedData[0].GetItem1());
			Assert::AreEqual(3, UnsortedData[1].GetItem1());
			Assert::AreEqual(21, UnsortedData[2].GetItem1());

			// sort by item2 descending
			Tuple2Item2Less<Tuple, int, int> Comparer2 = Tuple2Item2Less<Tuple, int, int>();
			BubbleSort(&UnsortedData[0], &UnsortedData[2], Comparer2);

			Assert::AreEqual(67, UnsortedData[0].GetItem2());
			Assert::AreEqual(9, UnsortedData[1].GetItem2());
			Assert::AreEqual(5, UnsortedData[2].GetItem2());
		}

		TEST_METHOD(QuickSortBytes)
		{
			byte UnsortedData[4];

			// test function with signature "const T First, const Elysium::Core::size Count"
			std::memcpy(&UnsortedData[0], &_UnsortedBytes[0], 4);
			QuickSort(&UnsortedData[0], 4);

			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(1), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[2]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[3]);

			// test function with signature "const T First, const T Last"
			std::memcpy(&UnsortedData[0], &_UnsortedBytes[0], 4);
			QuickSort(&UnsortedData[0], &UnsortedData[3]);

			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(1), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[2]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[3]);
		}
	private:
		byte _UnsortedBytes[4] = { 3, 1, 2, 1 };
	};
}
