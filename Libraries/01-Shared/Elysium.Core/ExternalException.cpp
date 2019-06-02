#include "ExternalException.hpp"

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

Elysium::Core::Runtime::InteropServices::ExternalException::ExternalException()
	: Elysium::Core::Exception(L"ExternalException")
{
	SetHResult(E_FAIL);
}
Elysium::Core::Runtime::InteropServices::ExternalException::ExternalException(const const String & Message)
	: Elysium::Core::Exception(Message)
{
	SetHResult(E_FAIL);
}
Elysium::Core::Runtime::InteropServices::ExternalException::ExternalException(const const String & Message, const int ErrorCode)
	: Elysium::Core::Exception(Message)
{
	SetHResult(ErrorCode);
}
Elysium::Core::Runtime::InteropServices::ExternalException::~ExternalException()
{
	/*
	if (_ErrorMessage != nullptr)
	{
		delete[] _ErrorMessage;
	}
	*/
}

int Elysium::Core::Runtime::InteropServices::ExternalException::GetErrorCode()
{
	return _ErrorCode;
}
HRESULT Elysium::Core::Runtime::InteropServices::ExternalException::GetHResult()
{
	return _ErrorCode;
}
/*
const char * Elysium::Core::Runtime::InteropServices::ExternalException::what() const throw()
{
	/*
	size_t NumberOfCharsConverted = 0;
	const wchar_t* Source = _COMError.ErrorMessage();
	const size_t SourceLength = wcslen(Source) + 1; // +1 because of '\0'

	if (_ErrorMessage != nullptr)
	{
		delete[] _ErrorMessage;
	}
	_ErrorMessage = new char[SourceLength];

	wcstombs_s(&NumberOfCharsConverted, _ErrorMessage, SourceLength, Source, SourceLength);

	return _ErrorMessage;
	*/
	/*
	const wchar_t* Source = _COMError.ErrorMessage();
	IErrorInfo* ErrorInfo = _COMError.ErrorInfo();
	HRESULT HResult = _COMError.Error();
	*-/
	// ToDo: this will only return the first char and therefore won't display the whole message
	//return (char*)_COMError.ErrorMessage();

	return "Elysium::Core::Runtime::InteropServices::ExternalException::what() isn't implemented yet";
}
*/
void Elysium::Core::Runtime::InteropServices::ExternalException::SetHResult(HRESULT ErrorCode)
{
	_ErrorCode = ErrorCode;

	// use _com_error to read more information
	_com_error COMError = ErrorCode;
	//IErrorInfo* ErrorInfo = COMError.ErrorInfo();

	std::wstring SourceMessage = COMError.ErrorMessage();
	//SourceMessage.to

	/*
	const wchar_t* Source = COMError.ErrorMessage();
	size_t SourceSize = wcslen(Source) + 1;
	size_t ConvertedChars = 0;
	const size_t TargetSize = SourceSize * 2;
	char* Target;
	wcstombs_s(&ConvertedChars, Target, TargetSize, Source, SourceSize);
	*/
}
