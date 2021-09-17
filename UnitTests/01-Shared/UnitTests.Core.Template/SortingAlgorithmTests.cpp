#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Algorithms.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Tuple.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template;
using namespace Elysium::Core::Template::Algorithms::Sorting;
using namespace Elysium::Core::Template::Collections;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <algorithm>

namespace UnitTests::Core::Template
{
	template<template <class, class> class T, class T1, class T2>
	struct Tuple2Item1Greater
	{
		bool operator()(const T<T1, T2>& Value1, const T<T1, T2>& Value2) const
		{
			return Value1.GetItem1() > Value2.GetItem1();
		}
	};

	TEST_CLASS(SortingAlgorithmTests)
	{
	public:
		TEST_METHOD(BubbleSortBytes)
		{
			byte UnsortedData[3];

			// test function with signature "const T First, const size_t Count"
			std::memcpy(&UnsortedData[0], &_UnsortedData[0], 3);
			BubbleSort(&UnsortedData[0], 3);

			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[2]);
			
			// test function with signature "const T First, const T Last"
			std::memcpy(&UnsortedData[0], &_UnsortedData[0], 3);
			BubbleSort(&UnsortedData[0], &UnsortedData[2]);

			Assert::AreEqual(static_cast<byte>(1), UnsortedData[0]);
			Assert::AreEqual(static_cast<byte>(2), UnsortedData[1]);
			Assert::AreEqual(static_cast<byte>(3), UnsortedData[2]);
		}

		TEST_METHOD(BubbleSortTuple)
		{
			Tuple<int, int> UnsortedData[3] =
			{
				Tuple<int, int>(3, 3),
				Tuple<int, int>(21, 2),
				Tuple<int, int>(-5, 1)
			};

			Tuple2Item1Greater<Tuple, int, int> Comparer = Tuple2Item1Greater<Tuple, int, int>();
			BubbleSort(&UnsortedData[0], 3, Comparer);

			Assert::AreEqual(-5, UnsortedData[0].GetItem1());
			Assert::AreEqual(3, UnsortedData[1].GetItem1());
			Assert::AreEqual(21, UnsortedData[2].GetItem1());
		}
	private:
		byte _UnsortedData[3] = { 3, 1, 2 };
	};
}
