/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLETEMPLATE
#define ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLETEMPLATE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Math::Geometry
{
	template <typename T>
	class RectangleTemplate
	{
	public:
		RectangleTemplate();
		RectangleTemplate(T X, T Y, T Width, T Height);
		virtual ~RectangleTemplate();
	private:
		T _X;
		T _Y;
		T _Width;
		T _Height;
	};

	template<typename T>
	inline RectangleTemplate<T>::RectangleTemplate()
	{
	}
	template<typename T>
	inline RectangleTemplate<T>::RectangleTemplate(T X, T Y, T Width, T Height)
		: _X(X), _Y(Y), _Width(Width), _Height(Height)
	{
	}
	template<typename T>
	inline RectangleTemplate<T>::~RectangleTemplate()
	{
	}
}
#endif
