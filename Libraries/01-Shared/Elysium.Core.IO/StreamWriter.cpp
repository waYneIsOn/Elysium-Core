#include "StreamWriter.hpp"

Elysium::Core::IO::StreamWriter::StreamWriter(Stream & OutputStream)
	: Elysium::Core::IO::TextWriter(),
	_OutputStream(OutputStream)
{
}
Elysium::Core::IO::StreamWriter::~StreamWriter()
{
}

const Elysium::Core::Text::Encoding & Elysium::Core::IO::StreamWriter::GetEncoding()
{
	return Elysium::Core::Text::Encoding::Default();
}

void Elysium::Core::IO::StreamWriter::Close()
{
	_OutputStream.Close();
}
void Elysium::Core::IO::StreamWriter::Flush()
{
	_OutputStream.Flush();
}

void Elysium::Core::IO::StreamWriter::Write(const byte * Value, const size_t Length)
{
	_OutputStream.Write(&Value[0], Length);
}
