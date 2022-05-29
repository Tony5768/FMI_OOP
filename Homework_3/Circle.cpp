#include "Circle.h"
#include "Rectangle.h"
#include "GlobalConstants.h"
#include "Utils.h"

const double PI = 3.1415;

void Circle::setRadius(double radius)
{
	this->radius = radius;
}

Circle::Circle() : Circle(0, 0, 0, DefaultColor) {}
Circle::Circle(double x, double y, double radius, const MyString& color) : Shape(1, color), radius(radius)
{
	setPoint(0, x, y);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}
double Circle::getPer() const
{
	return 2 * PI * radius;
}
bool Circle::isPointIn(double x, double y) const
{
	Shape::Point p(x, y);

	return p.getDist(getPointAtIndex(0)) <= radius;
}
Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::printData() const
{
	std::cout << "circle " << getPointAtIndex(0).x << " " << getPointAtIndex(0).y << " " << radius << " " << getColor();
}

void Circle::translate(double vertical, double horizontal)
{
	setPoint(0, getPointAtIndex(0).x + horizontal, getPointAtIndex(0).y + vertical);
}

MyString Circle::getType() const
{
	return "circle";
}

bool Circle::withinRectangle(double x, double y, double width, double height) const
{
	Shape::Point center = getPointAtIndex(0);
	return center.x + radius < x + width && center.x - radius > x &&
		center.y + radius < y&& center.y - radius > y - height;
}

bool Circle::withinCircle(double x, double y, double radius) const
{
	Shape::Point center(x, y);
	double distance = center.getDist(getPointAtIndex(0));

	return radius > (distance + this->radius);
}

void Circle::loadShape(const MyString& line, size_t& lineSize, size_t& currentIndex)
{
	double x = 0, y = 0, radius = 0;
	MyString color = "";

	loadArgument(line, lineSize, currentIndex, x);
	loadArgument(line, lineSize, currentIndex, y);
	loadArgument(line, lineSize, currentIndex, radius);
	loadArgument(line, lineSize, currentIndex, color);

	setPoint(0, x, y);
	setRadius(radius);
	setColor(color);
}
