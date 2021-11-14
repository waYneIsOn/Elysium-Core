/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#define ELYSIUM_CORE_TEXT_STRINGBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Text
{
	// ToDo: make use of LinkedList
	class ELYSIUM_CORE_API StringBuilder final
	{
	public:
		StringBuilder();
		StringBuilder(const Elysium::Core::size Capacity);
		StringBuilder(const StringBuilder& Source);
		~StringBuilder();

		const Elysium::Core::size GetCapacity() const;
		virtual const Elysium::Core::size GetLength() const;

		void SetLength(const Elysium::Core::size Value);

		void Append(const Elysium::Core::String& Value);
		void Append(const char8_t Value);
		void Append(const char8_t* Value, const Elysium::Core::size Length);
		void Clear();
		Elysium::Core::size IndexOf(const char8_t Value) const;
		Elysium::Core::size IndexOf(const char8_t Value, const Elysium::Core::size StartIndex) const;
		Elysium::Core::size IndexOf(const char8_t* Value) const;
		Elysium::Core::size IndexOf(const char8_t* Value, const Elysium::Core::size StartIndex) const;
		void Remove(const Elysium::Core::size StartIndex, const Elysium::Core::size Length);

		Elysium::Core::String ToString();
		Elysium::Core::String ToString(const Elysium::Core::size Length);
	private:
		Elysium::Core::size _Capacity;
		char8_t* _Data;
		Elysium::Core::size _Length;

		void Resize(Elysium::Core::size DesiredMinimumSize);
	};
}
#endif
