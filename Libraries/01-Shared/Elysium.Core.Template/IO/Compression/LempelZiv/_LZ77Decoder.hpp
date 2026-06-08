/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77DECODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77DECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77TOKEN
#include "LZ77Token.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::LempelZiv
{
	template <class T>
	class LZ77Decoder
	{
	public:
		using Token = LZ77Token<T>;
	public:
		constexpr LZ77Decoder() = default;

		constexpr LZ77Decoder(const LZ77Decoder& Source) = delete;

		constexpr LZ77Decoder(LZ77Decoder&& Right) noexcept = delete;

		constexpr ~LZ77Decoder() = default;
	public:
		constexpr LZ77Decoder& operator=(const LZ77Decoder& Source) = delete;

		constexpr LZ77Decoder& operator=(LZ77Decoder&& Right) noexcept = delete;
	private:
		// @ToDo: make all these values flexible. deflate introduces "limits" that a generic lz77-implementation does not have
		// for instance CurrentToken._Length could be 1 or 2 (no compression obviously) in generic lz77, while deflate only allows greater or equal 3

		inline static constexpr const Elysium::Core::Template::System::size MaxWindow = 32768;
		inline static constexpr const Elysium::Core::Template::System::uint8_t MinLength = 3;
		inline static constexpr const Elysium::Core::Template::System::size MaxLength = 258;
	public:
		inline Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Read(const Elysium::Core::Template::Container::Vector<Token>& Tokens)
		{
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result;

			for (Elysium::Core::Template::System::size i = 0; i < Tokens.GetLength(); ++i)
			{
				const Token& CurrentToken = Tokens[i];
				if (0 == CurrentToken._Length)
				{
					Result.PushBack(CurrentToken._Literal);
					continue;
				}
				
				if (0 == CurrentToken._Distance || CurrentToken._Distance > Result.GetLength() || MaxWindow < CurrentToken._Distance)
				{	// @ToDo: throw specific exception (invalid distance)
					throw 1;
				}

				if (MinLength > CurrentToken._Length || MaxLength < CurrentToken._Length)
				{	// @ToDo: throw specific exception
					throw 1;
				}

				// this line is very important as &Result[StartIndex] after a re-allocation due to resizing the vector will obviously point to crap data
				Result.Reserve(Result.GetLength() + CurrentToken._Length);

				for (Elysium::Core::Template::System::size j = 0; j < CurrentToken._Length; ++j)
				{
					Elysium::Core::Template::System::size StartIndex = Result.GetLength() - CurrentToken._Distance;
					if (StartIndex > Result.GetLength())
					{	// @ToDo: throw specific exception (underflow)
						throw 1;
					}
					Result.PushBack(Result[StartIndex]);
				}
				/*
				// optimization (once vector is removed)
				if (CurrentToken._Distance > CurrentToken._Length) ELYSIUM_CORE_PATH_LIKELY
				{	// non-overlapping -> fast path
					//memcpy(out + pos, out + pos - CurrentToken._Distance, CurrentToken._Length);
				}
				else
				{	// overlapping -> slow path
					for (Elysium::Core::Template::System::size j = 0; j < CurrentToken._Length; ++j)
					{
						Elysium::Core::Template::System::size StartIndex = Result.GetLength() - CurrentToken._Distance;
						if (StartIndex > Result.GetLength())
						{	// @ToDo: throw specific exception (underflow)
							throw 1;
						}
						Result.PushBack(Result[StartIndex]);
					}
				}
				*/
			}

			return Result;
		}
	};
}
#endif
