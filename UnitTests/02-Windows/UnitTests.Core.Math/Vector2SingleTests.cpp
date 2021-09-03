#include "CppUnitTest.h"
#include "../../../Libraries/01-Shared/Elysium.Core.Math/Vector2Double.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Math/Vector2Single.hpp"

using namespace Elysium::Core::Math::Numerics;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest::Core::Math::Numerics
{
	TEST_CLASS(Vector2Tests)
	{
	public:
		TEST_METHOD(Size)
		{
			Assert::AreEqual(sizeof(float) * 2, sizeof(Vector2<float>));
			Assert::AreEqual(sizeof(double) * 2, sizeof(Vector2<double>));
		}
		/*
		TEST_METHOD(Vector2Single_Add)
		{
			// test 1
			Vector2<float> Result = Vector2<float>::One();

			Vector2<float>::Add(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 2.0f);

			// test 2
			Vector2<float> Vec1 = Vector2<float>::UnitX();
			Vector2<float> Vec2 = Vector2<float>::UnitY();

			Vector2<float>::Add(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 1.0f);
		}

		TEST_METHOD(Vector2Single_Barycentric)
		{
			Vector2<float> X = Vector2<float>(1.0f, 0.0f);

			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(7.3f, 3.5f);
			Vector2<float> Vec3 = Vector2<float>(3.5f, 94.1f);
			Vector2<float> Result;

			Vector2<float>::Barycentric(&Vec1, &Vec2, &Vec3, 15.3f, 1.9f, Result);
			Assert::AreEqual(Result.X, 50.300011f);
			Assert::AreEqual(Result.Y, -59.260010f);
		}

		TEST_METHOD(Vector2Single_CatmullRom)
		{
			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(7.3f, 3.5f);
			Vector2<float> Vec3 = Vector2<float>(3.5f, 94.1f);
			Vector2<float> Vec4 = Vector2<float>(8.2f, -2.6f);
			Vector2<float> Result;

			Vector2<float>::CatmullRom(&Vec1, &Vec2, &Vec3, &Vec4, 1.9f, Result);
			Assert::AreEqual(Result.X, 19.197800f);
			Assert::AreEqual(Result.Y, -209.503281f);
		}

		TEST_METHOD(Vector2Single_Clamp)
		{
			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Min = Vector2<float>(7.3f, 3.5f);
			Vector2<float> Max = Vector2<float>(3.5f, 94.1f);
			Vector2<float> Result;

			Vector2<float>::Clamp(&Vec1, &Min, &Max, Result);
			Assert::AreEqual(Result.X, 7.3f);
			Assert::AreEqual(Result.Y, 18.0f);
		}

		TEST_METHOD(Vector2Single_Distance)
		{
			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(7.3f, 3.5f);
			float Result = 13.37f;

			Vector2<float>::Distance(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 14.827677f);
		}

		TEST_METHOD(Vector2Single_DistanceSquared)
		{
			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(7.3f, 3.5f);
			float Result = 13.37f;

			Vector2<float>::DistanceSquared(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 219.860001f);
		}

		TEST_METHOD(Vector2Single_Hermite)
		{
			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Tangent1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(7.3f, 3.5f);
			Vector2<float> Tangent2 = Vector2<float>(4.2f, 18.0f);
			float Amount = 13.37f;
			Vector2<float> Result;

			Vector2<float>::Hermite(&Vec1, &Tangent1, &Vec2, &Tangent2, Amount, Result);
			Assert::AreEqual(Result.X, 4728.410156f);
			Assert::AreEqual(Result.Y, 138178.546875f);
		}

		TEST_METHOD(Vector2Single_Lerp)
		{
			Vector2<float> Vec1 = Vector2<float>(4.0f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(9.0f, 7.0f);
			float Amount = 0.5f;
			Vector2<float> Result;

			Vector2<float>::Lerp(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 6.5f);
			Assert::AreEqual(Result.Y, 12.5f);
		}

		TEST_METHOD(Vector2Single_Divide)
		{
			// test 1
			Vector2<float> Result = Vector2<float>(15.0f, 21.0f);

			Vector2<float>::Divide(&Result, 3.0f, Result);
			Assert::AreEqual(Result.X, 5.0f);
			Assert::AreEqual(Result.Y, 7.0f);

			// test 2
			Vector2<float> Vec1 = Vector2<float>(4.0f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(2.0f, 3.0f);

			Vector2<float>::Divide(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 6.0f);
		}

		TEST_METHOD(Vector2Single_Dot)
		{
			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(7.3f, 3.5f);
			float Result = 13.37f;

			Vector2<float>::Dot(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 93.660004f);
		}

		TEST_METHOD(Vector2Single_Max)
		{
			Vector2<float> Vec1 = Vector2<float>::UnitX();
			Vector2<float> Vec2 = Vector2<float>::UnitY();
			Vector2<float> Result;

			Vector2<float>::Max(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 1.0f);
		}

		TEST_METHOD(Vector2Single_Min)
		{
			Vector2<float> Vec1 = Vector2<float>::UnitX();
			Vector2<float> Vec2 = Vector2<float>::UnitY();
			Vector2<float> Result;

			Vector2<float>::Min(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
		}

		TEST_METHOD(Vector2Single_Multiply)
		{
			// test 1
			Vector2<float> Result = Vector2<float>(5.1f, 3.3f);

			Vector2<float>::Multiply(&Result, 2.7f, Result);
			Assert::AreEqual(Result.X, 13.77f);
			Assert::AreEqual(Result.Y, 8.91f);

			// test 2
			Vector2<float> Vec1 = Vector2<float>(4.2f, 18.0f);
			Vector2<float> Vec2 = Vector2<float>(7.3f, 3.5f);

			Vector2<float>::Multiply(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 30.66f);
			Assert::AreEqual(Result.Y, 63.0f);
		}

		TEST_METHOD(Vector2Single_Negate)
		{
			Vector2<float> Result = Vector2<float>(-137.0f, 5.0f);

			Vector2<float>::Negate(&Result, Result);
			Assert::AreEqual(Result.X, 137.0f);
			Assert::AreEqual(Result.Y, -5.0f);
		}

		TEST_METHOD(Vector2Single_Normalize)
		{
			Vector2<float> Result = Vector2<float>::UnitX();

			Result.Normalize();
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 0.0f);
		}

		TEST_METHOD(Vector2Single_Reflect)
		{
			Vector2<float> Vec1 = Vector2<float>(4.0f, 18.0f);
			Vector2<float> Normal = Vector2<float>(1.0f, 0.0f);
			Vector2<float> Result;

			Vector2<float>::Reflect(&Vec1, &Normal, Result);
			Assert::AreEqual(Result.X, -4.0f);
			Assert::AreEqual(Result.Y, 18.0f);
		}

		TEST_METHOD(Vector2Single_Smoothstep)
		{
			Vector2<float> Vec1 = Vector2<float>(2.0f, 3.0f);
			Vector2<float> Vec2 = Vector2<float>(7.0f, 3.0f);
			float Amount = 0.5f;
			Vector2<float> Result;

			Vector2<float>::SmoothStep(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 2.625f);
			Assert::AreEqual(Result.Y, 3.0f);
		}

		TEST_METHOD(Vector2Single_Subtract)
		{
			// test 1
			Vector2<float> Result = Vector2<float>::One();

			Vector2<float>::Subtract(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);

			// test 2
			Vector2<float> Vec1 = Vector2<float>(2.3f, 3.7f);
			Vector2<float> Vec2 = Vector2<float>::One();

			Vector2<float>::Subtract(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.3f);
			Assert::AreEqual(Result.Y, 2.7f);
		}
		*/
	};
}
