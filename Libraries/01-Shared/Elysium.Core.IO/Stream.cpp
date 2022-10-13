#include "Stream.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core/ArgumentNullException.hpp"
#endif

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

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "../Elysium.Core/AsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "IOException.hpp"
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
	Elysium::Core::Container::VectorOfByte Buffer = Elysium::Core::Container::VectorOfByte(BufferSize);
	while ((BytesRead = Read(&Buffer[0], BufferSize)) > 0)
	{
		Destination.Write(&Buffer[0], BytesRead);
	}
}

void Elysium::Core::IO::Stream::WriteByte(const Elysium::Core::byte Value)
{
	Write(&Value, 1);
}

const Elysium::Core::IAsyncResult* Elysium::Core::IO::Stream::BeginWrite(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State)
{
	if (Buffer == nullptr)
	{
		throw ArgumentNullException(u8"Buffer");
	}

	Elysium::Core::Threading::Tasks::Task* WriteTask = new Elysium::Core::Threading::Tasks::Task(
		Elysium::Core::Template::Container::Delegate<void>::Bind<[]() -> void
		{
			//_Stream.Write(Buffer, Size);
		}>()
	);
	WriteTask->Start();

	return WriteTask;
}

void Elysium::Core::IO::Stream::EndWrite(const Elysium::Core::IAsyncResult* AsyncResult)
{
	const Elysium::Core::Internal::AsyncResult* CastResult = (const Elysium::Core::Internal::AsyncResult*)AsyncResult;
	if (CastResult->GetErrorCode() != NO_ERROR)
	{
		throw IOException(CastResult->GetErrorCode());
	}
}

const Elysium::Core::IAsyncResult* Elysium::Core::IO::Stream::BeginRead(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State)
{
	throw 1;
}

const Elysium::Core::size Elysium::Core::IO::Stream::EndRead(const Elysium::Core::IAsyncResult* AsyncResult)
{
	throw 1;
}
