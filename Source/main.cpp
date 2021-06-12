#include "lentier.h"
#include <iostream>

using namespace std;


int main()
{
	/* 19e jeu de données */
//début copier/coller (dans votre main)
	unsigned int aa[5] = { 2115348176,1777673873,70745332,1499975921,236491098 };
	lentier a;
	a.p = aa;
		a.size = 5;
	char* s = lentier2dec(a);
	cout << s << endl;
	//fin copier/coller
	/*
	Résultat attendu:
	80473750702011952452662690157637500818194540240
	*/
	//Pensez à la libération mémoire avant de faire un autre test
	delete[]s;
	/************ fin test 19 ***************/
}