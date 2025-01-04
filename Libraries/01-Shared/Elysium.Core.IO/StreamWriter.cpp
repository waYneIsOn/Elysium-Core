#include "StreamWriter.hpp"

Elysium::Core::IO::StreamWriter::StreamWriter(Stream & OutputStream)
	: Elysium::Core::IO::StreamWriter::StreamWriter(OutputStream, Elysium::Core::Text::Encoding::UTF8())
{ }
Elysium::Core::IO::StreamWriter::StreamWriter(Stream & OutputStream, const Elysium::Core::Text::Encoding & Encoding)
	: Elysium::Core::IO::TextWriter(),
	_OutputStream(OutputStream), _Encoding(Encoding)
{ }
Elysium::Core::IO::StreamWriter::~StreamWriter()
{ }

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

void Elysium::Core::IO::StreamWriter::Write(const byte * Value, const Elysium::Core::size Length)
{
	if (_OutputStream.GetPosition() == 0)
	{
		const Elysium::Core::Container::VectorOfByte& BOM = _Encoding.GetPreamble();
		const Elysium::Core::size BOMLength = BOM.GetLength();
		if (BOMLength > 0)
		{
			_OutputStream.Write(&BOM[0], BOM.GetLength());
		}
	}

	_OutputStream.Write(&Value[0], Length);
}
