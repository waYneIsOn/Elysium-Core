/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_TUPLE
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_TUPLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Collections
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="...TRest"></typeparam>
	template <class ...TRest>
	class Tuple final
	{ };
	
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	template <class T1>
	class Tuple<T1>
	{
	public:
		Tuple(T1 Item1);
		Tuple(const Tuple<T1>& Source) = delete;
		Tuple(Tuple<T1>&& Right) noexcept = delete;
		~Tuple();

		Tuple<T1>& operator=(const Tuple<T1>& Source) = delete;
		Tuple<T1>& operator=(Tuple<T1>&& Right) noexcept = delete;

		T1& GetItem1();

		const T1& GetItem1() const;
	private:
		T1 _Item1;
	};

	template<class T1>
	inline Tuple<T1>::Tuple(T1 Item1)
		: _Item1(Item1)
	{ }
	template<class T1>
	inline Tuple<T1>::~Tuple()
	{ }

	template<class T1>
	inline T1& Tuple<T1>::GetItem1()
	{
		return _Item1;
	}

	template<class T1>
	inline const T1& Tuple<T1>::GetItem1() const
	{
		return _Item1;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	/// <typeparam name="T2"></typeparam>
	template <class T1, class T2>
	class Tuple<T1, T2>
	{
	public:
		Tuple(T1 Item1, T2 Item2);
		Tuple(const Tuple<T1, T2>& Source) = delete;
		Tuple(Tuple<T1, T2>&& Right) noexcept;
		~Tuple();

		Tuple<T1, T2>& operator=(const Tuple<T1, T2>& Source) = delete;
		Tuple<T1, T2>& operator=(Tuple<T1, T2>&& Right) noexcept;

		T1& GetItem1();
		T2& GetItem2();

		const T1& GetItem1() const;
		const T2& GetItem2() const;
	private:
		T1 _Item1;
		T2 _Item2;
	};

	template<class T1, class T2>
	inline Tuple<T1, T2>::Tuple(T1 Item1, T2 Item2)
		: _Item1(Item1), _Item2(Item2)
	{ }
	template<class T1, class T2>
	inline Tuple<T1, T2>::Tuple(Tuple<T1, T2>&& Right) noexcept
		: _Item1(), _Item2()
	{
		*this = TypeTraits::Move(Right);
	}
	template<class T1, class T2>
	inline Tuple<T1, T2>::~Tuple()
	{ }

	template<class T1, class T2>
	inline Tuple<T1, T2>& Tuple<T1, T2>::operator=(Tuple<T1, T2>&& Right) noexcept
	{
		if (this != &Right)
		{
			_Item1 = TypeTraits::Move(Right._Item1);
			_Item2 = TypeTraits::Move(Right._Item2);
		}
		return *this;
	}

	template<class T1, class T2>
	inline T1& Tuple<T1, T2>::GetItem1()
	{
		return _Item1;
	}

	template<class T1, class T2>
	inline T2& Tuple<T1, T2>::GetItem2()
	{
		return _Item2;
	}

	template<class T1, class T2>
	inline const T1& Tuple<T1, T2>::GetItem1() const
	{
		return _Item1;
	}

	template<class T1, class T2>
	inline const T2& Tuple<T1, T2>::GetItem2() const
	{
		return _Item2;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	/// <typeparam name="T2"></typeparam>
	/// <typeparam name="T3"></typeparam>
	template <class T1, class T2, class T3>
	class Tuple<T1, T2, T3>
	{
	public:
		Tuple(T1 Item1, T2 Item2, T3 Item3);
		Tuple(const Tuple<T1, T2, T3>& Source) = delete;
		Tuple(Tuple<T1, T2, T3>&& Right) noexcept = delete;
		~Tuple();

		Tuple<T1, T2, T3>& operator=(const Tuple<T1, T2, T3>& Source) = delete;
		Tuple<T1, T2, T3>& operator=(Tuple<T1, T2, T3>&& Right) noexcept = delete;

		T1& GetItem1();
		T2& GetItem2();
		T3& GetItem3();

		const T1& GetItem1() const;
		const T2& GetItem2() const;
		const T3& GetItem3() const;
	private:
		T1 _Item1;
		T2 _Item2;
		T3 _Item3;
	};

	template<class T1, class T2, class T3>
	inline Tuple<T1, T2, T3>::Tuple(T1 Item1, T2 Item2, T3 Item3)
		: _Item1(Item1), _Item2(Item2), _Item3(Item3)
	{ }
	template<class T1, class T2, class T3>
	inline Tuple<T1, T2, T3>::~Tuple()
	{ }

	template<class T1, class T2, class T3>
	inline T1& Tuple<T1, T2, T3>::GetItem1()
	{
		return _Item1;
	}

	template<class T1, class T2, class T3>
	inline T2& Tuple<T1, T2, T3>::GetItem2()
	{
		return _Item2;
	}

	template<class T1, class T2, class T3>
	inline T3& Tuple<T1, T2, T3>::GetItem3()
	{
		return _Item3;
	}

	template<class T1, class T2, class T3>
	inline const T1& Tuple<T1, T2, T3>::GetItem1() const
	{
		return _Item1;
	}

	template<class T1, class T2, class T3>
	inline const T2& Tuple<T1, T2, T3>::GetItem2() const
	{
		return _Item2;
	}

	template<class T1, class T2, class T3>
	inline const T3& Tuple<T1, T2, T3>::GetItem3() const
	{
		return _Item3;
	}
}
#endif
