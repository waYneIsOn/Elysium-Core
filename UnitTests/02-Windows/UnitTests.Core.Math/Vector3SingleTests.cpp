#include "CppUnitTest.h"
#include "../../../Libraries/01-Shared/Elysium.Core.Math/Vector3Double.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Math/Vector3Single.hpp"

using namespace Elysium::Core::Math::Numerics;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest::Core::Math::Numerics
{
	TEST_CLASS(Vector3Tests)
	{
	public:
		TEST_METHOD(Size)
		{
			Assert::AreEqual(sizeof(float) * 3, sizeof(Vector3Single));
			Assert::AreEqual(sizeof(double) * 3, sizeof(Vector3Double));
		}

		TEST_METHOD(Vector3Single_Add)
		{
			Vector3Single Result = Vector3Single::One();

			Vector3Single::Add(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 2.0f);
			Assert::AreEqual(Result.Z, 2.0f);

			Vector3Single Vec1 = Vector3Single::UnitX();
			Vector3Single Vec2 = Vector3Single::UnitZ();

			Vector3Single::Add(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 1.0f);
		}

		TEST_METHOD(Vector3Single_Barycentric)
		{
			Vector3Single Vec1 = Vector3Single(4.2f, 18.0f, -590.234985f);
			Vector3Single Vec2 = Vector3Single(7.3f, 3.5f, 0.0f);
			Vector3Single Vec3 = Vector3Single(3.5f, 94.1f, 13.345f);
			Vector3Single Result;

			Vector3Single::Barycentric(&Vec1, &Vec2, &Vec3, 15.3f, 1.9f, Result);
			Assert::AreEqual(Result.X, 50.300011f);
			Assert::AreEqual(Result.Y, -59.260010f);
			Assert::AreEqual(Result.Z, 9587.162109f);
		}

		TEST_METHOD(Vector3Single_CatmullRom)
		{
			Vector3Single Vec1 = Vector3Single(4.2f, 0.0f, 18.0f);
			Vector3Single Vec2 = Vector3Single(7.3f, 0.0f, 3.5f);
			Vector3Single Vec3 = Vector3Single(3.5f, 0.0f, 94.1f);
			Vector3Single Vec4 = Vector3Single(8.2f, 0.0f, -2.6f);
			Vector3Single Result;

			Vector3Single::CatmullRom(&Vec1, &Vec2, &Vec3, &Vec4, 1.9f, Result);
			Assert::AreEqual(Result.X, 19.197800f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, -209.503281f);
		}

		TEST_METHOD(Vector3Single_Clamp)
		{
			Vector3Single Vec1 = Vector3Single(4.2f, 18.0f, 5448.f);
			Vector3Single Min = Vector3Single(7.3f, 3.5f, 7.0f);
			Vector3Single Max = Vector3Single(3.5f, 94.1f, 312.7f);
			Vector3Single Result;

			Vector3Single::Clamp(&Vec1, &Min, &Max, Result);
			Assert::AreEqual(Result.X, 7.3f);
			Assert::AreEqual(Result.Y, 18.0f);
			Assert::AreEqual(Result.Z, 312.7f);
		}

		TEST_METHOD(Vector3Single_Distance)
		{
			Vector3Single Vec1 = Vector3Single(4.2f, 18.0f, 0.0f);
			Vector3Single Vec2 = Vector3Single(7.3f, 3.5f, 0.0f);
			float Result = 13.37f;

			Vector3Single::Distance(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 14.827677f);
		}

		TEST_METHOD(Vector3Single_DistanceSquared)
		{
			Vector3Single Vec1 = Vector3Single(4.2f, 18.0f, 0.0f);
			Vector3Single Vec2 = Vector3Single(7.3f, 3.5f, 0.0f);
			float Result = 13.37f;

			Vector3Single::DistanceSquared(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 219.860001f);
		}

		TEST_METHOD(Vector3Single_Hermite)
		{
			Vector3Single Vec1 = Vector3Single(4.2f, 18.0f, -5.0f);
			Vector3Single Tangent1 = Vector3Single(4.2f, 18.0f, 1.93f);
			Vector3Single Vec2 = Vector3Single(7.3f, 3.5f, 46.89f);
			Vector3Single Tangent2 = Vector3Single(4.2f, 18.0f, -52.478f);
			float Amount = 13.37f;
			Vector3Single Result;

			Vector3Single::Hermite(&Vec1, &Tangent1, &Vec2, &Tangent2, Amount, Result);
			Assert::AreEqual(Result.X, 4728.410156f);
			Assert::AreEqual(Result.Y, 138178.546875f);
			Assert::AreEqual(Result.Z, -332302.125000f);
		}

		TEST_METHOD(Vector3Single_Lerp)
		{
			Vector3Single Vec1 = Vector3Single(4.0f, 18.0f, 25.0f);
			Vector3Single Vec2 = Vector3Single(9.0f, 7.0f, 175.0f);
			float Amount = 0.5f;
			Vector3Single Result;

			Vector3Single::Lerp(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 6.5f);
			Assert::AreEqual(Result.Y, 12.5f);
			Assert::AreEqual(Result.Z, 100.0f);
		}

		TEST_METHOD(Vector3Single_Divide)
		{
			// test 1
			Vector3Single Result = Vector3Single(15.0f, 21.0f, 18.0f);

			Vector3Single::Divide(&Result, 3.0f, Result);
			Assert::AreEqual(Result.X, 5.0f);
			Assert::AreEqual(Result.Y, 7.0f);
			Assert::AreEqual(Result.Z, 6.0f);

			// test 2
			Vector3Single Vec1 = Vector3Single(4.0f, 18.0f, 3.0f);
			Vector3Single Vec2 = Vector3Single(2.0f, 3.0f, 1.5f);

			Vector3Single::Divide(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 6.0f);
			Assert::AreEqual(Result.Z, 2.0f);
		}

		TEST_METHOD(Vector3Single_Dot)
		{
			Vector3Single Vec1 = Vector3Single(4.2f, 18.0f, 0.0f);
			Vector3Single Vec2 = Vector3Single(7.3f, 3.5f, 0.0f);
			float Result = 13.37f;

			Vector3Single::Dot(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 93.660004f);
		}

		TEST_METHOD(Vector3Single_Max)
		{
			Vector3Single Vec1 = Vector3Single::UnitX();
			Vector3Single Vec2 = Vector3Single::UnitY();
			Vector3Single Result;

			Vector3Single::Max(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 1.0f);
			Assert::AreEqual(Result.Z, 0.0f);
		}

		TEST_METHOD(Vector3Single_Min)
		{
			Vector3Single Vec1 = Vector3Single::UnitX();
			Vec1.Z = -3.0f;
			Vector3Single Vec2 = Vector3Single::UnitY();
			Vector3Single Result;

			Vector3Single::Min(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, -3.0f);
		}

		TEST_METHOD(Vector3Single_Multiply)
		{
			// test 1
			Vector3Single Result = Vector3Single(5.1f, 3.3f, 9.4f);

			Vector3Single::Multiply(&Result, 2.7f, Result);
			Assert::AreEqual(Result.X, 13.77f);
			Assert::AreEqual(Result.Y, 8.91f);
			Assert::AreEqual(Result.Z, 25.38f);

			// test 2
			Vector3Single Vec1 = Vector3Single(4.2f, 18.0f, 1.0f);
			Vector3Single Vec2 = Vector3Single(7.3f, 3.5f, 13.37f);

			Vector3Single::Multiply(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 30.66f);
			Assert::AreEqual(Result.Y, 63.0f);
			Assert::AreEqual(Result.Z, 13.37f);
		}

		TEST_METHOD(Vector3Single_Negate)
		{
			Vector3Single Result = Vector3Single(-137.0f, 5.0f, 23.854f);

			Vector3Single::Negate(&Result, Result);
			Assert::AreEqual(Result.X, 137.0f);
			Assert::AreEqual(Result.Y, -5.0f);
			Assert::AreEqual(Result.Z, -23.854f);
		}

		TEST_METHOD(Vector3Single_Normalize)
		{
			Vector3Single Result = Vector3Single::UnitZ();

			Result.Normalize();
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 1.0f);
		}

		TEST_METHOD(Vector3Single_Reflect)
		{
			Vector3Single Vec1 = Vector3Single(4.0f, 18.0f, -75.76f);
			Vector3Single Normal = Vector3Single(1.0f, 0.0f, 0.0f);
			Vector3Single Result;

			Vector3Single::Reflect(&Vec1, &Normal, Result);
			Assert::AreEqual(Result.X, -4.0f);
			Assert::AreEqual(Result.Y, 18.0f);
			Assert::AreEqual(Result.Z, -75.76f);
		}

		TEST_METHOD(Vector3Single_Smoothstep)
		{
			// test 2
			Vector3Single Vec1 = Vector3Single(2.0f, 3.0f, 25.3f);
			Vector3Single Vec2 = Vector3Single(7.0f, 3.0f, 728.298f);
			float Amount = 0.5f;
			Vector3Single Result;

			Vector3Single::SmoothStep(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 2.625f);
			Assert::AreEqual(Result.Y, 3.0f);
			Assert::AreEqual(Result.Z, 113.174744f);
		}

		TEST_METHOD(Vector3Single_Subtract)
		{
			// test 1
			Vector3Single Result = Vector3Single::One();

			Vector3Single::Subtract(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 0.0f);

			// test 2
			Vector3Single Vec1 = Vector3Single(2.3f, 3.7f, 9.91f);
			Vector3Single Vec2 = Vector3Single::One();

			Vector3Single::Subtract(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.3f);
			Assert::AreEqual(Result.Y, 2.7f);
			Assert::AreEqual(Result.Z, 8.91f);
		}
	private:
		// ...

		void LogXY()
		{
			Vector3Single Result = Vector3Single(20.0f, 25.0f, 0.0f);

			Logger::WriteMessage((char*)std::to_string(Result.X).c_str());
			Logger::WriteMessage((char*)std::to_string(Result.Y).c_str());
			Logger::WriteMessage((char*)std::to_string(Result.Z).c_str());
		}
	};
}