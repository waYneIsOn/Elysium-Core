#include "BuildInUriParser.hpp"

Elysium::Core::BuildInUriParser::BuildInUriParser(String Scheme, int Port, UriSyntaxFlags RequiredComponents)
	: Elysium::Core::UriParser(Scheme, Port, RequiredComponents)
{
}
