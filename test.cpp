#include "test.h"

MyClass::MyClass()
{

}

MyClass::~MyClass()
{

}

void MyClass::test()
{
	emit valueChanged(123);
}