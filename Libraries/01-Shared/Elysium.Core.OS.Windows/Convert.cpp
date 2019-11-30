#include "Convert.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

Elysium::Core::OS::Windows::Convert::~Convert()
{
}

std::wstring Elysium::Core::OS::Windows::Convert::ToWString(const String& Value)
{
	Elysium::Core::Collections::Generic::List<byte> Bytes = Elysium::Core::Text::Encoding::Default().GetBytes(Value, 0, Value.GetLength());

	// CP_ACP ?
	int Length = MultiByteToWideChar(CP_UTF8, 0, (char*)&Bytes[0], -1, NULL, 0);
	wchar_t* WideChars = new wchar_t[Length];
	MultiByteToWideChar(CP_UTF8, 0, (char*)&Bytes[0], -1, WideChars, Length);

	std::wstring WideString = std::wstring(WideChars);
	delete[] WideChars;

	return WideString;
}

Elysium::Core::OS::Windows::Convert::Convert()
{
}
