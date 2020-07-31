#include "ASCIIEncoding.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _MINWINDEF_
#include <minwindef.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif

#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif

Elysium::Core::Text::ASCIIEncoding::ASCIIEncoding()
	: Elysium::Core::Text::Encoding(20127)
{ }
Elysium::Core::Text::ASCIIEncoding::~ASCIIEncoding()
{ }

const bool Elysium::Core::Text::ASCIIEncoding::GetIsSingleByte() const
{
	return true;
}

const Elysium::Core::String Elysium::Core::Text::ASCIIEncoding::GetEncodingName() const
{
	return Elysium::Core::String(u"US-ASCII");
}

Elysium::Core::Collections::Template::List<byte> Elysium::Core::Text::ASCIIEncoding::GetBytes(const char16_t Input) const
{
	Elysium::Core::Collections::Template::List<byte> Result = Elysium::Core::Collections::Template::List<byte>(1);
	Elysium::Core::int32_t IntegerRepresentation = Input;
	Result[0] = IntegerRepresentation < 0x80 ? (byte)IntegerRepresentation : 0x3F;

	return Result;
}
Elysium::Core::Collections::Template::List<byte> Elysium::Core::Text::ASCIIEncoding::GetBytes(const String & Input, const size_t CharIndex, const size_t CharCount) const
{
	Elysium::Core::Collections::Template::List<byte> Result = Elysium::Core::Collections::Template::List<byte>(CharCount);

	Elysium::Core::int32_t IntegerRepresentation;
	for (size_t i = 0; i < CharCount; ++i)
	{
		IntegerRepresentation = Input[i];
		Result[i] = IntegerRepresentation < 0x80 ? (byte)IntegerRepresentation : 0x3F;
	}
	
	return Result;
}

Elysium::Core::String Elysium::Core::Text::ASCIIEncoding::GetString(const byte * Bytes, const size_t ByteCount) const
{
	String Result = String(ByteCount);
	for (size_t i = 0; i < ByteCount; ++i)
	{
		Result[i] = static_cast<char16_t>(Bytes[i]);
	}

	return Result;
}
