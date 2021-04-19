#include "lentier.h"
#include <iostream>

using namespace std;

int main()
{
	lentier a, b;

	a.size = 2;
	a.p = new unsigned int[a.size];

	b.size = 3;
	b.p = new unsigned int[b.size];

	a.p[0] = 1;
	b.p[0] = 1;
	a.p[1] = UINT_MAX;
	b.p[1] = UINT_MAX;
	b.p[2] = 3;
	
	lentier c = sub_lentier(a, b);

	cout << "size of C: " << c.size << endl;

	Affiche_lentier(c);
	
	delete[] a.p;
	delete[] b.p;
	delete[] c.p;
}