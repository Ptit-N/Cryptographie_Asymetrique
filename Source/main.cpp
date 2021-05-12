#include "lentier.h"
#include <iostream>

using namespace std;


int main()
{
	/* 20e jeu de données */
//début copier/coller (dans votre main)
	unsigned int a[18] = { 990923518,777689008,794130497,823054623,573811396,1304616115,1979484709,610308529,1206887478,1467769018,964722234,1185027026,1652101389,88634314,1084140140,1041928878,570235176,1665802409 };
	unsigned int b[9] = { 424928658,443650361,448833396,1888566536,527533718,877070267,1027476331,579231248,3879654164 };
	lentier aa;
	aa.p = a;
	aa.size = 18;
	lentier bb;
	bb.p = b;
	bb.size = 9;
	lentier res;
	res = div_eucl(aa, bb);
	Affiche_lentier(res);
	//fin copier/coller
	/*
	Résultat attendu:
	{1040781220,836310477,1191344811,1645576801,669642415,4117350591,1559026176,2785448488,3862855035};
	*/
	//Pensez à la libération mémoire avant de faire un autre test
	delete[]res.p;
	/************ fin test 20 ***************/
}