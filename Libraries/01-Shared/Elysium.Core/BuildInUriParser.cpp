#include "BuildInUriParser.hpp"

Elysium::Core::BuildInUriParser::BuildInUriParser(std::string Scheme, int Port, UriSyntaxFlags RequiredComponents)
	: Elysium::Core::UriParser(Scheme, Port, RequiredComponents)
{
}
