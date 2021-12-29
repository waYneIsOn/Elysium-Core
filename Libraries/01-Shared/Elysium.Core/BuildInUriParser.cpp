#include "BuildInUriParser.hpp"

Elysium::Core::BuildInUriParser::BuildInUriParser(Elysium::Core::Utf8String Scheme, int Port, UriSyntaxFlags RequiredComponents)
	: Elysium::Core::UriParser(Scheme, Port, RequiredComponents)
{ }

Elysium::Core::BuildInUriParser::~BuildInUriParser()
{ }
