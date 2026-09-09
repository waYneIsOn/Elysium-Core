/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_MESSAGE
#define ELYSIUM_CORE_TEMPLATE_DISPATCH_MESSAGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../Functional/RemoveConstVolatile.hpp"
#endif

namespace Elysium::Core::Template::Dispatch
{
	template <class Id, class Payload>
	class Message
	{
	public:
		using IdType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Id>;
		using PayloadType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Payload>;
	public:
		constexpr Message() noexcept = default;

		inline constexpr Message(const IdType Id, const PayloadType& Payload)
			: _Id(Id), _Payload(Payload)
		{ }

		constexpr Message(const Message& Source) = default;

		constexpr Message(Message&& Right) noexcept = delete;

		constexpr ~Message() noexcept = default;
	public:
		constexpr Message& operator=(const Message& Source) = default;

		constexpr Message& operator=(Message&& Right) noexcept = delete;
	public:
		inline constexpr const IdType GetId() const noexcept
		{
			return _Id;
		}

		inline constexpr const PayloadType GetPayload() const noexcept
		{
			return _Payload;
		}
	private:
		IdType _Id;
		PayloadType _Payload;
	};

	template <class Id>
	class Message<Id, void>
	{
	public:
		using IdType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Id>;
		using PayloadType = Elysium::Core::Template::Functional::RemoveConstVolatileType<void>;
	public:
		constexpr Message() noexcept = default;

		inline constexpr Message(const IdType Id)
			: _Id(Id)
		{ }

		constexpr Message(const Message& Source) = default;

		constexpr Message(Message&& Right) noexcept = delete;

		constexpr ~Message() noexcept = default;
	public:
		constexpr Message& operator=(const Message& Source) = default;

		constexpr Message& operator=(Message&& Right) noexcept = delete;
	public:
		inline constexpr const IdType GetId() const noexcept
		{
			return _Id;
		}
	private:
		IdType _Id;
	};
}
#endif
