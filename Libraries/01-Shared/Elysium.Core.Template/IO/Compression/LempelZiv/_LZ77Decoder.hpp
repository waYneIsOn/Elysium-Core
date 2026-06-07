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
				}
				else
				{
					Elysium::Core::Template::System::size StartIndex = Result.GetLength() - CurrentToken._Distance;

					// this line is very important as &Result[StartIndex] after a re-allocation due to resizing the vector will obviously point to crap data
					Result.Reserve(Result.GetLength() + CurrentToken._Length);
					Result.PushBackRange(&Result[StartIndex], CurrentToken._Length);
				}
			}

			Result.PushBack(0x00);

			return Result;
		}
	};
}
#endif
