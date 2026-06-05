/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_BINARYSTREAMREADER
#define ELYSIUM_CORE_TEMPLATE_IO_BINARYSTREAMREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "../Concepts/Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_INSTREAM
#include "InStream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Text/CharacterTraits.hpp"
#endif

namespace Elysium::Core::Template::IO
{
	/*
	template<Elysium::Core::Template::Concepts::Character C, class Traits = Elysium::Core::Template::Text::CharacterTraits<C>>
	class BinaryStreamReader
	{
	public:
		constexpr BinaryStreamReader() noexcept = delete;

		inline constexpr BinaryStreamReader(InStream& SourceStream)
			: _SourceStream(SourceStream)
		{ }

		constexpr BinaryStreamReader(const BinaryStreamReader& Source) = delete;

		constexpr BinaryStreamReader(BinaryStreamReader&& Right) noexcept = delete;

		virtual ~BinaryStreamReader() = default;
	public:
		constexpr BinaryStreamReader& operator=(const BinaryStreamReader& Source) = delete;

		constexpr BinaryStreamReader& operator=(BinaryStreamReader&& Right) noexcept = delete;
	public:
		inline InStream& GetUnderlyingStream()
		{
			return _SourceStream;
		}

		inline const InStream& GetUnderlyingStream() const
		{
			return _SourceStream;
		}
	public:

	private:
		InStream& _SourceStream;
	};
	*/
}
#endif
