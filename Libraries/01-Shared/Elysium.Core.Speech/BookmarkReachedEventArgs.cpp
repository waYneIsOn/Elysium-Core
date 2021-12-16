#include "BookmarkReachedEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::BookmarkReachedEventArgs::BookmarkReachedEventArgs(String&& Prompt, const Elysium::Core::uint64_t AudioPositionTicks, String&& Bookmark)
	: Elysium::Core::Speech::Synthesis::PromptEventArgs(Elysium::Core::Template::Functional::Move(Prompt)),
	_AudioPosition(AudioPositionTicks), _Bookmark(Elysium::Core::Template::Functional::Move(Bookmark))
{ }

Elysium::Core::Speech::Synthesis::BookmarkReachedEventArgs::~BookmarkReachedEventArgs()
{ }

const Elysium::Core::TimeSpan& Elysium::Core::Speech::Synthesis::BookmarkReachedEventArgs::GetAudioPosition() const
{
	return _AudioPosition;
}

const Elysium::Core::String& Elysium::Core::Speech::Synthesis::BookmarkReachedEventArgs::GetBookmark() const
{
	return _Bookmark;
}
