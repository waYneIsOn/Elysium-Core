#include "CppUnitTest.h"

#include <format>

#include "../../../Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PlatformIndependentTest)
	{
	public:
		TEST_METHOD(TypeComparison)
		{
			Assert::AreEqual(sizeof(int), sizeof(long));
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), sizeof(char8_t));
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), sizeof(char16_t));
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), sizeof(char32_t));
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), sizeof(float));
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), sizeof(double));
			Assert::AreEqual(static_cast<Elysium::Core::size>(8), sizeof(long double));
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), sizeof(Elysium::Core::byte));
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), sizeof(Elysium::Core::sbyte));
		}
		/*
		TEST_METHOD(CauseStackOverflowThroughRecursion)
		{
			size Dummy = 0;
			EndlessRecursion(&Dummy);
		}
	private:
		void EndlessRecursion(size* Start)
		{
			size Dummy = 0;
			Logger::WriteMessage(&std::format("size {0}\r\n", Start - &Dummy)[0]);
			EndlessRecursion(Start);
		}
		*/
	};
}
