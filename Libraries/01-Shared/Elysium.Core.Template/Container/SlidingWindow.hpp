/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../Concepts/NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER
#include "RingBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../Math/Min.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Memory/DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Elysium::Core::Template::Concepts::NonConstant T, Elysium::Core::Template::System::size Capacity = 32768, 
		class Container = Elysium::Core::Template::Container::RingBuffer<T, Capacity>>
	class SlidingWindow
	{
	public:
		using Value = Container::Value;
		using ConstValue = Container::ConstValue;

		using Pointer = Container::Pointer;
		using ConstPointer = Container::ConstPointer;

		using Reference = Container::Reference;
		using ConstReference = Container::ConstReference;
		using RValueReference = Container::RValueReference;
	public:
		inline static constexpr const bool CanUseFastModulo = Container::CanUseFastModulo;
	private:
		inline static constexpr const Elysium::Core::Template::System::size ItemSize = sizeof(Value);
	public:
		constexpr SlidingWindow() = default;

		constexpr SlidingWindow(const SlidingWindow& Source) = delete;

		constexpr SlidingWindow(SlidingWindow&& Right) noexcept = delete;

		inline ~SlidingWindow() = default;
	public:
		constexpr SlidingWindow& operator=(const SlidingWindow& Source) = delete;

		constexpr SlidingWindow& operator=(SlidingWindow&& Right) noexcept = delete;
	public:
		inline constexpr Reference operator[](const Elysium::Core::Template::System::size Index)
		{
			return _Buffer[Index];
		}

		inline constexpr ConstReference operator[](const Elysium::Core::Template::System::size Index) const
		{
			return _Buffer[Index];
		}
	public:
		inline constexpr Elysium::Core::Template::System::size GetCapacity() const
		{
			return _Buffer.GetCapacity();
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _Buffer.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::size GetHead() const noexcept
		{
			return _Buffer.GetHead();
		}

		inline constexpr const Elysium::Core::Template::System::size GetTail() const noexcept
		{
			return _Buffer.GetTail();
		}

		inline constexpr const bool GetIsEmpty() const //noexcept(_Buffer.GetIsEmpty())
		{
			return _Buffer.GetIsEmpty();
		}

		inline constexpr const bool GetIsFull() const //noexcept(_Buffer.GetIsFull())
		{
			return _Buffer.GetIsFull();
		}
	public:
		inline void Clear() noexcept
		{
			_Buffer.Clear();
		}
		
		inline void PushBackRange(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
		{
			if (Length > _Buffer.GetCapacity())
			{	// @ToDo
				throw;
			}

			Elysium::Core::Template::System::size RemainingLength = Length;

			while (RemainingLength > 0)
			{
				Elysium::Core::Template::System::size AvailableSlots = _Buffer.GetCapacity() - _Buffer.GetLength();

				if (RemainingLength > AvailableSlots)
				{
					Elysium::Core::Template::System::size RequiredDiscard = Elysium::Core::Template::Math::Min(RemainingLength - AvailableSlots, _Buffer.GetLength());
					_Buffer.CommitReadableSpan(RequiredDiscard);
				}

				Elysium::Core::Template::System::size BytesCopied = 0;

				Elysium::Core::Template::Container::View::MultiSpan<Value, 1024, 2> WriteableSpans = _Buffer.RequestWriteableSpan();
				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> WriteableSpan0 = WriteableSpans.GetFirst();
				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> WriteableSpan1 = WriteableSpans.GetSecond();

				const Elysium::Core::Template::System::size SlotsAvailable0 = WriteableSpan0.GetLength();
				const Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(RemainingLength, SlotsAvailable0);
				Elysium::Core::Template::Memory::MemCpy(WriteableSpan0.GetData(), &FirstItem[BytesCopied], BytesToCopy0);
				BytesCopied += BytesToCopy0;
								
				const Elysium::Core::Template::System::size SlotsAvailable1 = WriteableSpan1.GetLength();
				const Elysium::Core::Template::System::size BytesToCopy1 = Elysium::Core::Template::Math::Min(RemainingLength - BytesCopied, SlotsAvailable1);
				Elysium::Core::Template::Memory::MemCpy(WriteableSpan1.GetData(), &FirstItem[BytesCopied], BytesToCopy1);
				BytesCopied += BytesToCopy1;
				
				if (0 == BytesCopied)
				{	// @ToDo
					throw;
				}

				_Buffer.CommitWritableSpan(BytesCopied);

				RemainingLength -= BytesCopied;
			}

			if (0 != RemainingLength)
			{	// @ToDo
				throw;
			}
		}

		inline void PushBack(ConstReference Item)
		{
			if (_Buffer.GetIsFull())
			{
				_Buffer.CommitReadableSpan(1);
			}

			Elysium::Core::Template::System::size BytesCopied = 0;

			Elysium::Core::Template::Container::View::MultiSpan<Value, 1024, 2> WriteableSpans = _Buffer.RequestWriteableSpan();
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> WriteableSpan0 = WriteableSpans.GetFirst();
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> WriteableSpan1 = WriteableSpans.GetSecond();

			const Elysium::Core::Template::System::size SlotsAvailable0 = WriteableSpan0.GetLength();
			const Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(ItemSize, SlotsAvailable0);
			Elysium::Core::Template::Memory::MemCpy(WriteableSpan0.GetData(), &Item, BytesToCopy0);
			BytesCopied += BytesToCopy0;

			if (0 == BytesCopied)
			{
				const Elysium::Core::Template::System::size SlotsAvailable1 = WriteableSpan1.GetLength();
				const Elysium::Core::Template::System::size BytesToCopy1 = Elysium::Core::Template::Math::Min(ItemSize, SlotsAvailable1);
				Elysium::Core::Template::Memory::MemCpy(WriteableSpan1.GetData(), &Item, BytesToCopy1);
				BytesCopied += BytesToCopy1;
			}

			if (0 == BytesCopied)
			{	// @ToDo
				throw;
			}

			_Buffer.CommitWritableSpan(1);
		}

		inline void CopyFromHistory(const Elysium::Core::Template::System::size Distance, const Elysium::Core::Template::System::size Length)
		{
			_Buffer.CopyFromHistory(Distance, Length);
		}
	public:
		Container _Buffer;
	};
}
#endif
