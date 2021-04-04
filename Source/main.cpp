#include "lentier.h"
#include <iostream>

using namespace std;

int main()
{
	const unsigned int m(5);
	const unsigned int n(10);
	
	lentier a{ new unsigned int[m](), m };
	lentier b{ new unsigned int[n](), n };

	a %= b;

	cout << a.size;

	delete[] a.p;
	delete[] b.p;
}