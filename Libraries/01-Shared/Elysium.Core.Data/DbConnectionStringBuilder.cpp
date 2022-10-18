#include "DbConnectionStringBuilder.hpp"

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
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
	Text::Utf8StringBuilder ConnectionStringBuilder = Text::Utf8StringBuilder();
	for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = _KeyValueMap.GetBegin(); Iterator != _KeyValueMap.GetEnd(); ++Iterator)
	{
		Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String> Item = (*Iterator)->GetItem();
		const Elysium::Core::Utf8String& Key = Item.GetKey();
		const Elysium::Core::Utf8String& Value = Item.GetValue();

		if (!Elysium::Core::Utf8String::IsEmpty(Key) && !Elysium::Core::Utf8String::IsEmpty(Value))
		{
			ConnectionStringBuilder.Append(&Key[0]);
			ConnectionStringBuilder.Append(u8"=");
			ConnectionStringBuilder.Append(&Value[0]);
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
