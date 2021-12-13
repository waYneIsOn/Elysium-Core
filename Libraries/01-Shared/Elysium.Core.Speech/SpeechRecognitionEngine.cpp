#include "SpeechRecognitionEngine.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef SPHelper_h
#include <sphelper.h>
#endif
#endif

Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SpeechRecognitionEngine()
	: Elysium::Core::Speech::Recognition::SpeechRecognitionEngine(Elysium::Core::Globalization::CultureInfo())
{ }

Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SpeechRecognitionEngine(const Elysium::Core::Globalization::CultureInfo& Culture)
#if defined ELYSIUM_CORE_OS_WINDOWS
	: _NativeRecognizer(InitializeNativeRecognizer())
#endif
{ }

Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::~SpeechRecognitionEngine()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_NativeRecognizer != nullptr)
	{
		_NativeRecognizer->Release();
		_NativeRecognizer = nullptr;
	}

	CoUninitialize();
#endif
}

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::Test()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpObjectToken* DefaultAudioInputToken = nullptr;
	if (FAILED(Result = SpGetDefaultTokenFromCategoryId(SPCAT_AUDIOIN, &DefaultAudioInputToken)))
	{	// ToDo: throw specific exception
		throw 1;
	}

	if (FAILED(_NativeRecognizer->SetInput(DefaultAudioInputToken, TRUE)))
	{	// ToDo: throw specific exception
		throw 1;
	}

	SPRECOSTATE NativeState = SPRECOSTATE();
	if (FAILED(_NativeRecognizer->GetRecoState(&NativeState)))
	{	// ToDo: throw specific exception
		throw 1;
	}

	ISpObjectToken* NativeRecognitionProfile = nullptr;
	if (FAILED(_NativeRecognizer->GetRecoProfile(&NativeRecognitionProfile)))
	{	// ToDo: throw specific exception
		throw 1;
	}
	/*
	ISpRecoContext* NativeRecognizerContext = nullptr;
	if (FAILED(_NativeRecognizer->CreateRecoContext(&NativeRecognizerContext)))
	{	// ToDo: throw specific exception
		throw 1;
	}
	*/


	bool bla = false;
	/*
	ISpRecoResult* NativeRecognitionResult;
	NativeRecognitionResult->GetText()
	
	ISpPhrase* NativePhrase;
	_NativeRecognizer->EmulateRecognition(NativePhrase);
	NativePhrase->GetText()
	*/
#else
	throw 1;
#endif
}

#if defined ELYSIUM_CORE_OS_WINDOWS
ISpRecognizer* Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::InitializeNativeRecognizer()
{
	if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
	{
		return nullptr;
	}

	HRESULT Result = S_OK;

	ISpRecognizer* NativeRecognizer = nullptr;
	if (FAILED(Result = CoCreateInstance(CLSID_SpInprocRecognizer, nullptr, CLSCTX_ALL, IID_ISpRecognizer, (void**)&NativeRecognizer)))
	{
		return nullptr;
	}

	return NativeRecognizer;
}
#endif
