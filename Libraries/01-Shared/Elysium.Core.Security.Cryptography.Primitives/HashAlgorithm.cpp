#include "HashAlgorithm.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::HashAlgorithm::~HashAlgorithm()
{ }

const Elysium::Core::size Elysium::Core::Security::Cryptography::HashAlgorithm::GetHashSize() const
{
	return _HashValue.GetLength();
}
const bool Elysium::Core::Security::Cryptography::HashAlgorithm::GetCanReuseTransform() const
{
	return false;
}

Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Security::Cryptography::HashAlgorithm::ComputeHash(Elysium::Core::IO::Stream & InputStream)
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Buffer = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(4096);
	Elysium::Core::size BytesRead = 0;
	do
	{
		BytesRead = InputStream.Read(&Buffer[0], 4096);
		if (BytesRead > 0)
		{
			HashCore(&Buffer[0], BytesRead);
		}
	} while (BytesRead > 0);

	_HashValue = HashFinal();
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Temporary = Elysium::Core::Template::Functional::Move(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(_HashValue));

	Initialize();

	return Temporary;
}
Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Security::Cryptography::HashAlgorithm::ComputeHash(Elysium::Core::byte* Buffer, const Elysium::Core::size Length)
{
	HashCore(&Buffer[0], Length);
	_HashValue = HashFinal();
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Temporary = Elysium::Core::Template::Functional::Move(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(_HashValue));

	Initialize();

	return Temporary;
}

Elysium::Core::Security::Cryptography::HashAlgorithm::HashAlgorithm(int32_t HashSizeValue)
	: _HashValue(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(HashSizeValue)), _State(0)
{ }
