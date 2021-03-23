#include "lentier.h"
#include <iostream>

using namespace std;

int main()
{
	lentier a;
	lentier b;

	a.p = 3;
	b.p = 4;
	a.size = 5;
	a.size = 6;
	
	a = b.lentier::operator%(b);
}