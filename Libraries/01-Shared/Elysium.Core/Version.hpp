/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_VERSION
#define ELYSIUM_CORE_VERSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Version final
	{
	public:
		Version();

		Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor);

		Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor, const Elysium::Core::uint16_t& Build);

		Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor, const Elysium::Core::uint16_t& Build, const Elysium::Core::uint16_t& Revision);

		Version(const Version& Source);

		Version(Version&& Right) noexcept;

		~Version();
	public:
		Version& operator=(const Version& Other);

		Version& operator=(Version&& Right) noexcept;
	public:
		bool operator==(const Version& Other) const;

		bool operator!=(const Version& Other) const;

		bool operator<(const Version& Other) const;

		bool operator>(const Version& Other) const;

		bool operator<=(const Version& Other) const;

		bool operator>=(const Version& Other) const;
		/*
		friend Elysium::Core::IO::Stream& operator<<(Elysium::Core::IO::Stream& Target, const Elysium::Core::Version& Version);
		friend Elysium::Core::IO::Stream& operator>>(Elysium::Core::IO::Stream& Source, const Elysium::Core::Version& Version);
		*/
	public:
		static Version Parse(const Utf8String& Input);

		static Version Parse(const Utf8StringView Input);
	public:
		const Elysium::Core::uint16_t GetMajor() const;

		const Elysium::Core::uint16_t GetMinor() const;

		const Elysium::Core::uint16_t GetBuild() const;

		const Elysium::Core::uint16_t GetRevision() const;
	public:
		const Utf8String ToString();
	private:
		static constexpr const Elysium::Core::uint16_t Undefined = -1_ui16;

		static constexpr Elysium::Core::Utf8String::ConstCharacter Delimiter = u8'.';
	private:
		Elysium::Core::uint16_t _Major;
		Elysium::Core::uint16_t _Minor;
		Elysium::Core::uint16_t _Build;
		Elysium::Core::uint16_t _Revision;

		const Elysium::Core::uint8_t Compare(const Version& Other) const;
	};
}
#endif
