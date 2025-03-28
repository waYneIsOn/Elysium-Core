/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_ARGUMENTDESCRIPTOR
#define ELYSIUM_CORE_COMMANDLINE_ARGUMENTDESCRIPTOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOID
#include "../Elysium.Core.Template/IsVoid.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	template <class ...T>
	class ArgumentDescriptor
	{
	public:
		constexpr ArgumentDescriptor() = delete;

		constexpr ArgumentDescriptor(const char8_t* Command, const char8_t* Name, const char8_t* Description, const bool IsRequired = false);

		constexpr ArgumentDescriptor(const ArgumentDescriptor& Source) = delete;

		constexpr ArgumentDescriptor(ArgumentDescriptor&& Right) noexcept = delete;

		constexpr ~ArgumentDescriptor() = default;
	public:
		constexpr ArgumentDescriptor& operator=(const ArgumentDescriptor& Source) = delete;

		constexpr ArgumentDescriptor& operator=(ArgumentDescriptor&& Right) noexcept = delete;
	public:
		const bool IsFlag() const;
	private:
		Elysium::Core::Utf8String _Command;
		//... _Alternatives;	// @ToDo: multiple alternatives? (command is -i, alternatives /i, -install, /install?)
		// could simply handle this through different instances of ArgumentDescriptor? 
		// (or rather have multiple keys in the hashtable point to the same thing)
		Elysium::Core::Utf8String _Name;
		Elysium::Core::Utf8String _Description;
		bool _IsRequired;
	};

	template<class ...T>
	inline constexpr ArgumentDescriptor<T...>::ArgumentDescriptor(const char8_t* Command, const char8_t* Name, const char8_t* Description, const bool IsRequired)
		: _Command(Command), _Name(Name), _Description(Description), _IsRequired(IsRequired)
	{ }

	template<class ...T>
	inline const bool ArgumentDescriptor<T...>::IsFlag() const
	{
		// @ToDo: "T...[0]" seems to be only useable in C++26 and onwards. 
		// probably will need to implement TupleElement for parameter pack indexing
		return sizeof...(T) == 1 && Elysium::Core::Template::TypeTraits::IsVoidValue<T...[0]>;
	}
}
#endif
