#include "Point.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Math::Geometry::Point::Point()
	: X(0), Y(0)
{ }
Elysium::Core::Math::Geometry::Point::Point(Elysium::Core::uint32_t X, Elysium::Core::uint32_t Y)
	: X(X), Y(Y)
{ }
Elysium::Core::Math::Geometry::Point::Point(const Point& Source)
	: X(Source.X), Y(Source.Y)
{ }
Elysium::Core::Math::Geometry::Point::Point(Point&& Right) noexcept
	: X(0), Y(0)
{
	*this = std::move(Right);
}
Elysium::Core::Math::Geometry::Point::~Point()
{ }

Elysium::Core::Math::Geometry::Point& Elysium::Core::Math::Geometry::Point::operator=(const Point& Source)
{
	if (this != &Source)
	{
		X = Source.X;
		Y = Source.Y;
	}
	return *this;
}

Elysium::Core::Math::Geometry::Point& Elysium::Core::Math::Geometry::Point::operator=(Point&& Right) noexcept
{
	if (this != &Right)
	{
		X = Right.X;
		Y = Right.Y;

		Right.X = 0;
		Right.Y = 0;
	}
	return *this;
}
