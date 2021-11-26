#include "ExternalException.hpp"

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

Elysium::Core::Runtime::InteropServices::ExternalException::ExternalException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(0x80004005L)
{ }

Elysium::Core::Runtime::InteropServices::ExternalException::ExternalException(const Elysium::Core::int32_t ErrorCode)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(GetErrorMessage(ErrorCode))), _ErrorCode(ErrorCode)
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

	const Elysium::Core::Text::Encoding& WindowsEncoding = Elysium::Core::Text::Encoding::UTF16LE();
	return WindowsEncoding.GetString((const byte*)&ErrorMessageW[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(ErrorMessageW));
}
#endif
