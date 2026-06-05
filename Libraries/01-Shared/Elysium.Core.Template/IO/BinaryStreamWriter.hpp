/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_BINARYSTREAMWRITER
#define ELYSIUM_CORE_TEMPLATE_IO_BINARYSTREAMWRITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "../Concepts/Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_OUTSTREAM
#include "OutStream.hpp"
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
	class BinaryStreamWriter
	{
	public:
		constexpr BinaryStreamWriter() noexcept = delete;

		inline constexpr BinaryStreamWriter(OutStream& TargetStream)
			: _TargetStream(TargetStream)
		{ }

		constexpr BinaryStreamWriter(const BinaryStreamWriter& Source) = delete;

		constexpr BinaryStreamWriter(BinaryStreamWriter&& Right) noexcept = delete;

		virtual ~BinaryStreamWriter() = default;
	public:
		constexpr BinaryStreamWriter& operator=(const BinaryStreamWriter& Source) = delete;

		constexpr BinaryStreamWriter& operator=(BinaryStreamWriter&& Right) noexcept = delete;
	public:
		inline OutStream& GetUnderlyingStream()
		{
			return _TargetStream;
		}

		inline const OutStream& GetUnderlyingStream() const
		{
			return _TargetStream;
		}
	private:
		OutStream& _TargetStream;
	};
	*/
}
#endif
