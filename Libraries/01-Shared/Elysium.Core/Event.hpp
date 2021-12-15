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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif
/*
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif
*/
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
	public:
		Event& operator=(const Event& Source) = delete;

		Event& operator=(Event&& Right) noexcept = delete;
	public:
		const Event& operator+=(const Elysium::Core::Template::Container::Delegate<ReturnType, Args...>& Handler);

		const Event& operator-=(const Elysium::Core::Template::Container::Delegate<ReturnType, Args...>& Handler);

		ReturnType operator()(const Args... EventArgs);
	private:
		//Template::Container::Vector<Elysium::Core::Template::Container::Delegate<ReturnType, Args...>> _HandlerList;
		Collections::Template::List<Elysium::Core::Template::Container::Delegate<ReturnType, Args...>> _HandlerList;
	};

	template<class ReturnType, class ...Args>
	inline Event<ReturnType, Args...>::Event()
		: _HandlerList()
	{ }

	template<class ReturnType, class ...Args>
	inline Event<ReturnType, Args...>::~Event()
	{ }

	template<class ReturnType, class ...Args>
	inline const Event<ReturnType, Args...> & Event<ReturnType, Args...>::operator+=(const Elysium::Core::Template::Container::Delegate<ReturnType, Args...>&Handler)
	{
		_HandlerList.Add(Handler);
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline const Event<ReturnType, Args...> & Event<ReturnType, Args...>::operator-=(const Elysium::Core::Template::Container::Delegate<ReturnType, Args...>& Handler)
	{
		_HandlerList.Remove(Handler);
		return *this;
	}

	template<class ReturnType, class ...Args>
	inline ReturnType Event<ReturnType, Args...>::operator()(const Args ...EventArgs)
	{
		for (Elysium::Core::size i = 0; i < _HandlerList.GetCount(); i++)
		{
			_HandlerList[i](EventArgs...);
		}

		// ToDo
		return ReturnType();
	}
}
#endif
