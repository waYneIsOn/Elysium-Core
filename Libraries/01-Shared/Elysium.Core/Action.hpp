/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ACTION
#define ELYSIUM_CORE_ACTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

namespace Elysium::Core
{
	using Action = Elysium::Core::Template::Container::Delegate<void>;

	template<class T>
	using Action1 = Elysium::Core::Template::Container::Delegate<void, T>;

	template<class T1, class T2>
	using Action2 = Elysium::Core::Template::Container::Delegate<void, T1, T2>;

	template<class T1, class T2, class T3>
	using Action3 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3>;

	template<class T1, class T2, class T3, class T4>
	using Action4 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4>;

	template<class T1, class T2, class T3, class T4, class T5>
	using Action5 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5>;

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	using Action6 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	using Action7 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	using Action8 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
	using Action9 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
	using Action10 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
	using Action11 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
	using Action12 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
	using Action13 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
	using Action14 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
	using Action15 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>;

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14,class T15, class T16>
	using Action16 = Elysium::Core::Template::Container::Delegate<void, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16>;
}
#endif
