#include "DbConnectionStringBuilder.hpp"

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

void Elysium::Core::Data::Common::DbConnectionStringBuilder::SetConnectionString(const Elysium::Core::String & ConnectionString)
{
	/*
	Collections::Template::List<String> ConnectionStringParts = Collections::Template::List<String>();
	ConnectionString.Split(u8';', ConnectionStringParts);

	for (Elysium::Core::size i = 0; i < ConnectionStringParts.GetCount(); i++)
	{
		if (!String::IsNullOrEmtpy(ConnectionStringParts[i]))
		{
			Collections::Template::List<String> KeyValuePair = Collections::Template::List<String>();
			ConnectionStringParts[i].Split(u8'=', KeyValuePair);

			if (KeyValuePair.GetCount() != 2)
			{
				throw 1;
			}

			const String& Key = KeyValuePair[0];
			const String& Value = KeyValuePair[1];

			bool bla = false;
		}
	}
	*/
	Collections::Template::List<StringView> ConnectionStringParts = Collections::Template::List<StringView>();
	StringView ConnectionStringView = StringView(&ConnectionString[0]);
	ConnectionStringView.Split(u8';', ConnectionStringParts);

	const String Test = ConnectionStringView;

	for (Elysium::Core::size i = 0; i < ConnectionStringParts.GetCount(); i++)
	{
		const String Bla = ConnectionStringParts[i];
		bool blaaaa = false;
		/*
		if (!StringView::IsNullOrEmtpy(ConnectionStringParts[i]))
		{
			Collections::Template::List<StringView> KeyValuePair = Collections::Template::List<StringView>();
			ConnectionStringParts[i].Split(u8'=', KeyValuePair);

			if (KeyValuePair.GetCount() != 2)
			{
				throw 1;
			}

			const String& Key = KeyValuePair[0];
			const String& Value = KeyValuePair[1];

			bool bla = false;
		}
		*/
	}

	_KeyValueMap.Clear();
}
