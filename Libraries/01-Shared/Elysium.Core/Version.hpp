/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#define ELYSIUM_CORE_URISYNTAXFLAGS

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT Version final
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

			virtual Version& operator=(const Version& Value);
		private:
			unsigned int _Major;
			unsigned int _Minor;
			unsigned int _Build;
			unsigned int _Revision;
		};
	}
}
#endif
