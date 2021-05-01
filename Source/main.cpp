#include "lentier.h"
#include <iostream>

using namespace std;

void lentier2 (int *a)
{
	cout << *a << endl << a << endl << &a;
	*a = 10;
}


int main()
{
	lentier a, b, c;
	a.size = 2;
	a.p = new unsigned[a.size];
	b.size = 2;
	b.p = new unsigned[b.size];
	
	a.p[0] = 10;
	a.p[1] = UINT_MAX;
	b.p[0] = 3;
	b.p[1] = UINT_MAX;

	c = add_lentier(a, b);

	Affiche_lentier(c);
	
	delete[] a.p;
	delete[] b.p;
	delete[] c.p;

	int aab = 9;
	lentier2(&aab);
}