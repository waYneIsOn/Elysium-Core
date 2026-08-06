/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_LEMPELZIV_LZ77UTILITY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_LEMPELZIV_LZ77UTILITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_PAIR
#include "../../../../Container/Pair.hpp"
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

namespace Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv
{
	template <class T = Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size MaxWindow = 32768, Elysium::Core::Template::System::uint8_t MinMatch = 3, 
		Elysium::Core::Template::System::size MaxMatch = 258>
	class LZ77Utility
	{
	public:
		using SymbolType = Elysium::Core::Template::Functional::RemoveConstVolatileType<T>;

		using TokenType = Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv::LZ77Token<SymbolType>;
	public:
		constexpr LZ77Utility() = default;

		constexpr LZ77Utility(const LZ77Utility& Source) = delete;

		constexpr LZ77Utility(LZ77Utility&& Right) noexcept = delete;

		constexpr ~LZ77Utility() = default;
	public:
		constexpr LZ77Utility& operator=(const LZ77Utility& Source) = delete;

		constexpr LZ77Utility& operator=(LZ77Utility&& Right) noexcept = delete;
	public:
		inline Elysium::Core::Template::Container::Vector<TokenType> Encode(const SymbolType* Data, const Elysium::Core::Template::System::size Length)
		{
			Elysium::Core::Template::Container::Vector<TokenType> Result;

			TokenType CurrentToken{};
			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				const Elysium::Core::Template::Container::Pair<Elysium::Core::Template::System::size, Elysium::Core::Template::System::size> Match = FindMatch(Data, Length, i);
				const Elysium::Core::Template::System::size MatchLength = Match.GetFirst();
				const Elysium::Core::Template::System::size MatchDistance = Match.GetSecond();

				if (MatchLength >= MinMatch)
				{
					assert(MatchDistance > 0);
					assert(MatchDistance <= _SlidingWindow.GetLength());
					assert(MatchLength <= MaxMatch);
				}

				if (MatchLength >= MinMatch)
				{
					CurrentToken._Length = MatchLength;
					CurrentToken._Distance = MatchDistance;
					Result.PushBack(CurrentToken);

					_SlidingWindow.CopyFromHistory(MatchDistance, MatchLength);

					i += MatchLength - 1;
				}
				else
				{
					CurrentToken._Literal = Data[i];
					Result.PushBack(CurrentToken);

					_SlidingWindow.PushBack(CurrentToken._Literal);
				}
			}

			return Result;
		}
		/*
		inline void Decode(const Elysium::Core::Template::Container::Vector<TokenType>& Tokens)
		{

		}
		*/
	private:
		inline const Elysium::Core::Template::Container::Pair<Elysium::Core::Template::System::size, Elysium::Core::Template::System::size> FindMatch(const T* Data, 
			const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Position)
		{
			const Elysium::Core::Template::System::size WindowLength = _SlidingWindow.GetLength();

			Elysium::Core::Template::System::size BestLength = 0;
			Elysium::Core::Template::System::size BestDistance = 0;

			for (Elysium::Core::Template::System::size i = 0; i < WindowLength; ++i)
			{
				Elysium::Core::Template::System::size Count = 0;
				while (Count < MaxMatch && Position + Count < Length)
				{
					const Elysium::Core::Template::System::size SourceOffset = i + Count;

					SymbolType Source;
					if (SourceOffset < WindowLength)
					{
						Source = _SlidingWindow[SourceOffset];
					}
					else
					{
						Source = Data[Position + Count - (WindowLength - i)];
					}

					if (Source != Data[Position + Count])
					{
						break;
					}

					++Count;
				}
				
				if (Count > BestLength || (Count == BestLength && Count >= MinMatch && (BestDistance == 0 || WindowLength - i < BestDistance)))
				{
					BestLength = Count;
					BestDistance = WindowLength - i;
				}
			}

			return { BestLength, BestDistance };
		}
		/*
		inline void PushBackMatch(const Elysium::Core::Template::System::size Distance, const Elysium::Core::Template::System::size Length)
		{
			assert(Distance > 0);
			assert(Distance <= _SlidingWindow.GetLength());

			const Elysium::Core::Template::System::size SlidingWindowCapacity = _SlidingWindow.GetCapacity();

			Elysium::Core::Template::System::size SourceIndex;
			if constexpr (_SlidingWindow.CanUseFastModulo)
			{
				SourceIndex = (_SlidingWindow.GetTail() - Distance) & (SlidingWindowCapacity - 1);
			}
			else
			{
				SourceIndex = (_SlidingWindow.GetTail() - Distance) % SlidingWindowCapacity;
			}

			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				const SymbolType Symbol = _SlidingWindow[SourceIndex];

				_SlidingWindow.PushBack(Symbol);

				SourceIndex = (++SourceIndex) & (SlidingWindowCapacity - 1);
			}
		}
		*/
	public:
		Elysium::Core::Template::Container::SlidingWindow<SymbolType> _SlidingWindow{};
	};
}
#endif
