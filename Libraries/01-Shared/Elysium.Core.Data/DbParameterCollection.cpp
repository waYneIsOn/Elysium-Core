#include "DbParameterCollection.hpp"

Elysium::Core::Data::Common::DbParameterCollection::DbParameterCollection()
	: Elysium::Core::Data::IDataParameterCollection(),
	_InternalVector(Elysium::Core::Template::Container::Vector<const IDataParameter*>())
{ }

Elysium::Core::Data::Common::DbParameterCollection::~DbParameterCollection()
{ }

Elysium::Core::Data::IDataParameter& Elysium::Core::Data::Common::DbParameterCollection::operator[](Elysium::Core::size Index) const
{
	return *(Elysium::Core::Data::IDataParameter*)_InternalVector.GetAt(Index);
}

const Elysium::Core::size Elysium::Core::Data::Common::DbParameterCollection::GetLength() const
{
	return _InternalVector.GetLength();
}

const bool Elysium::Core::Data::Common::DbParameterCollection::GetIsReadOnly() const
{
	return false;
}

void Elysium::Core::Data::Common::DbParameterCollection::Add(const IDataParameter & Item)
{
	_InternalVector.PushBack(&Item);
}

void Elysium::Core::Data::Common::DbParameterCollection::Clear()
{
	_InternalVector.Clear();
}

bool Elysium::Core::Data::Common::DbParameterCollection::Contains(const IDataParameter & Item) const
{
	return false;
}

const Elysium::Core::size Elysium::Core::Data::Common::DbParameterCollection::IndexOf(const IDataParameter & Item) const
{
	return 0;
}

void Elysium::Core::Data::Common::DbParameterCollection::Insert(const Elysium::Core::size Index, const IDataParameter& Item)
{
}

bool Elysium::Core::Data::Common::DbParameterCollection::Remove(const IDataParameter & Item)
{
	return false;
}

void Elysium::Core::Data::Common::DbParameterCollection::RemoveAt(const Elysium::Core::size Index)
{
}
