#include "OidCollection.hpp"

Elysium::Core::Security::Cryptography::OidCollection::OidCollection()
	: _Capacity(0), _Count(0), _Data(nullptr)
{ }
Elysium::Core::Security::Cryptography::OidCollection::~OidCollection()
{ 
	if (_Data != nullptr)
	{
		delete[] _Data;
		_Data = nullptr;
	}
}
