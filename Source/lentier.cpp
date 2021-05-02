#include "lentier.h"

/*
lentier lentier::operator%=(lentier a)
{
	delete[] this->p;
	*this = div_eucl(*this, a);
	return *this;
}
*/

lentier operator%(const lentier a, const lentier b)
{
	lentier Sn;
	Sn = div_eucl(a, b);
	return Sn;
}

lentier div_eucl(const lentier a, const lentier b)
{
	if(a.size == 0 || b.size == 0 || a < b)
	{
		lentier reste;
		reste.size = 0;
		reste.p = nullptr;

		return reste;
	}
	
	lentier quotient, reste, facteur;										//reste est l'équivalent de A dans l'algorithme

	//Tout ce lambda ne sert qu'à éviter un overflow lors du calcul de la condition d'une boucle et éviter de garder toutes les variables temporaires créées en mémoire
	auto lambda = [b, facteur](const unsigned i, lentier quotient, lentier reste) mutable -> void
	{
		lentier factQ, factA1, factA2;					//Chacun des termes de la condition à vérifier risque de dépasser les 64 bits de mémoires (taille max d'une variable)
		long long unsigned temp;						//facteur sera utilisé en tant que factB

		factA1.size = 3;
		factA1.p = new unsigned[factA1.size];
		factA1.p[0] = reste.p[i];

		factA2.size = 3;
		factA2.p = new unsigned[factA2.size]();
		factA2.p[2] = 1;																									//r² = 2^64 = 0b 1 00000000 00000000

		factA1 = factA1 * factA2;

		temp = (reste.p[i - 1] * static_cast<long long unsigned>(0x100000000)) + ((reste.size >= i - 1) ? reste.p[i - 2] : 0);

		factA2.p[0] = static_cast<unsigned>(temp % 0x100000000);
		factA2.p[1] = static_cast<unsigned>(temp / 0x100000000);

		temp = (b.p[b.size - 1] * static_cast<long long unsigned>(0x100000000)) + ((b.size >= 2) ? b.p[b.size - 2] : 0);

		facteur.size = 2;
		facteur.p = new unsigned[facteur.size]();
		facteur.p[0] = static_cast<unsigned>(temp % 0x100000000);
		facteur.p[1] = static_cast<unsigned>(temp / 0x100000000);

		factQ.size = 1;
		factQ.p = &quotient.p[i - b.size];

		while (factQ * facteur > factA1 * factA2)
		{
			quotient.p[i - b.size] -= 1;

			factQ.p = &quotient.p[i - b.size];
		}

		
		delete[] factA1.p;
		delete[] factA2.p;
		delete[] facteur.p;
		facteur.size = 0;
	};

	reste.size = a.size;								//Est-ce qu'on a le droit de modifier a et b ?
	reste.p = new unsigned[reste.size];
	for (unsigned i = 0; i < reste.size; i++)
	{
		reste.p[i] = a.p[i];
	}


	quotient.size = a.size - b.size + 1;
	quotient.p = new unsigned[quotient.size]();								//1.
	reste.size = b.size - 1;
	reste.p = new unsigned[reste.size]();

	facteur.size = quotient.size;

	facteur = b * facteur;
	
	while (reste >= facteur)												//2.
	{
		quotient.p[quotient.size - 1] += 1;
		reste = reste - facteur;
	}

	delete[] facteur.p;
	facteur.size = 0;
	
	for(auto i = a.size - 1 ; i > b.size ; i--)		//i >= b.size ?				3.
	{
		if(reste.p[i] == b.p[b.size - 1])												//a
		{
			quotient.p[i - b.size] = UINT_MAX;
		}
		else
		{
			quotient.p[i - b.size] = static_cast<unsigned>(((reste.p[i] * static_cast<long long unsigned>(0x100000000)) + reste.p[i - 1]) / b.p[b.size - 1]);
		}

		lambda(i, quotient, reste);														//b			c'est comme un appel de fonction, la définition de lambda est au début de div_eucl

		facteur.size = i - b.size + 1;
		facteur.p = new unsigned[facteur.size]();
		facteur.p[facteur.size - 1] = quotient.p[i - b.size];
		facteur = b * facteur;

		if(reste >= facteur)															//c
		{
			reste = reste - facteur;
		}
		else																			//d
		{
			facteur.size = i - b.size + 1;
			facteur.p = new unsigned[facteur.size]();
			facteur.p[facteur.size - 1] = 1;
			facteur = b * facteur;

			reste = reste + facteur;
			quotient.p[i - b.size] -= 1;
		}
	}

	delete[] quotient.p;													//à supprimer si on veut renvoyer le quotient
	if(facteur.size != 0)													//Si a.size == b.size, on ne passe pas dans la boucle et facteur.p est delete juste avant
	{
		delete[] facteur.p;
	{
		
	}
	
	return reste;
}