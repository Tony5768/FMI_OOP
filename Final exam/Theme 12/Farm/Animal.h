#pragma once
#include <iostream>
class Animal
{
public:
	virtual void sayHello() const = 0;

	virtual Animal* clone()  const = 0;//������� ����� �� ������� �����.

	virtual ~Animal() {} //!!!
};