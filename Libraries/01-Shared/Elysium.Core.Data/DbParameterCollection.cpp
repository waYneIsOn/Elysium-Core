#include "DbParameterCollection.hpp"

const size_t Elysium::Core::Data::Common::DbParameterCollection::GetCount() const
{
	return _InternalVector.size();
}
const bool Elysium::Core::Data::Common::DbParameterCollection::GetIsReadOnly() const
{
	return false;
}

void Elysium::Core::Data::Common::DbParameterCollection::Add(const IDataParameter & Item)
{
	_InternalVector.push_back(&Item);
}
void Elysium::Core::Data::Common::DbParameterCollection::Add(const IDataParameter * Item)
{
	_InternalVector.push_back(Item);
}
void Elysium::Core::Data::Common::DbParameterCollection::Clear()
{
	_InternalVector.clear();
}
bool Elysium::Core::Data::Common::DbParameterCollection::Contains(const IDataParameter & Item) const
{
	return false;
}
const size_t Elysium::Core::Data::Common::DbParameterCollection::IndexOf(const IDataParameter & Item) const
{
	return 0;
}
void Elysium::Core::Data::Common::DbParameterCollection::Insert(size_t Index, const IDataParameter & Item)
{
}
bool Elysium::Core::Data::Common::DbParameterCollection::Remove(const IDataParameter & Item)
{
	return false;
}
void Elysium::Core::Data::Common::DbParameterCollection::RemoveAt(size_t Index)
{
}

Elysium::Core::Data::IDataParameter & Elysium::Core::Data::Common::DbParameterCollection::operator[](size_t Index) const
{
	return *(Elysium::Core::Data::IDataParameter*)_InternalVector.at(Index);
}

Elysium::Core::Data::Common::DbParameterCollection::DbParameterCollection()
	: Elysium::Core::Data::IDataParameterCollection(),
	_InternalVector(std::vector<const IDataParameter*>())
{
}
