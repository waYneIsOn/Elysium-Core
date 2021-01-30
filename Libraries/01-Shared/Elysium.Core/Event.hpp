/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_EVENT
#define ELYSIUM_CORE_EVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

namespace Elysium::Core
{
	template <class ReturnType, class ...Args>
	class Event final
	{
	public:
		Event();
		Event(const Event& Source) = delete;
		Event(Event&& Right) noexcept = delete;
		~Event();

		Event& operator=(const Event& Source) = delete;
		Event& operator=(Event&& Right) noexcept = delete;

		const Event& operator+=(const Delegate<ReturnType, Args...>& Handler);
		const Event& operator-=(const Delegate<ReturnType, Args...>& Handler);

		void operator()(void* Sender, const EventArgs& EventArgs);
	private:
		Collections::Template::List<Delegate<ReturnType, Args...>> _HandlerList;
	};

	template<class ReturnType, class ...Args>
	inline Event<ReturnType, Args...>::Event()
		: _HandlerList()
	{ }

	template<class ReturnType, class ...Args>
	inline Event<ReturnType, Args...>::~Event()
	{ }

	template<class ReturnType, class ...Args>
	inline const Event<ReturnType, Args...> & Event<ReturnType, Args...>::operator+=(const Delegate<ReturnType, Args...>&Handler)
	{
		_HandlerList.Add(Handler);
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline const Event<ReturnType, Args...> & Event<ReturnType, Args...>::operator-=(const Delegate<ReturnType, Args...>& Handler)
	{
		_HandlerList.Remove(Handler);
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline void Event<ReturnType, Args...>::operator()(void* Sender, const EventArgs& EventArgs)
	{
		for (size_t i = 0; i < _HandlerList.GetCount(); i++)
		{
			_HandlerList[i](Sender, EventArgs);
		}
	}
}
#endif
