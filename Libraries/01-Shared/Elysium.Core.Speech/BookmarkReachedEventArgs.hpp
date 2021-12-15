/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_BOOKMARKREACHEDEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_BOOKMARKREACHEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS
#include "PromptEventArgs.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API BookmarkReachedEventArgs : public PromptEventArgs
	{
		friend class SpeechSynthesizer;
	protected:
		BookmarkReachedEventArgs(String&& Prompt, const Elysium::Core::uint64_t Ticks, String&& Bookmark);
	public:
		BookmarkReachedEventArgs(const BookmarkReachedEventArgs& Source) = delete;

		BookmarkReachedEventArgs(BookmarkReachedEventArgs&& Right) noexcept = delete;

		virtual ~BookmarkReachedEventArgs();
	public:
		BookmarkReachedEventArgs& operator=(const BookmarkReachedEventArgs& Source) = delete;

		BookmarkReachedEventArgs& operator=(BookmarkReachedEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::TimeSpan& GetAudioPosition() const;

		const String& GetBookmark() const;
	private:
		TimeSpan _AudioPosition;
		String _Bookmark;
	};
}
#endif
