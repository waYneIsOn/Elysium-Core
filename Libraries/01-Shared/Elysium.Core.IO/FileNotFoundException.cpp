#include "FileNotFoundException.hpp"

Elysium::Core::IO::FileNotFoundException::FileNotFoundException()
	: Elysium::Core::IO::IOException(u"IOException")
{ }
Elysium::Core::IO::FileNotFoundException::FileNotFoundException(const char16_t * Message)
	: Elysium::Core::IO::IOException(Message)
{ }
Elysium::Core::IO::FileNotFoundException::FileNotFoundException(String && Message)
	: Elysium::Core::IO::IOException(std::move(Message))
{ }
Elysium::Core::IO::FileNotFoundException::~FileNotFoundException()
{ }
