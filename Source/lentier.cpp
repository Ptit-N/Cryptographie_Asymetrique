#include "lentier.h"

/*
lentier lentier::operator%=(lentier a)
{
	delete[] this->p;
	*this = div_eucl(*this, a);
	return *this;
}
*/

lentier operator%(lentier a, lentier b)
{
	
	a = div_eucl(a, b);
	return a;
}

lentier div_eucl(const lentier a, const lentier b)
{
	lentier quotient, reste, A, B, facteur;
	unsigned int maxsize;
	unsigned char cnumber;
	long long unsigned int noverflow;

	A.size = a.size;								//Est-ce qu'on a le droit de modifier a et b ?
	A.p = new unsigned[A.size];
	B.size = b.size;
	B.p = new unsigned[B.size];
	for (unsigned i = 0; i < A.size; i++)
	{
		A.p[i] = a.p[i];
	}
	for (unsigned i = 0; i < B.size; i++)
	{
		B.p[i] = b.p[i];
	}


	quotient.size = a.size - b.size;
	quotient.p = new unsigned[quotient.size]();
	reste.size = b.size - 1;
	reste.p = new unsigned[reste.size]();

	facteur.size = quotient.size + 1;
	facteur.p = new unsigned[facteur.size]();
	facteur.p[facteur.size - 1] = 1;
	while (A >= (B*facteur))
	{
		
	}
	
	return b;
}