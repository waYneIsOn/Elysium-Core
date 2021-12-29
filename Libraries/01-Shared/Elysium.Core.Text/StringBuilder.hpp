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
/*
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Template/StringBuilder.hpp"
#endif
*/
namespace Elysium::Core::Text
{
	/*
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBuilderBase<char8_t>;

	using StringBuilder = Elysium::Core::Template::Text::StringBuilderBase<char8_t>;
	*/

	// ToDo: make use of LinkedList
	class ELYSIUM_CORE_API StringBuilder final
	{
	public:
		StringBuilder();

		StringBuilder(const Elysium::Core::size Capacity);

		StringBuilder(const StringBuilder& Source);

		~StringBuilder();
	public:
		const Elysium::Core::size GetCapacity() const;

		virtual const Elysium::Core::size GetLength() const;

		void SetLength(const Elysium::Core::size Value);
	public:
		void Append(const Elysium::Core::Utf8String& Value);

		void Append(const char8_t Value);

		void Append(const char8_t* Value, const Elysium::Core::size Length);

		void Clear();

		Elysium::Core::size IndexOf(const char8_t Value) const;

		Elysium::Core::size IndexOf(const char8_t Value, const Elysium::Core::size StartIndex) const;

		Elysium::Core::size IndexOf(const char8_t* Value) const;

		Elysium::Core::size IndexOf(const char8_t* Value, const Elysium::Core::size StartIndex) const;

		void Remove(const Elysium::Core::size StartIndex, const Elysium::Core::size Length);

		Elysium::Core::Utf8String ToString();

		Elysium::Core::Utf8String ToString(const Elysium::Core::size Length);
	private:
		Elysium::Core::size _Capacity;
		char8_t* _Data;
		Elysium::Core::size _Length;

		void Resize(Elysium::Core::size DesiredMinimumSize);
	};
}
#endif
