#include <stdexcept>
#include <string>
#include <iomanip>
#include "ShapeCollection.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "MyString.h"
#include "GlobalConstants.h"
#include "Utils.h"
#include "Serialize.h"

void ShapeCollection::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete data[i];
	}

	delete[] data;
}
void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	data = new Shape * [other.count];
	count = other.count;
	capacity = other.capacity;

	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];
	for (size_t i = 0; i < count; i++)
	{
		newCollection[i] = data[i];
	}

	delete[] data;
	data = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	count = 0;
	data = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}
ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addShape(Shape* shape)
{
	if (count == capacity)
	{
		resize();
	}

	data[count++] = shape;
}

void ShapeCollection::addRectangle(double x, double y, double width, double height, const MyString& color)
{
	Rectangle* rect = new Rectangle(x, y, width, height, color);
	addShape(rect);
}
void ShapeCollection::addCircle(double cx, double cy, int radius, const MyString& color)
{
	Circle* circlce = new Circle(cx, cy, radius, color);
	addShape(circlce);
}

void ShapeCollection::addLine(double x1, double y1, double x2, double y2, const MyString& color)
{
	Line* line = new Line(x1, y1, x2, y2, color);
	addShape(line);
}

void ShapeCollection::eraseFigure(size_t shapeIndex, MyString& shapeType)
{
	if (shapeIndex >= count)
	{
		throw std::invalid_argument("There is no figure number " + std::to_string(shapeIndex + 1) + "!\n");
	}

	--count;

	shapeType = data[shapeIndex]->getType();
	delete data[shapeIndex];

	for (size_t currentShapeIndex = shapeIndex; currentShapeIndex < count; currentShapeIndex++)
	{
		data[currentShapeIndex] = data[currentShapeIndex + 1];
	}
}

void ShapeCollection::translate(double vertical, double horizontal)
{
	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		data[shapeIndex]->translate(vertical, horizontal);
	}
}

void ShapeCollection::translate(double vertical, double horizontal, size_t shapeIndex, MyString& shapeType)
{
	if (shapeIndex > count)
	{
		throw std::out_of_range("There is no figure number " + std::to_string(shapeIndex + 1) + "!\n");
	}

	data[shapeIndex]->translate(vertical, horizontal);
	shapeType = data[shapeIndex]->getType();
}

void ShapeCollection::withinRectangle(double x, double y, double width, double height) const
{
	bool containsFigures = false;
	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		if (data[shapeIndex]->withinRectangle(x, y, width, height))
		{
			data[shapeIndex]->print();
			containsFigures = true;
		}
	}

	if (!containsFigures)
	{
		throw std::invalid_argument("No figures are located within rectangle " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + std::to_string(height) + "\n");
	}
}

void ShapeCollection::withinCircle(double cx, double cy, double radius) const
{
	bool containsFigures = false;
	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		if (data[shapeIndex]->withinCircle(cx, cy, radius))
		{
			data[shapeIndex]->print();
			containsFigures = true;
		}
	}

	if (!containsFigures)
	{
		throw std::invalid_argument("No figures are located within circle " + std::to_string(cx) + " " + std::to_string(cy) + " " + std::to_string(radius) + "\n");

	}
}

void ShapeCollection::pointIn(double x, double y) const
{
	bool containsFigures = false;
	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		if (data[shapeIndex]->isPointIn(x, y))
		{
			data[shapeIndex]->print();
			containsFigures = true;
		}
	}

	if (!containsFigures)
	{
		throw std::invalid_argument("No figures contains point " + std::to_string(x) + " " + std::to_string(y) + "\n");
	}
}

double ShapeCollection::getPerOfFigureByIndex(size_t shapeIndex) const
{
	if (shapeIndex >= count)
	{
		throw std::out_of_range("Out of range in shapes collection!\n");
	}

	return data[shapeIndex]->getPer();
}

double ShapeCollection::getAreaOfFigureByIndex(size_t shapeIndex) const
{
	if (shapeIndex >= count)
	{
		throw std::out_of_range("Out of range in shapes collection!\n");
	}

	return data[shapeIndex]->getArea();
}

double ShapeCollection::getIfPointInShapeByIndex(size_t shapeIndex, double x, double y) const
{
	if (shapeIndex >= count)
	{
		throw std::out_of_range("Out of range in shapes collection!\n");
	}

	return data[shapeIndex]->isPointIn(x, y);
}

size_t ShapeCollection::getShapesCount() const
{
	return count;
}

void ShapeCollection::printShapes() const
{
	if (count == 0)
	{
		throw std::exception("There are no shapes in the list yet!\n");
	}

	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		std::cout << (shapeIndex + 1) << ". ";
		data[shapeIndex]->print();
	}
}

void ShapeCollection::printAreas() const
{
	if (count == 0)
	{
		throw std::exception("There are no shapes in the list yet!\n");
	}

	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		data[shapeIndex]->printArea();
	}
}

void ShapeCollection::printPerimteres() const
{
	if (count == 0)
	{
		throw std::exception("There are no shapes in the list yet!\n");
	}

	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		data[shapeIndex]->printPerimeter();
	}
}


void ShapeCollection::load(std::ifstream& sourceFile)
{
	MyString line;
	Shape* shape = nullptr;

	//Found open tag <svg>
	while (true)
	{
		line.getline(sourceFile);
		if (line == SvgCloseTag)
		{
			break;
		}

		MyString shapeType = "";
		size_t currentIndex = 0, lineSize = strlen(line.c_str());
		getShapeType(line, shapeType, lineSize, currentIndex);
		if (shapeType == tagRectangle)
		{
			shape = new Rectangle();
		}
		else if (shapeType == typeCircle)
		{
			shape = new Circle();
		}
		else if (shapeType == typeLine)
		{
			shape = new Line();
		}

		shape->loadShape(line, lineSize, currentIndex);
		addShape(shape);
	}
}

void ShapeCollection::saveToFile(const MyString& path, const Collection<MyString>& headers)
{
	std::ofstream file(path.c_str());

	saveHeaders(file, headers);

	file << SvgOpenTag << "\n";

	for (size_t shapeIndex = 0; shapeIndex < count; shapeIndex++)
	{
		data[shapeIndex]->saveShape(file);
	}

	file << SvgCloseTag;

	file.close();
}