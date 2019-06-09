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

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
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
			Version(const unsigned int& Major, const unsigned int& Minor);
			Version(const unsigned int& Major, const unsigned int& Minor, const unsigned int& Build);
			Version(const unsigned int& Major, const unsigned int& Minor, const unsigned int& Build, const unsigned int& Revision);
			~Version();

			const unsigned int GetMajor() const;
			const unsigned int GetMinor() const;
			const unsigned int GetBuild() const;
			const unsigned int GetRevision() const;

			static void Parse(const String& Input, Version* Result);
			static Version Parse(const String& Input);

			// assignment operator
			virtual Version& operator=(const Version& Other);

			// relational operators
			bool operator==(const Version& Other);
			bool operator!=(const Version& Other);
			bool operator<(const Version& Other);
			bool operator>(const Version& Other);
			bool operator<=(const Version& Other);
			bool operator>=(const Version& Other);

			// stream extraction and insertion
			friend Elysium::Core::IO::Stream& operator<<(Elysium::Core::IO::Stream& Target, const Version& Version);
			friend Elysium::Core::IO::Stream& operator>>(Elysium::Core::IO::Stream& Source, const Version& Version);
		private:
			unsigned int _Major;
			unsigned int _Minor;
			unsigned int _Build;
			unsigned int _Revision;

			int Compare(const Version& Other);
		};
	}
}
#endif
