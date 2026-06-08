/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77ENCODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77ENCODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR
#include "../../../Container/KeyValuePair.hpp"
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
	class LZ77Encoder
	{
	public:
		using Token = LZ77Token<T>;
	public:
		constexpr LZ77Encoder() = default;

		constexpr LZ77Encoder(const LZ77Encoder& Source) = delete;

		constexpr LZ77Encoder(LZ77Encoder&& Right) noexcept = delete;

		constexpr ~LZ77Encoder() = default;
	public:
		constexpr LZ77Encoder& operator=(const LZ77Encoder& Source) = delete;

		constexpr LZ77Encoder& operator=(LZ77Encoder&& Right) noexcept = delete;
	private:
		inline static constexpr const Elysium::Core::Template::System::size MaxWindow = 32768;	// 32 kb is the maximum allowed windows size in DEFLATE
		inline static constexpr const Elysium::Core::Template::System::uint8_t MinMatch = 3;	// DEFLATE uses a minumum of 3 - every smaller match is not worth encoding
		inline static constexpr const Elysium::Core::Template::System::uint16_t MaxMatch = 258;	// 258 seems to be efficient and again is the standard in DEFLATE
	public:
		inline Elysium::Core::Template::Container::Vector<Token> Write(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			Elysium::Core::Template::Container::Vector<Token> Result;

			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				const Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::size, Elysium::Core::Template::System::size> Match = FindMatch(Data, Length, i);
				const Elysium::Core::Template::System::size& MatchLength = Match.GetKey();
				const Elysium::Core::Template::System::size& MatchDistance = Match.GetValue();
				
				Token CurrentToken{};

				if (MatchLength >= MinMatch)
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

					_SlidingWindow.PushBackRange(&Data[i], 1);
				}

				TrimSlidingWindow();
			}

			return Result;
		}
	private:
		inline const Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::size, Elysium::Core::Template::System::size> FindMatch(
			const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Position)
		{
			Elysium::Core::Template::System::size BestLength = 0;
			Elysium::Core::Template::System::size BestDistance = 0;

			for (Elysium::Core::Template::System::size i = 0; i < _SlidingWindow.GetLength(); ++i)
			{
				Elysium::Core::Template::System::size Count = 0;

				while (Count < MaxMatch && Position + Count < Length && _SlidingWindow[i + Count] == Data[Position + Count])
				{
					++Count;

					if (i + Count >= _SlidingWindow.GetLength())
					{
						break;
					}
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
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _SlidingWindow;
	};
}
#endif
