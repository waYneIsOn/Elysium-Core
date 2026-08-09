/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_LEMPELZIV_LZ77DECODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_LEMPELZIV_LZ77DECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIFOQUEUE
#include "../../../../Container/Adopter/FiFoQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW
#include "../../../../Container/SlidingWindow.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../../../../Functional/RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_LEMPELZIV_LZ77TOKEN
#include "LZ77Token.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CALLTRAITS
#include "../../../../TypeTraits/CallTraits.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv
{
	template <class T = Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size MaxWindow = 32768, Elysium::Core::Template::System::uint8_t MinMatch = 3, 
		Elysium::Core::Template::System::size MaxMatch = 258>
	class LZ77Decoder
	{
	public:
		using SymbolType = Elysium::Core::Template::Functional::RemoveConstVolatileType<T>;

		using TokenType = Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv::LZ77Token<SymbolType>;

		using ParameterTokenType = Elysium::Core::Template::TypeTraits::CallTraits<TokenType>::ParameterType;
	public:
		constexpr LZ77Decoder() = default;

		constexpr LZ77Decoder(const LZ77Decoder& Source) = delete;

		constexpr LZ77Decoder(LZ77Decoder&& Right) noexcept = delete;

		constexpr ~LZ77Decoder() = default;
	public:
		constexpr LZ77Decoder& operator=(const LZ77Decoder& Source) = delete;

		constexpr LZ77Decoder& operator=(LZ77Decoder&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const noexcept(noexcept(_Tokens.GetLength()))
		{
			return _Tokens.GetLength();
		}
	public:
		inline void Push(ParameterTokenType Token)
		{
			_Tokens.Push(Token);
		}
	public:
		inline Elysium::Core::Template::System::uint16_t PeekLength()
		{
			if (_Tokens.GetIsEmpty())
			{
				return 0;
			}

			typename Elysium::Core::Template::Container::FiFoQueue<TokenType>::Reference Token = _Tokens.GetFront();
			const Elysium::Core::Template::System::uint16_t Result = 0 < Token._Length ? Token._Length : 1;
			if (0 == Result)
			{	// @ToDo: this should never happen. if it does, something in the implementation is wrong!
				throw;
			}

			return Result;
		}

		inline Elysium::Core::Template::System::uint16_t Process()
		{
			typename Elysium::Core::Template::Container::FiFoQueue<TokenType>::Value Token = _Tokens.GetFront();
			_Tokens.Pop();

			if (0 < Token._Length)
			{
				_SlidingWindow.CopyFromHistory(Token._Distance, Token._Length);
			}
			else
			{
				_SlidingWindow.PushBack(Token._Literal);
			}

			return Token._Distance;
		}
	public:
		Elysium::Core::Template::Container::FiFoQueue<TokenType> _Tokens{};

		Elysium::Core::Template::Container::SlidingWindow<T> _SlidingWindow{};
	};
}
#endif
