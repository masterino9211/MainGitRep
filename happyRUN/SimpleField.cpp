#include "SimpleField.h"

SimpleField::SimpleField()
: visited(false)
, weight(-1)
, passable(false)
{
}

bool SimpleField::operator<(SimpleField& arg)
{
	return weight < arg.weight;
}

bool SimpleField::operator<=(SimpleField& arg)
{
	return weight <= arg.weight;
}

bool SimpleField::operator==(SimpleField& arg)
{
	return weight == arg.weight;
}

bool SimpleField::operator>(SimpleField& arg)
{
	return weight > arg.weight;
}

bool SimpleField::operator>=(SimpleField& arg)
{
	return weight >= arg.weight;
}
