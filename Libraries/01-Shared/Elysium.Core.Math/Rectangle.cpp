#include "Rectangle.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Math::Geometry::Rectangle::Rectangle()
	: X(0), Y(0), Width(0), Height(0)
{ }
Elysium::Core::Math::Geometry::Rectangle::Rectangle(Elysium::Core::uint32_t X, Elysium::Core::uint32_t Y, Elysium::Core::uint32_t Width, Elysium::Core::uint32_t Height)
	: X(X), Y(Y), Width(Width), Height(Height)
{ }
Elysium::Core::Math::Geometry::Rectangle::Rectangle(const Rectangle & Source)
	: X(Source.X), Y(Source.Y), Width(Source.Width), Height(Source.Height)
{ }
Elysium::Core::Math::Geometry::Rectangle::Rectangle(Rectangle&& Right) noexcept
	: X(0), Y(0), Width(0), Height(0)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}
Elysium::Core::Math::Geometry::Rectangle::~Rectangle()
{ }

Elysium::Core::Math::Geometry::Rectangle& Elysium::Core::Math::Geometry::Rectangle::operator=(const Rectangle & Source)
{
	if (this != &Source)
	{
		X = Source.X;
		Y = Source.Y;
		Width = Source.Width;
		Height = Source.Height;
	}
	return *this;
}

Elysium::Core::Math::Geometry::Rectangle& Elysium::Core::Math::Geometry::Rectangle::operator=(Rectangle&& Right) noexcept
{
	if (this != &Right)
	{
		X = Elysium::Core::Template::Functional::Move(Right.X);
		Y = Elysium::Core::Template::Functional::Move(Right.Y);
		Width = Elysium::Core::Template::Functional::Move(Right.Width);
		Height = Elysium::Core::Template::Functional::Move(Right.Height);
	}
	return *this;
}

const bool Elysium::Core::Math::Geometry::Rectangle::Contains(const Rectangle& Other) const
{
	throw 1;
}

void Elysium::Core::Math::Geometry::Rectangle::Inflate(const Elysium::Core::uint32_t HorizontalAmount, const Elysium::Core::uint32_t VerticalAmount)
{
	X -= HorizontalAmount;
	Width += HorizontalAmount;

	Y -= VerticalAmount;
	Height += VerticalAmount;
}

const bool Elysium::Core::Math::Geometry::Rectangle::Intersects(const Rectangle& Other) const
{
	//return X < Other.Width && Width > Other.X && Y > Other.Height && Height < Other.Y;
	throw 1;
}
