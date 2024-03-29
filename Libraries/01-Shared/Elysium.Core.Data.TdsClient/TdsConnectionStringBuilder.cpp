#include "TdsConnectionStringBuilder.hpp"

Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::TdsConnectionStringBuilder()
	: Elysium::Core::Data::Common::DbConnectionStringBuilder()
{
	SetServer(Elysium::Core::Utf8String());
	SetDatabase(Elysium::Core::Utf8String());
	SetIsTrustedConnection(false);
}

Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::~TdsConnectionStringBuilder()
{ }

const Elysium::Core::Utf8String& Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::GetServer() const
{
	return _KeyValueMap[u8"Server"];
}

const Elysium::Core::Utf8String& Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::GetDatabase() const
{
	return _KeyValueMap[u8"Database"];
}

const bool Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::GetIsTrustedConnection() const
{
	return _KeyValueMap[u8"Trusted_Connection"] == u8"Yes";
}

void Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::SetServer(const Elysium::Core::Utf8String& Value)
{
	_KeyValueMap.Set(u8"Server", Value);
}

void Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::SetDatabase(const Elysium::Core::Utf8String& Value)
{
	_KeyValueMap.Set(u8"Database", Value);
}

void Elysium::Core::Data::TdsClient::TdsConnectionStringBuilder::SetIsTrustedConnection(const bool Value)
{
	_KeyValueMap.Set(u8"Trusted_Connection", Value ? u8"Yes" : u8"No");
}
