/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_MESSAGEQUEUE
#define ELYSIUM_CORE_TEMPLATE_DISPATCH_MESSAGEQUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEENDEDQUEUE
#include "../Container/DoubleEndedQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_MESSAGE
#include "Message.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../Functional/RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "../Threading/Mutex.hpp"
#endif

namespace Elysium::Core::Template::Dispatch
{
	template <class Message>
	class MessageQueue
	{
	public:
		using MessageType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Message>;

		using IdType = Message::IdType;
		using PayloadType = Message::PayloadType;
	public:
		constexpr MessageQueue() noexcept = default;

		constexpr MessageQueue(const MessageQueue& Source) = delete;

		constexpr MessageQueue(MessageQueue&& Right) noexcept = delete;

		constexpr ~MessageQueue() noexcept = default;
	public:
		constexpr MessageQueue& operator=(const MessageQueue& Source) = delete;

		constexpr MessageQueue& operator=(MessageQueue&& Right) noexcept = delete;
	public:
		inline void Post(MessageType&& Message)
		{
			_Mutex.Lock();
			_FiFoQueue.PushBack(Message);
			_Mutex.Unlock();
		}
		/*
		inline constexpr const bool TryPost(MessageType&& Message) noexcept
		{
			return false;
		}
		*/
	public:
		inline constexpr const bool Get(MessageType& Message)
		{
			_Mutex.Lock();
			if (_FiFoQueue.GetIsEmpty())
			{
				_Mutex.Unlock();

				return false;
			}

			MessageType& FrontMessage = _FiFoQueue.GetFront();
			Message = FrontMessage;
			_FiFoQueue.PopFront();
			_Mutex.Unlock();

			return true;
		}
	private:
		Elysium::Core::Template::Threading::Mutex _Mutex{};
		Elysium::Core::Template::Container::DoubleEndedQueue<MessageType> _FiFoQueue{};
	};
}
#endif
