#include "lentier.h"

lentier lentier::operator%=(lentier a)
{
	unsigned* t;
	t = this->p;
	*this = div_eucl(*this, a);
	delete[] t;
	return *this;
}

lentier lentier::operator/=(lentier a)
{
	unsigned* temp = this->p;
	*this = *this / a;
	delete[] temp;

	return *this;
}

lentier operator/(const lentier a, const lentier b)
{
	lentier Sn, *c;

	c = div_lentier(a, b);
	Sn = c[0];

	delete[] c[1].p;
	delete[] c;
	
	return Sn;
}

lentier operator%(const lentier a, const lentier b)
{
	lentier Sn;
	Sn = div_eucl(a, b);
	return Sn;
}

lentier div_eucl(const lentier a, const lentier b, const bool deux)
{
	if(a.size == 0 || b.size == 0 || (b.size == 1 && b.p[0] == 0))					//Conditions à respecter pour le bon fonctionnement du programme
	{
		lentier reste;
		reste.size = 0;
		reste.p = nullptr;

		if (deux)
		{
			lentier both, * pass;
			both.size = 1;
			both.p = new unsigned[both.size];
			pass = new lentier[2];

			pass[0].size = 0;
			pass[0].p = nullptr;
			pass[1] = reste;

			both.p[0] = (unsigned)pass;

			return both;
		}

		return reste;
	}
	if (a < b)									//Renvoi du divisé comme reste si inférieur au diviseur
	{
		lentier reste;
		reste.size = a.size;
		reste.p = new unsigned[reste.size];
		for (unsigned i = 0; i < reste.size; i++)
		{
			reste.p[i] = a.p[i];
		}

		if (deux)
		{
			lentier both, * pass;
			both.size = 1;
			both.p = new unsigned[both.size];
			pass = new lentier[2];

			pass[0].size = 1;
			pass[0].p = new unsigned[pass[0].size]();
			pass[1] = reste;

			both.p[0] = (unsigned)pass;

			return both;
		}

		return reste;
	}

	lentier quotient, reste, B, facteur;
	unsigned int* temp;										//reste est l'équivalent de A dans l'algorithme
	
	
	unsigned char m = 0;
	unsigned int n = b.p[b.size - 1];
	while(n != 0)
	{
		m++;
		n >>= 1;
	}
	
	if(m != 32)					//Normalisation des termes de l'opération
	{
		if(static_cast<unsigned>(log2(a.p[a.size - 1])) > m)
		{
			reste.size = a.size + 1;
		}
		else
		{
			reste.size = a.size;
		}
		reste.p = new unsigned[reste.size];

		if(reste.size == a.size + 1)
		{
			reste.p[reste.size - 1] = a.p[a.size - 1] >> m;
		}
		if(a.size > 1)
		{
			for (unsigned i = a.size - 1; i > 0; i--)
			{
				reste.p[i] = (a.p[i] << (32 - m)) | (a.p[i - 1] >> m);
			}
		}
		reste.p[0] = a.p[0] << (32 - m);

		B.size = b.size;
		B.p = new unsigned[B.size];
		for (unsigned i = 1; i < B.size; i++)
		{
			B.p[i] = (b.p[i] << (32 - m)) | (b.p[i - 1] >> m);
		}
		B.p[0] = b.p[0] << (32 - m);
	}
	else
	{
		reste.size = a.size;
		reste.p = new unsigned[reste.size];
		for (unsigned i = 0; i < reste.size; i++)
		{
			reste.p[i] = a.p[i];
		}
		B = b;
	}
	
	quotient.size = reste.size - B.size;
	quotient.p = new unsigned[quotient.size]();								//1.
	
	if(B.size == 1)																//Optimisation si le diviseur n'a qu'un seul chiffre
	{
		if(reste.p[reste.size - 1] >= B.p[0])
		{
			quotient.p[quotient.size - 1] += reste.p[reste.size - 1] / B.p[0];
			reste.p[reste.size - 1] %= B.p[0];
		}

		for (auto i = reste.size - 1; i >= 1; i--)
		{
			quotient.p[i - 1] = static_cast<unsigned>((reste.p[i] * static_cast<long long unsigned>(0x100000000) + reste.p[i - 1]) / B.p[0]);
			reste.p[i] -= static_cast<unsigned>((static_cast<unsigned long long>(quotient.p[i - 1]) * B.p[0]) >> 32);
			reste.p[i - 1] -= static_cast<unsigned>((static_cast<unsigned long long>(quotient.p[i - 1]) * B.p[0]) & 0xFFFFFFFF);
		}

		lAdjust(reste, 1);
	}
	else
	{
		facteur.size = reste.size;
		facteur.p = new unsigned[facteur.size]();
		for (unsigned i = 1; i <= B.size; i++)
		{
			facteur.p[facteur.size - i] = B.p[B.size - i];
		}

		while (reste >= facteur)												//2.
		{
			quotient.p[quotient.size - 1] += 1;
			temp = reste.p;
			reste = reste - facteur;
			delete[] temp;
		}

		delete[] facteur.p;
		facteur.size = 0;

		for (auto i = reste.size - 1; i >= B.size; i--)						//3.
		{
			if (reste.p[i] == B.p[B.size - 1])												//a
			{
				quotient.p[i - B.size] = UINT_MAX;
			}
			else
			{
				quotient.p[i - B.size] = static_cast<unsigned>((reste.p[i] * static_cast<long long unsigned>(0x100000000) + reste.p[i - 1]) / B.p[B.size - 1]);
			}

			//Toute cette lambda ne sert qu'à éviter un overflow lors du calcul de la condition d'une boucle et éviter de garder toutes les variables temporaires créées en mémoire
			[&B, &quotient, &reste, i]() mutable -> void
			{
				lentier factQ, factA1, ltemp, facteur;					//Chacun des termes de la condition à vérifier risque de dépasser les 64 bits de mémoires (taille max d'une variable)
				unsigned* temp;										//facteur sera utilisé en tant que factB

				factA1.size = 3;
				factA1.p = new unsigned[factA1.size]();
				factA1.p[2] = reste.p[i];									//factA1 = A[i]*r² + A[i-1] * r + A[i - 2]
				factA1.p[1] = reste.p[i - 1];
				factA1.p[0] = reste.p[i - 2];


				facteur.size = 2;
				facteur.p = new unsigned[facteur.size]();
				facteur.p[1] = B.p[B.size - 1];
				facteur.p[0] = B.p[B.size - 2];

				factQ.size = 1;
				factQ.p = &quotient.p[i - B.size];

				ltemp = factQ * facteur;
				while (ltemp > factA1)
				{

					quotient.p[i - B.size] -= 1;
					factQ.p = &quotient.p[i - B.size];
					temp = ltemp.p;
					ltemp = factQ * facteur;
					delete[] temp;
				}


				delete[] factA1.p;
				delete[] facteur.p;
				delete[] ltemp.p;
			}();													//b			c'est comme un appel de fonction, la définition de lambda est au début de div_eucl

			facteur.size = i - B.size + 1;
			facteur.p = new unsigned[facteur.size]();
			facteur.p[facteur.size - 1] = quotient.p[i - B.size];
			temp = facteur.p;
			facteur = B * facteur;
			delete[] temp;

			if (reste >= facteur)															//c
			{
				temp = reste.p;
				reste = reste - facteur;
				delete[] temp;
				delete[] facteur.p;
			}
			else																			//d
			{
				quotient.p[i - B.size] -= 1;

				lAdjust(facteur, i - B.size + 1);

				facteur.p[facteur.size - 1] = quotient.p[i - B.size];
				temp = facteur.p;
				facteur = B * facteur;
				delete[] temp;

				reste = reste - facteur;
				delete[] facteur.p;
			}
		}
	}
	

	if(B.p != b.p) delete[] B.p;

	if (m != 32)					//Inversion de la normalisation
	{
		facteur.size = reste.size;
		facteur.p = new unsigned[facteur.size]();
		if(reste.size > 1)
		{
			for (unsigned i = 0; i < facteur.size - 1; i++)
			{
				facteur.p[i] = (reste.p[i + 1] << m) | (reste.p[i] >> (32 - m));
			}
		}
		facteur.p[facteur.size - 1] = reste.p[reste.size - 1] >> (32 - m);
		if (facteur.p[facteur.size - 1] == 0 && facteur.size > 1)
		{
			lAdjust(facteur, facteur.size - 1);
		}
		delete[] reste.p;
		reste = facteur;
	}
	
	if (deux == 1)
	{
		lentier both, *pass;
		both.size = 1;
		both.p = new unsigned[both.size];
		pass = new lentier[2];

		pass[0] = quotient;
		pass[1] = reste;
		
		both.p[0] = (unsigned) pass;

		return both;
	}
	
	delete[] quotient.p;
	
	return reste;
}

lentier* div_lentier(const lentier a, const lentier b)
{
	lentier c, *pass;
	c = div_eucl(a, b, 1);
	pass = (lentier*)c.p[0];
	return pass;
}