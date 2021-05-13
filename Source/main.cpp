#include "lentier.h"
#include <iostream>

using namespace std;


int main()
{
	unsigned int a[4] = { 0,990923518,777689008,794130497 };
	unsigned int b[2] = { 0,2 };
	lentier aa, *cc;
	aa.p = a;
	aa.size = 4;
	lentier bb;
	bb.p = b;
	bb.size = 2;

	cc = div_lentier(aa, bb);
	Affiche_lentier(cc[0]);
	Affiche_lentier(cc[1]);

	lentier res2 = mult_classique(bb, cc[1]);
	lentier res = mult_classique(bb, cc[0]);
	lentier res3 = add_lentier(res, res2);
	Affiche_lentier(res3);

	delete[] res.p;
	delete[] res2.p;
	delete[] res3.p;
	del_lentier_pointer(cc);
}