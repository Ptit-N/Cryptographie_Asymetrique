#include "lentier.h"

struct lentier
{
	unsigned int p;
	unsigned int size;
	
	lentier operator%=(lentier a)
	{
		*this = div_eucl(*this, a);
		return *this;
	}
};

lentier operator%(lentier a, lentier b)
{
	a = div_eucl(a, b);
	return a;
}


lentier div_eucl(lentier a, lentier b)
{
	return a;
}
