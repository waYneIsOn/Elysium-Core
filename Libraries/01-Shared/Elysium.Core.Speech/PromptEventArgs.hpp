/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS
#define ELYSIUM_CORE_SPEECH_SYNTHESIS_PROMPTEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SPEECH_API
#include "API.hpp"
#endif

namespace Elysium::Core::Speech::Synthesis
{
	class ELYSIUM_CORE_SPEECH_API PromptEventArgs
	{
	protected:
		PromptEventArgs();
	public:
		PromptEventArgs(const PromptEventArgs& Source) = delete;

		PromptEventArgs(PromptEventArgs&& Right) noexcept = delete;

		virtual ~PromptEventArgs();
	public:
		PromptEventArgs& operator=(const PromptEventArgs& Source) = delete;

		PromptEventArgs& operator=(PromptEventArgs&& Right) noexcept = delete;
	};
}
#endif
