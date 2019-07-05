#pragma once

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#define MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT
#include <CppUnitTestAssert.h>
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			// Some basic type templates are missing due from CppUnitTestAssert.h. See:
			// https://developercommunity.visualstudio.com/content/problem/338198/missing-tostring-template-specialization-for-basic.html
			// Once a fix is released, this declaration can be removed.
			template<>
			inline std::wstring ToString<int64_t>(const int64_t& t)
			{
				RETURN_WIDE_STRING(t);
			}
		}
	}
}
#endif

