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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Container/Vector.hpp"
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
	template <class T, Elysium::Core::Template::System::size MaxWindow = 32768, Elysium::Core::Template::System::uint8_t MinMatch = 3, Elysium::Core::Template::System::size MaxMatch = 258>
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
		inline Elysium::Core::Template::Container::Vector<TokenType> Decode(const T* Data, const Elysium::Core::Template::System::size Length)
		{
			Elysium::Core::Template::Container::Vector<TokenType> Result;

			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				const Elysium::Core::Template::Container::Pair<Elysium::Core::Template::System::size, Elysium::Core::Template::System::size> Match = FindMatch(Data, Length, i);
				const Elysium::Core::Template::System::size& MatchLength = Match.GetFirst();
				const Elysium::Core::Template::System::size& MatchDistance = Match.GetSecond();

				if (MatchLength >= MinMatch)
				{
					assert(MatchDistance > 0);
					assert(MatchDistance <= _SlidingWindow.GetLength());
					assert(MatchLength <= MaxMatch);
				}

				TokenType CurrentToken{};

				//if (MatchLength >= MinMatch)	// allows overlaps (rest of my implementation doesn't!!!!!)
				if (MatchLength >= MinMatch && MatchDistance >= MatchLength)	// prevents overlaps
				{
					CurrentToken._Length = MatchLength;
					CurrentToken._Distance = MatchDistance;
					Result.PushBack(CurrentToken);

					_SlidingWindow.PushBackRange(&Data[i], MatchLength);

					i += MatchLength - 1;
				}
				else
				{
					CurrentToken._Literal = Data[i];
					Result.PushBack(CurrentToken);

					_SlidingWindow.PushBack(CurrentToken._Literal);
				}

				TrimSlidingWindow();
			}

			return Result;
		}
	private:
		inline const Elysium::Core::Template::Container::Pair<Elysium::Core::Template::System::size, Elysium::Core::Template::System::size> FindMatch(const T* Data, 
			const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Position)
		{
			Elysium::Core::Template::System::size BestLength = 0;
			Elysium::Core::Template::System::size BestDistance = 0;

			for (Elysium::Core::Template::System::size i = 0; i < _SlidingWindow.GetLength(); ++i)
			{
				Elysium::Core::Template::System::size Count = 0;
				while (Count < MaxMatch && Position + Count < Length && i + Count < _SlidingWindow.GetLength() && _SlidingWindow[i + Count] == Data[Position + Count])
				{
					++Count;
				}

				if (Count > BestLength)
				{
					BestLength = Count;
					BestDistance = _SlidingWindow.GetLength() - i;
				}
			}

			return { BestLength, BestDistance };
		}

		inline void TrimSlidingWindow()
		{
			Elysium::Core::Template::System::size SlidingWindowLength = _SlidingWindow.GetLength();
			if (SlidingWindowLength > MaxWindow)
			{
				Elysium::Core::Template::System::size Excess = SlidingWindowLength - MaxWindow;
				_SlidingWindow.Erase(_SlidingWindow.GetBegin(), _SlidingWindow.GetBegin() + Excess);
			}
		}
	private:
		Elysium::Core::Template::Container::Vector<SymbolType> _SlidingWindow{};
	};
}
#endif
