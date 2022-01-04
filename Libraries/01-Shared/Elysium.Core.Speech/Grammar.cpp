#include "Grammar.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#include "../Elysium.Core/COMException.hpp"
#endif
#endif

Elysium::Core::Speech::Recognition::Grammar::Grammar()
	: Grammar(u8"", u8"")
{ }

Elysium::Core::Speech::Recognition::Grammar::Grammar(const Utf8String& Path, const Utf8String& RuleName)
	:  _Name(u8""),
#if defined ELYSIUM_CORE_OS_WINDOWS
	_NativeRecognitionGrammar(nullptr)
#endif
{ }

Elysium::Core::Speech::Recognition::Grammar::~Grammar()
{
	if (_NativeRecognitionGrammar != nullptr)
	{
		_NativeRecognitionGrammar->Release();
		_NativeRecognitionGrammar = nullptr;
	}
}

const bool Elysium::Core::Speech::Recognition::Grammar::GetIsLoaded() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_NativeRecognitionGrammar == nullptr)
	{
		return false;
	}

	SPGRAMMARSTATE State;
	HRESULT Result = _NativeRecognitionGrammar->GetGrammarState(&State);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	return State == SPGRAMMARSTATE::SPGS_ENABLED;
#else
#error "unsupported os"
#endif
}

const Elysium::Core::Utf8String& Elysium::Core::Speech::Recognition::Grammar::GetName() const
{
	return _Name;
}

void Elysium::Core::Speech::Recognition::Grammar::SetName(const Utf8String& Value)
{
	_Name = Value;
}

#if defined ELYSIUM_CORE_OS_WINDOWS
void Elysium::Core::Speech::Recognition::Grammar::Load()
{
	HRESULT Result = S_OK;

	const wchar_t* RuleName = L"SomeCustomRuleName";

	// ToDo
	WORD LanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
	if (FAILED(Result = _NativeRecognitionGrammar->ResetGrammar(LanguageId)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	// ToDo
	SPSTATEHANDLE State;
	if (FAILED(Result = _NativeRecognitionGrammar->GetRule(RuleName, 0, SPRAF_TopLevel | SPRAF_Active, true, &State)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	// ToDo
	const wchar_t* Command = L"computer";
	if (FAILED(Result = _NativeRecognitionGrammar->AddWordTransition(State, NULL, Command, L" ", SPWT_LEXICAL, 1, nullptr)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	//NativeRecognitionGrammar->LoadCmdFromFile(nullptr, SPLOADOPTIONS::SPLO_DYNAMIC);

	if (FAILED(Result = _NativeRecognitionGrammar->Commit(0)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	// activate
	if (FAILED(Result = _NativeRecognitionGrammar->SetRuleState(RuleName, 0, SPRS_ACTIVE)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
}

void Elysium::Core::Speech::Recognition::Grammar::Unload()
{
	throw 1;
}
#endif
