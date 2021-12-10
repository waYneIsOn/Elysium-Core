#include "VoiceInfo.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
Elysium::Core::Speech::Synthesis::VoiceInfo::VoiceInfo(ISpObjectToken* VoiceToken)
	: _VoiceToken(VoiceToken)
{ }
#endif

Elysium::Core::Speech::Synthesis::VoiceInfo::~VoiceInfo()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_VoiceToken != nullptr)
	{
		_VoiceToken->Release();
		_VoiceToken = nullptr;
	}
#endif
}

const Elysium::Core::Speech::Synthesis::VoiceAge Elysium::Core::Speech::Synthesis::VoiceInfo::GetAge() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpDataKey* AttributesKey;
	if (FAILED(Result = _VoiceToken->OpenKey(SPTOKENKEY_ATTRIBUTES, &AttributesKey)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	wchar_t* NativeValue;
	if (FAILED(Result = AttributesKey->GetStringValue(L"Age", &NativeValue)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	const Elysium::Core::size NativeValueLength = Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(NativeValue);
	VoiceAge Value = VoiceAge::NotSet;
	if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare(NativeValue, L"Child", NativeValueLength) == 0)
	{
		Value = VoiceAge::Child;
	}
	else if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare(NativeValue, L"Teen", NativeValueLength) == 0)
	{
		Value = VoiceAge::Teen;
	}
	else if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare(NativeValue, L"Adult", NativeValueLength) == 0)
	{
		Value = VoiceAge::Adult;
	}
	else if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare(NativeValue, L"Senior", NativeValueLength) == 0)
	{
		Value = VoiceAge::Senior;
	}

	CoTaskMemFree(NativeValue);
	AttributesKey->Release();

	return Value;
#else
	throw 1;
#endif
}

const Elysium::Core::Globalization::CultureInfo Elysium::Core::Speech::Synthesis::VoiceInfo::GetCulture() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpDataKey* AttributesKey;
	if (FAILED(Result = _VoiceToken->OpenKey(SPTOKENKEY_ATTRIBUTES, &AttributesKey)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	wchar_t* NativeValue;
	if (FAILED(Result = AttributesKey->GetStringValue(L"Language", &NativeValue)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	const Elysium::Core::int32_t LocaleId = Elysium::Core::Template::Text::Convert<wchar_t>::ToInt32(NativeValue,
		Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(NativeValue), 10);

	CoTaskMemFree(NativeValue);
	AttributesKey->Release();

	return Elysium::Core::Globalization::CultureInfo(LocaleId, false);
#else
	throw 1;
#endif
}

const Elysium::Core::Speech::Synthesis::VoiceGender Elysium::Core::Speech::Synthesis::VoiceInfo::GetGender() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpDataKey* AttributesKey;
	if (FAILED(Result = _VoiceToken->OpenKey(SPTOKENKEY_ATTRIBUTES, &AttributesKey)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	wchar_t* NativeValue;
	if (FAILED(Result = AttributesKey->GetStringValue(L"Gender", &NativeValue)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	const Elysium::Core::size NativeValueLength = Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(NativeValue);
	VoiceGender Value = VoiceGender::NotSet;
	if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare(NativeValue, L"Male", NativeValueLength) == 0)
	{
		Value = VoiceGender::Male;
	}
	else if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare(NativeValue, L"Female", NativeValueLength) == 0)
	{
		Value = VoiceGender::Female;
	}
	else if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare(NativeValue, L"Neutral", NativeValueLength) == 0)
	{
		Value = VoiceGender::Neutral;
	}

	CoTaskMemFree(NativeValue);
	AttributesKey->Release();

	return Value;
#else
	throw 1;
#endif
}

const Elysium::Core::String Elysium::Core::Speech::Synthesis::VoiceInfo::GetId() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	wchar_t* NativeValue;
	if (FAILED(Result = _VoiceToken->GetId(&NativeValue)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	const String Value = _WindowsEncoding.GetString((Elysium::Core::byte*)NativeValue,
		Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(NativeValue) + sizeof(wchar_t));

	CoTaskMemFree(NativeValue);

	return Value;
#else
	throw 1;
#endif
}

const Elysium::Core::String Elysium::Core::Speech::Synthesis::VoiceInfo::GetName() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpDataKey* AttributesKey;
	if (FAILED(Result = _VoiceToken->OpenKey(SPTOKENKEY_ATTRIBUTES, &AttributesKey)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	wchar_t* NativeValue;
	if (FAILED(Result = AttributesKey->GetStringValue(L"Name", &NativeValue)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	const String Value = _WindowsEncoding.GetString((Elysium::Core::byte*)NativeValue,
		Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(NativeValue) + sizeof(wchar_t));

	CoTaskMemFree(NativeValue);
	AttributesKey->Release();

	return Value;
#else
	throw 1;
#endif
}
