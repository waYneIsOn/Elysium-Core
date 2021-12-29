/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ENVIRONMENT
#define ELYSIUM_CORE_ENVIRONMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

namespace Elysium::Core
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_API Environment final
	{
	public:
		Environment() = delete;

		Environment(const Environment& Source) = delete;

		Environment(Environment&& Right) noexcept = delete;

		~Environment() = delete;
	public:
		Environment& operator=(const Environment& Source) = delete;

		Environment& operator=(Environment&& Right) noexcept = delete;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const bool Is64BitProcess();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::Utf8String MachineName();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::Utf8String& NewLine();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const OperatingSystem OSVersion();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::uint32_t ProcessorCount();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::Utf8String UserName();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::Utf8String SystemDirectory();
	private:
		inline static const Elysium::Core::Utf8String _NewLine = Elysium::Core::Utf8String(Template::Text::CharacterTraits<char8_t>::NewLineCharacters);

#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _InternalEncoding = Elysium::Core::Text::Encoding::UTF16LE();
#endif
	};
}
#endif
