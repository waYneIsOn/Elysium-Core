#include "SqlNativeSequentialStream.hpp"

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::SqlNativeSequentialStream()
{
	AddRef();
}
Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::~SqlNativeSequentialStream()
{
}

int Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::Seek(unsigned long Position)
{
	_CurrentPosition = Position;

	return true;
}
int Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::Clear()
{
	_Buffer.clear();
	_CurrentPosition = 0;

	return true;
}
int Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::CompareData(void * Buffer)
{
	return memcmp(Buffer, &_Buffer[0], _Buffer.size()) == 0;
}
size_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::Length()
{
	return _Buffer.size();
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::operator void* const()
{
	return &_Buffer[0];
}

STDMETHODIMP_(unsigned long __stdcall) Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::AddRef(void)
{
	return ++_ReferenceCounter;
}
STDMETHODIMP_(unsigned long __stdcall) Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::Release(void)
{
	if (--_ReferenceCounter)
	{
		return _ReferenceCounter;
	}

	//delete this;
	return 0;
}
STDMETHODIMP_(HRESULT __stdcall) Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::QueryInterface(REFIID Guid, LPVOID * Object)
{
	*Object = nullptr;

	if (Guid == IID_IUnknown || Guid == IID_ISequentialStream)
	{
		*Object = this;
	}

	if (*Object)
	{
		((IUnknown*)*Object)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

STDMETHODIMP_(HRESULT __stdcall) Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::Read(void * Buffer, unsigned long Count, unsigned long * BytesRead)
{
	if (BytesRead)
	{
		*BytesRead = 0;
	}
	if (!Buffer)
	{
		return STG_E_INVALIDPOINTER;
	}
	if (Count == 0)
	{
		return S_OK;
	}

	size_t AvailableBytes = _Buffer.size() - _CurrentPosition;
	if (AvailableBytes == 0)
	{
		return S_FALSE;
	}

	size_t BytesToRead = Count > AvailableBytes ? AvailableBytes : Count;
	//memcpy_s(Buffer, sizeof(Buffer), (void*)((BYTE*)&_Buffer[0] + _CurrentPosition), BytesToRead);
	memcpy(Buffer, &_Buffer[_CurrentPosition], Count);
	_CurrentPosition += BytesToRead;

	if (BytesRead)
	{
		*BytesRead = (unsigned long)BytesToRead;
	}

	if (Count != BytesToRead)
	{
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeSequentialStream::Write(const void * Buffer, unsigned long Count, unsigned long * BytesWritten)
{
	if (!Buffer)
	{
		return STG_E_INVALIDPOINTER;
	}
	if (BytesWritten)
	{
		*BytesWritten = 0;
	}
	if (Count == 0)
	{
		return S_OK;
	}

	_Buffer.resize(_Buffer.size() + Count);

	// Need to append to the end of the stream.
	//_Buffer = CoTaskMemRealloc(_Buffer, _Buffer.size());
	//memcpy_s((void*)((BYTE*)&_Buffer[0] + _CurrentPosition), sizeof((void*)((BYTE*)Buffer + _CurrentPosition)), Buffer, Count);
	// _CurrentPosition += Count;  

	memcpy(&_Buffer[_CurrentPosition], Buffer, Count);
	_CurrentPosition += Count;

	if (BytesWritten)
	{
		*BytesWritten = Count;
	}
	return S_OK;
}
