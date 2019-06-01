#include "Encoding.hpp"

Elysium::Core::Text::Encoding::~Encoding()
{
}

Elysium::Core::Text::Encoding::Encoding()
	: Elysium::Core::Text::Encoding(0)
{
}
Elysium::Core::Text::Encoding::Encoding(int CodePage)
	: _CodePage(CodePage)
{
}
