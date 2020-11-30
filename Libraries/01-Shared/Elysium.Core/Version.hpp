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
		Version(const Elysium::Core::uint32_t& Major, const Elysium::Core::uint32_t& Minor);
		Version(const Elysium::Core::uint32_t& Major, const Elysium::Core::uint32_t& Minor, const Elysium::Core::uint32_t& Build);
		Version(const Elysium::Core::uint32_t& Major, const Elysium::Core::uint32_t& Minor, const Elysium::Core::uint32_t& Build, const Elysium::Core::uint32_t& Revision);
		Version(const Version& Source);
		Version(Version&& Right) noexcept;
		~Version();

		Version& operator=(const Version& Other);
		Version& operator=(Version&& Right) noexcept;

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
		const Elysium::Core::uint32_t GetMajor() const;
		const Elysium::Core::uint32_t GetMinor() const;
		const Elysium::Core::uint32_t GetBuild() const;
		const Elysium::Core::uint32_t GetRevision() const;

		static void Parse(const StringView& Input, Version& Result);
		static Version Parse(const StringView& Input);
	private:
		Elysium::Core::uint32_t _Major;
		Elysium::Core::uint32_t _Minor;
		Elysium::Core::uint32_t _Build;
		Elysium::Core::uint32_t _Revision;

		const Elysium::Core::uint32_t Compare(const Version& Other) const;
	};
}
#endif
