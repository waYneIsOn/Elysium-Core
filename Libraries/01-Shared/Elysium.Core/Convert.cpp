#include "Convert.hpp"

#ifndef _STRING_
#include <string>
#endif

Elysium::Core::Convert::~Convert()
{
}

int32_t Elysium::Core::Convert::ToInt32(ElysiumChar * Value, int32_t FromBase)
{
#if UNICODE
	//return wcstoul(Value, nullptr, FromBase);
	return wcstoul(Value, &Value, FromBase);
#else
	/*
	if (FromBase == 16)
	{
		if (*Value > 47 && *Value < 58)
		{
			return Input - 48;
		}
		else if (*Value > 64 && *Value < 71)
		{	// A-F
			return Input - 55;
		}
		else if (*Value > 96 && *Value < 103)
		{	// a-f
			return Input - 87;
		}
		else
		{
			return 0;
		}
	}
	*/
#endif
}
int32_t Elysium::Core::Convert::ToInt32(Elysium::Core::String & Value, int32_t FromBase)
{
#if UNICODE
	return wcstoul(&Value[0], nullptr, FromBase);
#else

#endif
}

Elysium::Core::Convert::Convert()
{
}
