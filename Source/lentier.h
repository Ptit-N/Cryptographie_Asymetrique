#pragma once

struct lentier
{
	unsigned int* p;
	unsigned int size;
	
	
	lentier operator%=(lentier a);
};

lentier operator%(lentier a, lentier b);

lentier div_eucl(lentier a, lentier b);