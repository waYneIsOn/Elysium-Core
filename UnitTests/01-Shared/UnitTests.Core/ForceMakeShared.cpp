#include "CppUnitTest.h"

#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tricks
{
	// https://devblogs.microsoft.com/oldnewthing/20220721-00/?p=106879
    template<typename T>
    struct require_make_shared :
        public std::enable_shared_from_this<T>
    {
    protected:
        struct use_the_create_method 
        {
            explicit use_the_create_method() = default;
        };

        require_make_shared()
        { }
    public:
        template<typename...Args>
        static auto create(Args&&... args)
        {
            static_assert(std::is_convertible_v<T*, require_make_shared*>, "Must derive publicly from require_make_shared");
            return std::make_shared<T>(use_the_create_method{}, std::forward<Args>(args)...);
        }

        // Deny copy construction
        require_make_shared(require_make_shared const&) = delete;
    };

    class Widget : public require_make_shared<Widget>
    {
    public:
        static auto create()
        {
            return require_make_shared::create();
        } // assertion failure

        // public but unusable from outside the class
        Widget(use_the_create_method)
        { }
        Widget(use_the_create_method, int)
        { }
        Widget(use_the_create_method, int, int)
        { }
    };

	TEST_CLASS(ForceMakeShared)
	{
	public:
		TEST_METHOD(Example)
		{
            auto v1 = Widget::create(); // okay
            //auto v2 = std::make_shared<Widget>(); // nope
            //auto v3 = std::make_unique<Widget>(); // nope
            //Widget v4; // nope
		}
	};
}
