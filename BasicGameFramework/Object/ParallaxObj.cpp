#include "ParallaxObj.h"

#include <iostream>

void ParallaxObj::Init()
{
}

void ParallaxObj::Write(std::ostream& os) const
{
	os << 2 << "\t";
	GameObject::Write(os);
}

