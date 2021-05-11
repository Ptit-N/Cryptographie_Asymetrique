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

lentier div_eucl(const lentier a, const lentier b, const bool deux)
{
	if(a.size == 0 || b.size == 0 || (b.size == 1 && b.p[0] == 0) || a < b)
	{
		lentier reste;
		reste.size = 0;
		reste.p = nullptr;

		return reste;
	}
	
	lentier quotient, reste, facteur;
	unsigned int* temp;										//reste est l'équivalent de A dans l'algorithme

	//Tout ce lambda ne sert qu'à éviter un overflow lors du calcul de la condition d'une boucle et éviter de garder toutes les variables temporaires créées en mémoire
	auto lambda = [b, facteur](const unsigned i, lentier quotient, lentier reste) mutable -> void
	{
		lentier factQ, factA1, ltemp;					//Chacun des termes de la condition à vérifier risque de dépasser les 64 bits de mémoires (taille max d'une variable)
		unsigned* temp;										//facteur sera utilisé en tant que factB
		
		factA1.size = 3;
		factA1.p = new unsigned[factA1.size]();
		factA1.p[2] = reste.p[i];									//factA1 = A[i]*r² + A[i-1] * r + A[i - 2]
		factA1.p[1] = reste.p[i - 1];
		factA1.p[0] = ((reste.size > i - 2) ? reste.p[i - 2] : 0);


		facteur.size = 2;
		facteur.p = new unsigned[facteur.size]();
		facteur.p[1] = b.p[b.size - 1];
		facteur.p[0] = (b.size >= 2) ? b.p[b.size - 2] : 0;

		factQ.size = 1;
		factQ.p = &quotient.p[i - b.size];

		ltemp = factQ * facteur;
		while (ltemp > factA1)
		{
			temp = ltemp.p;
			delete[] temp;
			quotient.p[i - b.size] -= 1;
			factQ.p = &quotient.p[i - b.size];
			ltemp = factQ * facteur;
		}

		
		delete[] factA1.p;
		delete[] facteur.p;
		delete[] ltemp.p;
		facteur.size = 0;
	};

	reste.size = a.size;
	reste.p = new unsigned[reste.size];
	for (unsigned i = 0; i < reste.size; i++)
	{
		reste.p[i] = a.p[i];
	}


	quotient.size = a.size - b.size + 1;
	quotient.p = new unsigned[quotient.size]();								//1.

 	facteur.size = a.size;
	facteur.p = new unsigned[facteur.size]();
	for(unsigned i = 1; i <= b.size; i++)
	{
		facteur.p[facteur.size - i] = b.p[b.size - i];
	}
	
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
		temp = facteur.p;
		facteur = b * facteur;
		delete[] temp;

		if(reste >= facteur)															//c
		{
			temp = reste.p;
			reste = reste - facteur;
			delete[] temp;
		}
		else																			//d
		{
			quotient.p[i - b.size] -= 1;

			lAdjust(facteur, i - b.size + 1);
			
			facteur.p[facteur.size - 1] = quotient.p[i - b.size];
			temp = facteur.p;
			facteur = b * facteur;
			delete[] temp;

			reste = reste - facteur;
		}
	}
	
	if (facteur.size != 0)													//Si a.size == b.size, on ne passe pas dans la boucle et facteur.p est delete juste avant
	{
		delete[] facteur.p;
	}

	if (deux == 1)															//Ceci est un outrage à toutes les lois de la programmation que j'ai respecté dans ma vie
	{
		lentier both, *pass;
		both.size = 2;
		both.p = new unsigned[both.size];
		pass = new lentier[2];
		pass[0].size = quotient.size;
		pass[0].p = new unsigned[pass[0].size];
		pass[1].size = reste.size;
		pass[1].p = new unsigned[pass[1].size];

		for (unsigned i = 0; i < quotient.size; i++)
		{
			pass[0].p[i] = quotient.p[i];
		}
		for (unsigned i = 0; i < reste.size; i++)
		{
			pass[1].p[i] = reste.p[i];
		}
		
		both.p[0] = (unsigned) &pass[0];
		both.p[1] = (unsigned) &pass[1];

		delete[] quotient.p;
		delete[] reste.p;
		pass = nullptr;

		return both;
	}
	
	delete[] quotient.p;													//à supprimer si on veut renvoyer le quotient
	
	return reste;
}

lentier* div_lentier(const lentier a, const lentier b)
{
	lentier c, *pass;
	c = div_eucl(a, b, 1);
	pass = (lentier*)c.p[0];
	return pass;
}

void del_lentier_pointer(lentier* a)
{
	delete[] a[0].p;
	delete[] a[1].p;
	delete[] a;
}