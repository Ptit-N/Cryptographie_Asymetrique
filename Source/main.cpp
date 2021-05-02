#include "lentier.h"
#include <iostream>

using namespace std;


int main()
{
	lentier a, b, c;
	a.size = 4;
	a.p = new unsigned[a.size];
	b.size = 1;
	b.p = new unsigned[b.size];
	
	a.p[3] = 83;
	b.p[0] = 47;

	c = div_eucl(a, b);

	Affiche_lentier(c);
	
	delete[] a.p;
	delete[] b.p;
	delete[] c.p;
}