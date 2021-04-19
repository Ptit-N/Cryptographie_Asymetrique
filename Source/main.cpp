#include "lentier.h"
#include <iostream>

using namespace std;

int main()
{
	lentier a, b;

	a.size = 3;
	a.p = new unsigned int[a.size];

	b.size = 2;
	b.p = new unsigned int[b.size];

	a.p[0] = 1;
	b.p[0] = 1;
	a.p[1] = UINT_MAX;
	b.p[1] = UINT_MAX;
	a.p[2] = 3;
	
	lentier c = add_lentier(a, b);

	cout << "size of C: " << c.size << endl;

	for (auto i = c.size; i >= 1; i--)
	{
		cout << c.p[i - 1] << ' ';
	}
	
	delete[] a.p;
	delete[] b.p;
	delete[] c.p;
}