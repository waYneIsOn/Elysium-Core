#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Independent::LanguageFeatures
{
    struct C
    {
        union
        {
            int a;
            const char* p;
        };

        int x;
    };

    TEST_CLASS(AggregateInitialization)
    {
    public:
        TEST_METHOD(Example)
        {
            C SomeInstance = { .a = 1, .x = 3 };
        }
    };
}
