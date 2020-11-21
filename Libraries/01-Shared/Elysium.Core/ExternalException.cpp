#include "ExternalException.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Runtime::InteropServices::ExternalException::ExternalException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(0x80004005L)
{ }
Elysium::Core::Runtime::InteropServices::ExternalException::ExternalException(const Elysium::Core::int32_t ErrorCode)
	: Elysium::Core::Exception(std::move(GetErrorMessage(ErrorCode))), _ErrorCode(ErrorCode)
{ }
Elysium::Core::Runtime::InteropServices::ExternalException::~ExternalException()
{ }

const Elysium::Core::int32_t Elysium::Core::Runtime::InteropServices::ExternalException::GetErrorCode() const
{
	return _ErrorCode;
}

const HRESULT Elysium::Core::Runtime::InteropServices::ExternalException::GetHResult() const
{
	return static_cast<HRESULT>(_ErrorCode);
}

Elysium::Core::String Elysium::Core::Runtime::InteropServices::ExternalException::GetErrorMessage(const Elysium::Core::int32_t ErrorCode)
{
	_com_error COMError = _com_error(ErrorCode);
	const wchar_t* ErrorMessageW = COMError.ErrorMessage();

	const Elysium::Core::Text::Encoding& Utf16BeEncoding = Elysium::Core::Text::Encoding::UTF16BE();
	return Utf16BeEncoding.GetString((const byte*)&ErrorMessageW[0], std::char_traits<wchar_t>::length(ErrorMessageW));
}
