#include "DictationGrammar.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#include "../Elysium.Core/COMException.hpp"
#endif
#endif

Elysium::Core::Speech::Recognition::DictationGrammar::DictationGrammar()
	: DictationGrammar(u8"uri=grammar:dictation rule=")
{ }

Elysium::Core::Speech::Recognition::DictationGrammar::DictationGrammar(const Utf8String& Topic)
	: Elysium::Core::Speech::Recognition::Grammar(),
	_Topic(Topic)
{ }

Elysium::Core::Speech::Recognition::DictationGrammar::~DictationGrammar()
{ }

void Elysium::Core::Speech::Recognition::DictationGrammar::SetDictationContext(const Utf8String& PrecedingText, const Utf8String& SubsequentText)
{
	throw 1;
}

#if defined ELYSIUM_CORE_OS_WINDOWS
void Elysium::Core::Speech::Recognition::DictationGrammar::Load()
{
	HRESULT Result = S_OK;
	/*
	// ToDo
	WORD LanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
	if (FAILED(Result = _NativeRecognitionGrammar->ResetGrammar(LanguageId)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
	*/
	// ToDo
	//Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = _WindowsEncoding.GetBytes(&_Topic[0], _Topic.GetLength(), sizeof(wchar_t));
	//if (FAILED(Result = _NativeRecognitionGrammar->LoadDictation((wchar_t*)&Bytes[0], SPLOADOPTIONS::SPLO_STATIC)))
	//if (FAILED(Result = _NativeRecognitionGrammar->LoadDictation(SPTOPIC_SPELLING, SPLOADOPTIONS::SPLO_STATIC)))
	if (FAILED(Result = _NativeRecognitionGrammar->LoadDictation(nullptr, SPLOADOPTIONS::SPLO_STATIC)))
	{
		// "0x8004503a - SPERR_NOT_FOUND - IDispatch error #20026" may occurre if ...
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	// activate
	if (FAILED(Result = _NativeRecognitionGrammar->SetDictationState(SPRS_ACTIVE)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
}

void Elysium::Core::Speech::Recognition::DictationGrammar::Unload()
{
	HRESULT Result = _NativeRecognitionGrammar->UnloadDictation();
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
}
#endif
