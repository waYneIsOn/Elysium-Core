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
			Assert::AreEqual(sizeof(float) * 3, sizeof(Vector3<float>));
			Assert::AreEqual(sizeof(double) * 3, sizeof(Vector3<double>));
		}
		/*
		TEST_METHOD(Vector3Single_Add)
		{
			Vector3<float> Result = Vector3<float>::One();

			Vector3<float>::Add(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 2.0f);
			Assert::AreEqual(Result.Z, 2.0f);

			Vector3<float> Vec1 = Vector3<float>::UnitX();
			Vector3<float> Vec2 = Vector3<float>::UnitZ();

			Vector3<float>::Add(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 1.0f);
		}

		TEST_METHOD(Vector3Single_Barycentric)
		{
			Vector3<float> Vec1 = Vector3<float>(4.2f, 18.0f, -590.234985f);
			Vector3<float> Vec2 = Vector3<float>(7.3f, 3.5f, 0.0f);
			Vector3<float> Vec3 = Vector3<float>(3.5f, 94.1f, 13.345f);
			Vector3<float> Result;

			Vector3<float>::Barycentric(&Vec1, &Vec2, &Vec3, 15.3f, 1.9f, Result);
			Assert::AreEqual(Result.X, 50.300011f);
			Assert::AreEqual(Result.Y, -59.260010f);
			Assert::AreEqual(Result.Z, 9587.162109f);
		}

		TEST_METHOD(Vector3Single_CatmullRom)
		{
			Vector3<float> Vec1 = Vector3<float>(4.2f, 0.0f, 18.0f);
			Vector3<float> Vec2 = Vector3<float>(7.3f, 0.0f, 3.5f);
			Vector3<float> Vec3 = Vector3<float>(3.5f, 0.0f, 94.1f);
			Vector3<float> Vec4 = Vector3<float>(8.2f, 0.0f, -2.6f);
			Vector3<float> Result;

			Vector3<float>::CatmullRom(&Vec1, &Vec2, &Vec3, &Vec4, 1.9f, Result);
			Assert::AreEqual(Result.X, 19.197800f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, -209.503281f);
		}

		TEST_METHOD(Vector3Single_Clamp)
		{
			Vector3<float> Vec1 = Vector3<float>(4.2f, 18.0f, 5448.f);
			Vector3<float> Min = Vector3<float>(7.3f, 3.5f, 7.0f);
			Vector3<float> Max = Vector3<float>(3.5f, 94.1f, 312.7f);
			Vector3<float> Result;

			Vector3<float>::Clamp(&Vec1, &Min, &Max, Result);
			Assert::AreEqual(Result.X, 7.3f);
			Assert::AreEqual(Result.Y, 18.0f);
			Assert::AreEqual(Result.Z, 312.7f);
		}

		TEST_METHOD(Vector3Single_Distance)
		{
			Vector3<float> Vec1 = Vector3<float>(4.2f, 18.0f, 0.0f);
			Vector3<float> Vec2 = Vector3<float>(7.3f, 3.5f, 0.0f);
			float Result = 13.37f;

			Vector3<float>::Distance(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 14.827677f);
		}

		TEST_METHOD(Vector3Single_DistanceSquared)
		{
			Vector3<float> Vec1 = Vector3<float>(4.2f, 18.0f, 0.0f);
			Vector3<float> Vec2 = Vector3<float>(7.3f, 3.5f, 0.0f);
			float Result = 13.37f;

			Vector3<float>::DistanceSquared(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 219.860001f);
		}

		TEST_METHOD(Vector3Single_Hermite)
		{
			Vector3<float> Vec1 = Vector3<float>(4.2f, 18.0f, -5.0f);
			Vector3<float> Tangent1 = Vector3<float>(4.2f, 18.0f, 1.93f);
			Vector3<float> Vec2 = Vector3<float>(7.3f, 3.5f, 46.89f);
			Vector3<float> Tangent2 = Vector3<float>(4.2f, 18.0f, -52.478f);
			float Amount = 13.37f;
			Vector3<float> Result;

			Vector3<float>::Hermite(&Vec1, &Tangent1, &Vec2, &Tangent2, Amount, Result);
			Assert::AreEqual(Result.X, 4728.410156f);
			Assert::AreEqual(Result.Y, 138178.546875f);
			Assert::AreEqual(Result.Z, -332302.125000f);
		}

		TEST_METHOD(Vector3Single_Lerp)
		{
			Vector3<float> Vec1 = Vector3<float>(4.0f, 18.0f, 25.0f);
			Vector3<float> Vec2 = Vector3<float>(9.0f, 7.0f, 175.0f);
			float Amount = 0.5f;
			Vector3<float> Result;

			Vector3<float>::Lerp(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 6.5f);
			Assert::AreEqual(Result.Y, 12.5f);
			Assert::AreEqual(Result.Z, 100.0f);
		}

		TEST_METHOD(Vector3Single_Divide)
		{
			// test 1
			Vector3<float> Result = Vector3<float>(15.0f, 21.0f, 18.0f);

			Vector3<float>::Divide(&Result, 3.0f, Result);
			Assert::AreEqual(Result.X, 5.0f);
			Assert::AreEqual(Result.Y, 7.0f);
			Assert::AreEqual(Result.Z, 6.0f);

			// test 2
			Vector3<float> Vec1 = Vector3<float>(4.0f, 18.0f, 3.0f);
			Vector3<float> Vec2 = Vector3<float>(2.0f, 3.0f, 1.5f);

			Vector3<float>::Divide(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 6.0f);
			Assert::AreEqual(Result.Z, 2.0f);
		}

		TEST_METHOD(Vector3Single_Dot)
		{
			Vector3<float> Vec1 = Vector3<float>(4.2f, 18.0f, 0.0f);
			Vector3<float> Vec2 = Vector3<float>(7.3f, 3.5f, 0.0f);
			float Result = 13.37f;

			Vector3<float>::Dot(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 93.660004f);
		}

		TEST_METHOD(Vector3Single_Max)
		{
			Vector3<float> Vec1 = Vector3<float>::UnitX();
			Vector3<float> Vec2 = Vector3<float>::UnitY();
			Vector3<float> Result;

			Vector3<float>::Max(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 1.0f);
			Assert::AreEqual(Result.Z, 0.0f);
		}

		TEST_METHOD(Vector3Single_Min)
		{
			Vector3<float> Vec1 = Vector3<float>::UnitX();
			Vec1.Z = -3.0f;
			Vector3<float> Vec2 = Vector3<float>::UnitY();
			Vector3<float> Result;

			Vector3<float>::Min(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, -3.0f);
		}

		TEST_METHOD(Vector3Single_Multiply)
		{
			// test 1
			Vector3<float> Result = Vector3<float>(5.1f, 3.3f, 9.4f);

			Vector3<float>::Multiply(&Result, 2.7f, Result);
			Assert::AreEqual(Result.X, 13.77f);
			Assert::AreEqual(Result.Y, 8.91f);
			Assert::AreEqual(Result.Z, 25.38f);

			// test 2
			Vector3<float> Vec1 = Vector3<float>(4.2f, 18.0f, 1.0f);
			Vector3<float> Vec2 = Vector3<float>(7.3f, 3.5f, 13.37f);

			Vector3<float>::Multiply(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 30.66f);
			Assert::AreEqual(Result.Y, 63.0f);
			Assert::AreEqual(Result.Z, 13.37f);
		}

		TEST_METHOD(Vector3Single_Negate)
		{
			Vector3<float> Result = Vector3<float>(-137.0f, 5.0f, 23.854f);

			Vector3<float>::Negate(&Result, Result);
			Assert::AreEqual(Result.X, 137.0f);
			Assert::AreEqual(Result.Y, -5.0f);
			Assert::AreEqual(Result.Z, -23.854f);
		}

		TEST_METHOD(Vector3Single_Normalize)
		{
			Vector3<float> Result = Vector3<float>::UnitZ();

			Result.Normalize();
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 1.0f);
		}

		TEST_METHOD(Vector3Single_Reflect)
		{
			Vector3<float> Vec1 = Vector3<float>(4.0f, 18.0f, -75.76f);
			Vector3<float> Normal = Vector3<float>(1.0f, 0.0f, 0.0f);
			Vector3<float> Result;

			Vector3<float>::Reflect(&Vec1, &Normal, Result);
			Assert::AreEqual(Result.X, -4.0f);
			Assert::AreEqual(Result.Y, 18.0f);
			Assert::AreEqual(Result.Z, -75.76f);
		}

		TEST_METHOD(Vector3Single_Smoothstep)
		{
			Vector3<float> Vec1 = Vector3<float>(2.0f, 3.0f, 25.3f);
			Vector3<float> Vec2 = Vector3<float>(7.0f, 3.0f, 728.298f);
			float Amount = 0.5f;
			Vector3<float> Result;

			Vector3<float>::SmoothStep(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 2.625f);
			Assert::AreEqual(Result.Y, 3.0f);
			Assert::AreEqual(Result.Z, 113.174744f);
		}

		TEST_METHOD(Vector3Single_Subtract)
		{
			// test 1
			Vector3<float> Result = Vector3<float>::One();

			Vector3<float>::Subtract(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 0.0f);

			// test 2
			Vector3<float> Vec1 = Vector3<float>(2.3f, 3.7f, 9.91f);
			Vector3<float> Vec2 = Vector3<float>::One();

			Vector3<float>::Subtract(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.3f);
			Assert::AreEqual(Result.Y, 2.7f);
			Assert::AreEqual(Result.Z, 8.91f);
		}
	private:
		// ...

		void LogXY()
		{
			Vector3<float> Result = Vector3<float>(20.0f, 25.0f, 0.0f);

			Logger::WriteMessage((char*)std::to_string(Result.X).c_str());
			Logger::WriteMessage((char*)std::to_string(Result.Y).c_str());
			Logger::WriteMessage((char*)std::to_string(Result.Z).c_str());
		}
		*/
	};
}