#include "Convert.hpp"

#ifndef _STRING_
#include <string>
#endif

Elysium::Core::Convert::~Convert()
{
}

int Elysium::Core::Convert::ToInt32(ElysiumChar * Value, int FromBase)
{
#if UNICODE
	return wcstoul(Value, nullptr, FromBase);
#else

#endif
}
int Elysium::Core::Convert::ToInt32(Elysium::Core::String & Value, int FromBase)
{
#if UNICODE
	return wcstoul(&Value[0], nullptr, FromBase);
#else

#endif
}

Elysium::Core::Convert::Convert()
{
}
