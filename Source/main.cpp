#include "lentier.h"
#include <iostream>

using namespace std;


int main()
{
	//début copier/coller (dans votre main)
	unsigned int aa[3] = { 1806659176,1021366019,527857808 };
	lentier a;
	a.p = aa;
	a.size = 3;
	char* s = lentier2dec(a);
	cout << s << endl;
	//fin copier/coller
	/*
	Résultat attendu:
	9737257895872047995341991528
	*/
	//Pensez à la libération mémoire avant de faire un autre test
	delete[]s;
	/************ fin test 1 ***************/

}