#include "DbConnectionStringBuilder.hpp"

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

Elysium::Core::Data::Common::DbConnectionStringBuilder::DbConnectionStringBuilder()
	: _KeyValueMap()
{ }

Elysium::Core::Data::Common::DbConnectionStringBuilder::~DbConnectionStringBuilder()
{ }

Elysium::Core::Utf8String& Elysium::Core::Data::Common::DbConnectionStringBuilder::operator[](const Elysium::Core::Utf8String& Key)
{
	return _KeyValueMap[Key];
}

const Elysium::Core::Utf8String& Elysium::Core::Data::Common::DbConnectionStringBuilder::operator[](const Elysium::Core::Utf8String& Key) const
{
	return _KeyValueMap[Key];
}

Elysium::Core::Utf8String Elysium::Core::Data::Common::DbConnectionStringBuilder::GetConnectionString()
{
	Text::StringBuilder ConnectionStringBuilder = Text::StringBuilder();
	for (Elysium::Core::Template::Container::HashTable<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = _KeyValueMap.GetBegin(); Iterator != _KeyValueMap.GetEnd(); ++Iterator)
	{
		Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String> Item = (*Iterator)->GetItem();
		const Elysium::Core::Utf8String& Key = Item.GetKey();
		const Elysium::Core::Utf8String& Value = Item.GetValue();

		if (!Elysium::Core::Utf8String::IsNullOrEmtpy(Key) && !Elysium::Core::Utf8String::IsNullOrEmtpy(Value))
		{
			ConnectionStringBuilder.Append(Key);
			ConnectionStringBuilder.Append(u8"=");
			ConnectionStringBuilder.Append(Value);
			ConnectionStringBuilder.Append(u8";");
		}
	}

	return ConnectionStringBuilder.ToString();
}

void Elysium::Core::Data::Common::DbConnectionStringBuilder::SetConnectionString(const Elysium::Core::Utf8String & ConnectionString)
{
	_KeyValueMap.Clear();

	Utf8StringView ConnectionStringView = Utf8StringView(&ConnectionString[0]);
	Template::Container::Vector<Utf8StringView> ConnectionStringParts = ConnectionStringView.Split(u8';');

	for (Elysium::Core::size i = 0; i < ConnectionStringParts.GetLength(); i++)
	{
		if (!Utf8StringView::IsNullOrEmtpy(ConnectionStringParts[i]))
		{
			Template::Container::Vector<Utf8StringView> KeyValuePair = ConnectionStringParts[i].Split(u8'=');

			if (KeyValuePair.GetLength() != 2)
			{	// ToDo: how to handle this scenario? are there any "key, no value"-parts?
				throw 1;
			}

			_KeyValueMap.Set(&KeyValuePair[0][0], &KeyValuePair[1][0]);
		}
	}
}
