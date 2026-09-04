/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_EVENT
#define ELYSIUM_CORE_TEMPLATE_DISPATCH_EVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Container/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "../Threading/Mutex.hpp"
#endif

namespace Elysium::Core::Template::Dispatch
{
	template <bool ThreadSafe, bool MultipleHandler, bool SynchronousDispatch, class ReturnType, class ...Args>
	class Event
	{
	public:
		constexpr Event() noexcept = default;

		constexpr Event(const Event& Source) = delete;

		constexpr Event(Event&& Right) noexcept = delete;

		constexpr ~Event() noexcept = default;
	public:
		constexpr Event& operator=(const Event& Source) = delete;

		constexpr Event& operator=(Event&& Right) noexcept = delete;
	public:
		inline constexpr const Event& operator+=(const Elysium::Core::Template::Container::Delegate<ReturnType, Args...>& Handler)
		{
			_HandlerList.PushBack(Handler);
			return *this;
		}

		inline constexpr const Event& operator-=(const Elysium::Core::Template::Container::Delegate<ReturnType, Args...>& Handler)
		{
			_HandlerList.Erase(Handler);
			return *this;
		}

		inline constexpr ReturnType operator()(Args... EventArgs)
		{
			for (Elysium::Core::Template::System::size i = 0; i < _HandlerList.GetLength(); ++i)
			{
				_HandlerList[i](EventArgs...);
			}

			// @ToDo
			return ReturnType();
		}
	private:
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Container::Delegate<ReturnType, Args...>> _HandlerList{};
	};
}
#endif
