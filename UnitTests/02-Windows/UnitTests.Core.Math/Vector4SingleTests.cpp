#include "CppUnitTest.h"
#include "../../../Libraries/01-Shared/Elysium.Core.Math/Vector4Double.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Math/Vector4Single.hpp"

using namespace Elysium::Core::Math::Numerics;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest::Core::Math::Numerics
{
	TEST_CLASS(Vector4Tests)
	{
	public:
		TEST_METHOD(Size)
		{
			Assert::AreEqual(sizeof(float) * 4, sizeof(Vector4<float>));
			Assert::AreEqual(sizeof(double) * 4, sizeof(Vector4<double>));
		}
		/*
		TEST_METHOD(Vector4Single_Add)
		{
			// test 1
			Vector4<float> Result = Vector4<float>::One();

			Vector4<float>::Add(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 2.0f);
			Assert::AreEqual(Result.Z, 2.0f);
			Assert::AreEqual(Result.W, 2.0f);

			// test 2
			Vector4<float> Vec1 = Vector4<float>::UnitX();
			Vector4<float> Vec2 = Vector4<float>::UnitW();

			Vector4<float>::Add(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 0.0f);
			Assert::AreEqual(Result.W, 1.0f);
		}

		TEST_METHOD(Vector4Single_Barycentric)
		{
			Vector4<float> Vec1 = Vector4<float>(4.2f, 18.0f, -590.234985f, 0.0f);
			Vector4<float> Vec2 = Vector4<float>(7.3f, 3.5f, 0.0f, 163.712f);
			Vector4<float> Vec3 = Vector4<float>(3.5f, 94.1f, 13.345f, 234.913f);
			Vector4<float> Result;

			Vector4<float>::Barycentric(&Vec1, &Vec2, &Vec3, 15.3f, 1.9f, Result);
			Assert::AreEqual(Result.X, 50.300011f);
			Assert::AreEqual(Result.Y, -59.260010f);
			Assert::AreEqual(Result.Z, 9587.162109f);
			Assert::AreEqual(Result.W, 2951.128418f);
		}

		TEST_METHOD(Vector4Single_CatmullRom)
		{
			Vector4<float> Vec1 = Vector4<float>(4.2f, 0.0f, 0.0f, 18.0f);
			Vector4<float> Vec2 = Vector4<float>(7.3f, 0.0f, 0.0f, 3.5f);
			Vector4<float> Vec3 = Vector4<float>(3.5f, 0.0f, 0.0f, 94.1f);
			Vector4<float> Vec4 = Vector4<float>(8.2f, 0.0f, 0.0f, -2.6f);
			Vector4<float> Result;

			Vector4<float>::CatmullRom(&Vec1, &Vec2, &Vec3, &Vec4, 1.9f, Result);
			Assert::AreEqual(Result.X, 19.197800f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 0.0f);
			Assert::AreEqual(Result.W, -209.503281f);
		}

		TEST_METHOD(Vector4Single_Clamp)
		{
			Vector4<float> Vec1 = Vector4<float>(4.2f, 18.0f, 5448.f, 23435634.345f);
			Vector4<float> Min = Vector4<float>(7.3f, 3.5f, 7.0f, 345.3456f);
			Vector4<float> Max = Vector4<float>(3.5f, 94.1f, 312.7f, -28.0f);
			Vector4<float> Result;

			Vector4<float>::Clamp(&Vec1, &Min, &Max, Result);
			Assert::AreEqual(Result.X, 7.3f);
			Assert::AreEqual(Result.Y, 18.0f);
			Assert::AreEqual(Result.Z, 312.7f);
			Assert::AreEqual(Result.W, 345.3456f);
		}

		TEST_METHOD(Vector4Single_Distance)
		{
			Vector4<float> Vec1 = Vector4<float>(4.2f, 18.0f, 0.0f, 0.0f);
			Vector4<float> Vec2 = Vector4<float>(7.3f, 3.5f, 0.0f, 1.375f);
			float Result = 13.37f;

			Vector4<float>::Distance(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 14.891294f);
		}

		TEST_METHOD(Vector4Single_DistanceSquared)
		{
			Vector4<float> Vec1 = Vector4<float>(4.2f, 18.0f, 0.0f, 0.0f);
			Vector4<float> Vec2 = Vector4<float>(7.3f, 3.5f, 0.0f, -1.375f);
			float Result = 13.37f;

			Vector4<float>::DistanceSquared(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 221.750626f);
		}

		TEST_METHOD(Vector4Single_Hermite)
		{
			Vector4<float> Vec1 = Vector4<float>(4.2f, 18.0f, -5.0f, -345.34f);
			Vector4<float> Tangent1 = Vector4<float>(4.2f, 18.0f, 1.93f, 4.345f);
			Vector4<float> Vec2 = Vector4<float>(7.3f, 3.5f, 46.89f, 1908.02f);
			Vector4<float> Tangent2 = Vector4<float>(4.2f, 18.0f, -52.478f, 2.0f);
			float Amount = 13.37f;
			Vector4<float> Result;

			Vector4<float>::Hermite(&Vec1, &Tangent1, &Vec2, &Tangent2, Amount, Result);
			Assert::AreEqual(Result.X, 4728.410156f);
			Assert::AreEqual(Result.Y, 138178.546875f);
			Assert::AreEqual(Result.Z, -332302.125000f);
			Assert::AreEqual(Result.W, -9549593.000000f);
		}

		TEST_METHOD(Vector4Single_Lerp)
		{
			Vector4<float> Vec1 = Vector4<float>(4.0f, 18.0f, 25.0f, 0.0f);
			Vector4<float> Vec2 = Vector4<float>(9.0f, 7.0f, 175.0f, -23);
			float Amount = 0.5f;
			Vector4<float> Result;

			Vector4<float>::Lerp(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 6.5f);
			Assert::AreEqual(Result.Y, 12.5f);
			Assert::AreEqual(Result.Z, 100.0f);
			Assert::AreEqual(Result.W, -11.5f);
		}

		TEST_METHOD(Vector4Single_Divide)
		{
			// test 1
			Vector4<float> Result = Vector4<float>(15.0f, 21.0f, 18.0f, 7.2f);

			Vector4<float>::Divide(&Result, 3.0f, Result);
			Assert::AreEqual(Result.X, 5.0f);
			Assert::AreEqual(Result.Y, 7.0f);
			Assert::AreEqual(Result.Z, 6.0f);
			Assert::AreEqual(Result.W, 2.4f);

			// test 2
			Vector4<float> Vec1 = Vector4<float>(4.0f, 18.0f, 3.0f, 2.3f);
			Vector4<float> Vec2 = Vector4<float>(2.0f, 3.0f, 1.5f, 1.15f);

			Vector4<float>::Divide(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 2.0f);
			Assert::AreEqual(Result.Y, 6.0f);
			Assert::AreEqual(Result.Z, 2.0f);
			Assert::AreEqual(Result.W, 2.0f);
		}

		TEST_METHOD(Vector4Single_Dot)
		{
			Vector4<float> Vec1 = Vector4<float>(4.2f, 18.0f, 0.0f, 124.347895f);
			Vector4<float> Vec2 = Vector4<float>(7.3f, 3.5f, 0.0f, 0.0f);
			float Result = 13.37f;

			Vector4<float>::Dot(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result, 93.660004f);
		}

		TEST_METHOD(Vector4Single_Max)
		{
			Vector4<float> Vec1 = Vector4<float>::UnitX();
			Vector4<float> Vec2 = Vector4<float>::UnitW();
			Vector4<float> Result;

			Vector4<float>::Max(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 0.0f);
			Assert::AreEqual(Result.W, 1.0f);
		}

		TEST_METHOD(Vector4Single_Min)
		{
			Vector4<float> Vec1 = Vector4<float>::UnitX();
			Vec1.Z = -3.0f;
			Vector4<float> Vec2 = Vector4<float>::UnitW();
			Vector4<float> Result;

			Vector4<float>::Min(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, -3.0f);
			Assert::AreEqual(Result.W, 0.0f);
		}

		TEST_METHOD(Vector4Single_Multiply)
		{
			// test 1
			Vector4<float> Result = Vector4<float>(5.1f, 3.3f, 9.4f, 5.1f);

			Vector4<float>::Multiply(&Result, 2.7f, Result);
			Assert::AreEqual(Result.X, 13.77f);
			Assert::AreEqual(Result.Y, 8.91f);
			Assert::AreEqual(Result.Z, 25.38f);
			Assert::AreEqual(Result.W, 13.77f);

			// test 2
			Vector4<float> Vec1 = Vector4<float>(4.2f, 18.0f, 1.0f, 0.0f);
			Vector4<float> Vec2 = Vector4<float>(7.3f, 3.5f, 13.37f, 5.1f);

			Vector4<float>::Multiply(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 30.66f);
			Assert::AreEqual(Result.Y, 63.0f);
			Assert::AreEqual(Result.Z, 13.37f);
			Assert::AreEqual(Result.W, 0.0f);
		}

		TEST_METHOD(Vector4Single_Negate)
		{
			Vector4<float> Result = Vector4<float>(-137.0f, 5.0f, 23.854f, 20345.345f);

			Vector4<float>::Negate(&Result, Result);
			Assert::AreEqual(Result.X, 137.0f);
			Assert::AreEqual(Result.Y, -5.0f);
			Assert::AreEqual(Result.Z, -23.854f);
			Assert::AreEqual(Result.W, -20345.345703f);
		}

		TEST_METHOD(Vector4Single_Normalize)
		{
			Vector4<float> Result = Vector4<float>::UnitW();

			Result.Normalize();
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 0.0f);
			Assert::AreEqual(Result.W, 1.0f);
		}

		TEST_METHOD(Vector4Single_Reflect)
		{
			Vector4<float> Vec1 = Vector4<float>(4.0f, 18.0f, -75.76f, 0.0f);
			Vector4<float> Normal = Vector4<float>(1.0f, 0.0f, 0.0f, 965.9874f);
			Vector4<float> Result;

			Vector4<float>::Reflect(&Vec1, &Normal, Result);
			Assert::AreEqual(Result.X, -4.0f);
			Assert::AreEqual(Result.Y, 18.0f);
			Assert::AreEqual(Result.Z, -75.76f);
			Assert::AreEqual(Result.W, -7727.899414f);
		}

		TEST_METHOD(Vector4Single_Smoothstep)
		{
			Vector4<float> Vec1 = Vector4<float>(2.0f, 3.0f, 25.3f, 12.5612f);
			Vector4<float> Vec2 = Vector4<float>(7.0f, 3.0f, 728.298f, -234.034f);
			float Amount = 0.5f;
			Vector4<float> Result;

			Vector4<float>::SmoothStep(&Vec1, &Vec2, Amount, Result);
			Assert::AreEqual(Result.X, 2.625f);
			Assert::AreEqual(Result.Y, 3.0f);
			Assert::AreEqual(Result.Z, 113.174744f);
			Assert::AreEqual(Result.W, -18.263199f);
		}

		TEST_METHOD(Vector4Single_Subtract)
		{
			// test 1
			Vector4<float> Result = Vector4<float>::One();

			Vector4<float>::Subtract(&Result, &Result, Result);
			Assert::AreEqual(Result.X, 0.0f);
			Assert::AreEqual(Result.Y, 0.0f);
			Assert::AreEqual(Result.Z, 0.0f);
			Assert::AreEqual(Result.W, 0.0f);

			// test 2
			Vector4<float> Vec1 = Vector4<float>(2.3f, 3.7f, 9.91f, -27.3450f);
			Vector4<float> Vec2 = Vector4<float>::One();

			Vector4<float>::Subtract(&Vec1, &Vec2, Result);
			Assert::AreEqual(Result.X, 1.3f);
			Assert::AreEqual(Result.Y, 2.7f);
			Assert::AreEqual(Result.Z, 8.91f);
			Assert::AreEqual(Result.W, -28.344999f);
		}
		*/
	private:
		// ...

		void LogXY()
		{
			Vector4<float> Result = Vector4<float>(20.0f, 25.0f, 0.0f, 0.0f);

			Logger::WriteMessage((char*)std::to_string(Result.X).c_str());
			Logger::WriteMessage((char*)std::to_string(Result.Y).c_str());
			Logger::WriteMessage((char*)std::to_string(Result.Z).c_str());
			Logger::WriteMessage((char*)std::to_string(Result.W).c_str());
		}
	};
}