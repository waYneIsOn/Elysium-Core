#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Independent::LanguageFeatures
{
    TEST_CLASS(CatchAnythingThrown)
    {
    public:
        TEST_METHOD(Example)
        {
            try 
            {
                throw 1;
            }
            catch (...)
            { }
        }
    };
}
