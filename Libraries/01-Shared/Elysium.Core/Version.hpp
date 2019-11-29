/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_VERSION
#define ELYSIUM_CORE_VERSION

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API Version final
		{
		public:
			Version();
			Version(const uint32_t& Major, const uint32_t& Minor);
			Version(const uint32_t& Major, const uint32_t& Minor, const uint32_t& Build);
			Version(const uint32_t& Major, const uint32_t& Minor, const uint32_t& Build, const uint32_t& Revision);
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

			friend Elysium::Core::IO::Stream& operator<<(Elysium::Core::IO::Stream& Target, const Version& Version);
			friend Elysium::Core::IO::Stream& operator>>(Elysium::Core::IO::Stream& Source, const Version& Version);

			const uint32_t GetMajor() const;
			const uint32_t GetMinor() const;
			const uint32_t GetBuild() const;
			const uint32_t GetRevision() const;

			static void Parse(const StringView& Input, Version& Result);
			static Version Parse(const StringView& Input);
		private:
			uint32_t _Major;
			uint32_t _Minor;
			uint32_t _Build;
			uint32_t _Revision;

			uint32_t Compare(const Version& Other) const;
		};
	}
}
#endif
