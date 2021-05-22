#include "lentier.h"
#include <iostream>

using namespace std;


int main()
{
	/* 1e jeu de données */
//début copier/coller (dans votre main)
	const char* s = "201374501817115722381693399046953154910981538702977772991559837490819494829508978805309598983915928634998";
	lentier a;
	a = dec2lentier(s);
	Affiche_lentier(a);//fin copier/coller
	/*
	Résultat attendu:
	{2045593206,279951739,222109666,889033077,1057640747,1016240163,1712087700,1631452143,173372631,1544088762,94277024};
	*/
	//Pensez à la libération mémoire avant de faire un autre test
	delete[]a.p;
	/************ fin test 1 ***************/
}