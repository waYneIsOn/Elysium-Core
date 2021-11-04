#include "Stream.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "../Elysium.Core/ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "../Elysium.Core.Threading/Task.hpp"
#endif

Elysium::Core::IO::Stream::Stream()
{ }

Elysium::Core::IO::Stream::~Stream()
{ }
/*
Elysium::Core::IO::Stream& Elysium::Core::IO::Stream::operator<<(const Elysium::Core::byte Value)
{
	Write(&Value, sizeof(Elysium::Core::byte));
	return (*this);
}

Elysium::Core::IO::Stream& Elysium::Core::IO::Stream::operator<<(const Elysium::Core::uint32_t Value)
{
	Elysium::Core::byte* Bytes = (Elysium::Core::byte*)&Value;
	Write(Bytes, sizeof(Elysium::Core::uint32_t));
	return (*this);
}

Elysium::Core::IO::Stream& Elysium::Core::IO::Stream::operator>>(const Elysium::Core::uint32_t Value)
{
	throw NotImplementedException();

	return (*this);
}
*/
const bool Elysium::Core::IO::Stream::GetCanTimeout() const
{
	return false;
} 

const Elysium::Core::uint64_t Elysium::Core::IO::Stream::GetPosition() const
{
	if (!GetCanSeek())
	{
		throw NotSupportedException();
	}

	return 0;
}

const Elysium::Core::uint32_t Elysium::Core::IO::Stream::GetReadTimeout() const
{
	throw InvalidOperationException();
}

const Elysium::Core::uint32_t Elysium::Core::IO::Stream::GetWriteTimeout() const
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::SetReadTimeout(const Elysium::Core::uint32_t Value)
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::SetWriteTimeout(const Elysium::Core::uint32_t Value)
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::CopyTo(Stream & Destination)
{
	static const Elysium::Core::size BufferSize = 4096;
	CopyTo(Destination, BufferSize);
}

void Elysium::Core::IO::Stream::CopyTo(Stream & Destination, const Elysium::Core::size BufferSize)
{
	if (&Destination == this)
	{
		throw InvalidOperationException(u8"cannot copy from a stream to the same one");
	}

	Elysium::Core::size BytesRead = 0;
	Elysium::Core::Collections::Template::List<byte> Buffer = Elysium::Core::Collections::Template::List<byte>(BufferSize);
	while ((BytesRead = Read(&Buffer[0], BufferSize)) > 0)
	{
		Destination.Write(&Buffer[0], BytesRead);
	}
}

void Elysium::Core::IO::Stream::WriteByte(const Elysium::Core::byte Value)
{
	Write(&Value, 1);
}

const Elysium::Core::IAsyncResult* Elysium::Core::IO::Stream::BeginWrite(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State)
{
	throw 1;
	/*
	Elysium::Core::Threading::Tasks::Task WriteTask = Elysium::Core::Threading::Tasks::Task(
		Delegate<void>::Bind<[]() -> void
		{
			
		}>()
	);

	WriteTask.Start();
	WriteTask.Wait();

	return WriteTask;
	*/
}

void Elysium::Core::IO::Stream::EndWrite(const Elysium::Core::IAsyncResult* AsyncResult)
{
	throw 1;
}

const Elysium::Core::IAsyncResult* Elysium::Core::IO::Stream::BeginRead(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State)
{
	throw 1;
}

const Elysium::Core::size Elysium::Core::IO::Stream::EndRead(const Elysium::Core::IAsyncResult* AsyncResult)
{
	throw 1;
}
