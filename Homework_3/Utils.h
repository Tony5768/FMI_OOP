#pragma once
#include "MyString.h"
#include "ShapeCollection.h"
#include "Collection.hpp"

bool isPrefix(const MyString& text, const MyString& prefix);

void loadFigures(const MyString& path, ShapeCollection& shapes, Collection<MyString>& headers);

void getShapeType(const MyString& line, MyString& type, size_t& lineSize, size_t& currentIndex);

int getStartindex(const MyString& line, size_t& lineSize);

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument, char startSeparator, char endSeparator);

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument, char startSeparator, char endSeparator);

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument);

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument);

void getTranslateArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void readUnnecessaryLines(std::ifstream& sourceFile, Collection<MyString>& headers);

MyString parseDoubleToString(double value);

MyString parseIntToString(int value);

char parseIntToChar(size_t value);

size_t getNumSize(int number);

void swap(char& el1, char& el2);
