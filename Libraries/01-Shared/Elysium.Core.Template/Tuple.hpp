/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLEANDCONSTRUCTIBLE
#include "MoveAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="...TRest"></typeparam>
	template <Concepts::MoveAssignableAndConstructible ...TRest>
	class Tuple final
	{ };
	
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	template <Concepts::MoveAssignableAndConstructible T1>
	class Tuple<T1>
	{
	public:
		Tuple(T1 Item1);

		Tuple(const Tuple<T1>& Source) = delete;

		Tuple(Tuple<T1>&& Right) noexcept = delete;

		~Tuple();
	public:
		Tuple<T1>& operator=(const Tuple<T1>& Source) = delete;

		Tuple<T1>& operator=(Tuple<T1>&& Right) noexcept = delete;
	public:
		T1& GetItem1();

		const T1& GetItem1() const;
	private:
		T1 _Item1;
	};

	template<Concepts::MoveAssignableAndConstructible T1>
	inline Tuple<T1>::Tuple(T1 Item1)
		: _Item1(Item1)
	{ }
	template<Concepts::MoveAssignableAndConstructible T1>
	inline Tuple<T1>::~Tuple()
	{ }

	template<Concepts::MoveAssignableAndConstructible T1>
	inline T1& Tuple<T1>::GetItem1()
	{
		return _Item1;
	}

	template<Concepts::MoveAssignableAndConstructible T1>
	inline const T1& Tuple<T1>::GetItem1() const
	{
		return _Item1;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	/// <typeparam name="T2"></typeparam>
	template <Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	class Tuple<T1, T2>
	{
	public:
		Tuple(T1 Item1, T2 Item2);

		Tuple(const Tuple<T1, T2>& Source) = delete;

		Tuple(Tuple<T1, T2>&& Right) noexcept;

		~Tuple();
	public:
		Tuple<T1, T2>& operator=(const Tuple<T1, T2>& Source) = delete;

		Tuple<T1, T2>& operator=(Tuple<T1, T2>&& Right) noexcept;
	public:
		T1& GetItem1();

		T2& GetItem2();

		const T1& GetItem1() const;

		const T2& GetItem2() const;
	private:
		T1 _Item1;
		T2 _Item2;
	};

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	inline Tuple<T1, T2>::Tuple(T1 Item1, T2 Item2)
		: _Item1(Item1), _Item2(Item2)
	{ }
	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	inline Tuple<T1, T2>::Tuple(Tuple<T1, T2>&& Right) noexcept
		: _Item1(), _Item2()
	{
		*this = Functional::Move(Right);
	}
	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	inline Tuple<T1, T2>::~Tuple()
	{ }

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	inline Tuple<T1, T2>& Tuple<T1, T2>::operator=(Tuple<T1, T2>&& Right) noexcept
	{
		if (this != &Right)
		{
			_Item1 = Functional::Move(Right._Item1);
			_Item2 = Functional::Move(Right._Item2);
		}
		return *this;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	inline T1& Tuple<T1, T2>::GetItem1()
	{
		return _Item1;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	inline T2& Tuple<T1, T2>::GetItem2()
	{
		return _Item2;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
	inline const T1& Tuple<T1, T2>::GetItem1() const
	{
		return _Item1;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2>
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
	template <Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	class Tuple<T1, T2, T3>
	{
	public:
		Tuple(T1 Item1, T2 Item2, T3 Item3);

		Tuple(const Tuple<T1, T2, T3>& Source) = delete;

		Tuple(Tuple<T1, T2, T3>&& Right) noexcept = delete;

		~Tuple();
	public:
		Tuple<T1, T2, T3>& operator=(const Tuple<T1, T2, T3>& Source) = delete;

		Tuple<T1, T2, T3>& operator=(Tuple<T1, T2, T3>&& Right) noexcept = delete;
	public:
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

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline Tuple<T1, T2, T3>::Tuple(T1 Item1, T2 Item2, T3 Item3)
		: _Item1(Item1), _Item2(Item2), _Item3(Item3)
	{ }
	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline Tuple<T1, T2, T3>::~Tuple()
	{ }

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline T1& Tuple<T1, T2, T3>::GetItem1()
	{
		return _Item1;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline T2& Tuple<T1, T2, T3>::GetItem2()
	{
		return _Item2;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline T3& Tuple<T1, T2, T3>::GetItem3()
	{
		return _Item3;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline const T1& Tuple<T1, T2, T3>::GetItem1() const
	{
		return _Item1;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline const T2& Tuple<T1, T2, T3>::GetItem2() const
	{
		return _Item2;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3>
	inline const T3& Tuple<T1, T2, T3>::GetItem3() const
	{
		return _Item3;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	/// <typeparam name="T2"></typeparam>
	/// <typeparam name="T3"></typeparam>
	/// <typeparam name="T4"></typeparam>
	template <Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3,
		Concepts::MoveAssignableAndConstructible T4>
	class Tuple<T1, T2, T3, T4>
	{
	public:
		Tuple(T1 Item1, T2 Item2, T3 Item3, T4 Item4);

		Tuple(const Tuple<T1, T2, T3, T4>& Source) = delete;

		Tuple(Tuple<T1, T2, T3, T4>&& Right) noexcept = delete;

		~Tuple();
	public:
		Tuple<T1, T2, T3, T4>& operator=(const Tuple<T1, T2, T3, T4>& Source) = delete;

		Tuple<T1, T2, T3, T4>& operator=(Tuple<T1, T2, T3, T4>&& Right) noexcept = delete;
	public:
		T1& GetItem1();

		T2& GetItem2();

		T3& GetItem3();

		T4& GetItem4();

		const T1& GetItem1() const;

		const T2& GetItem2() const;

		const T3& GetItem3() const;

		const T4& GetItem4() const;
	private:
		T1 _Item1;
		T2 _Item2;
		T3 _Item3;
		T4 _Item4;
	};

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3, 
		Concepts::MoveAssignableAndConstructible T4>
	inline Tuple<T1, T2, T3, T4>::Tuple(T1 Item1, T2 Item2, T3 Item3, T4 Item4)
		: _Item1(Item1), _Item2(Item2), _Item3(Item3), _Item4(Item4)
	{ }
	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3, 
		Concepts::MoveAssignableAndConstructible T4>
	inline Tuple<T1, T2, T3, T4>::~Tuple()
	{ }

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3,
		Concepts::MoveAssignableAndConstructible T4>
	inline T1& Tuple<T1, T2, T3, T4>::GetItem1()
	{
		return _Item1;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3,
		Concepts::MoveAssignableAndConstructible T4>
	inline T2& Tuple<T1, T2, T3, T4>::GetItem2()
	{
		return _Item2;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3, 
		Concepts::MoveAssignableAndConstructible T4>
	inline T3& Tuple<T1, T2, T3, T4>::GetItem3()
	{
		return _Item3;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3,
		Concepts::MoveAssignableAndConstructible T4>
	inline T4& Tuple<T1, T2, T3, T4>::GetItem4()
	{
		return _Item4;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3, 
		Concepts::MoveAssignableAndConstructible T4>
	inline const T1& Tuple<T1, T2, T3, T4>::GetItem1() const
	{
		return _Item1;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3, 
		Concepts::MoveAssignableAndConstructible T4>
	inline const T2& Tuple<T1, T2, T3, T4>::GetItem2() const
	{
		return _Item2;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3,
		Concepts::MoveAssignableAndConstructible T4>
	inline const T3& Tuple<T1, T2, T3, T4>::GetItem3() const
	{
		return _Item3;
	}

	template<Concepts::MoveAssignableAndConstructible T1, Concepts::MoveAssignableAndConstructible T2, Concepts::MoveAssignableAndConstructible T3, 
		Concepts::MoveAssignableAndConstructible T4>
	inline const T4& Tuple<T1, T2, T3, T4>::GetItem4() const
	{
		return _Item4;
	}
}
#endif
