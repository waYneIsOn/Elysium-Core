#include "CharEnumerator.hpp"

Elysium::Core::CharEnumerator::CharEnumerator(const String* IEnumerable)
	: _IEnumerable(IEnumerable), _Index(0)
{
}
Elysium::Core::CharEnumerator::~CharEnumerator()
{
}

bool Elysium::Core::CharEnumerator::MoveNext()
{
	return _Index++ < _IEnumerable->GetLength();
}
