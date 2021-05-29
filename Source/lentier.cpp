#include "lentier.h"

lentier div_eucl(const lentier a, const lentier b, const bool deux)
{
	if(a.size == 0 || b.size == 0 || (b.size == 1 && b.p[0] == 0))					//Situations compromettant le bon fonctionnement du programme
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
			both.p[1] = (unsigned)((unsigned long long)(pass) / 0x100000000);

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
			both.p[1] = (unsigned)((unsigned long long)(pass) / 0x100000000);

			return both;
		}

		return reste;
	}

	lentier quotient, reste, B, facteur;					//reste est l'équivalent de A dans l'algorithme
	
	
	const unsigned char m = static_cast<unsigned char>(log2(b.p[b.size - 1]) + 1);
	
	if(m != 32)					//Normalisation des termes de l'opération
	{
		if(static_cast<unsigned>(log2(a.p[a.size - 1])) > m)	//overflow
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
			reste.p[i - 1] -= static_cast<unsigned>(quotient.p[i - 1] * B.p[0]);
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
			quotient.p[quotient.size - 1]++;
			reste -= facteur;
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
				quotient.p[i - B.size] = static_cast<unsigned>((reste.p[i] * 0x100000000 + reste.p[i - 1]) / B.p[B.size - 1]);
			}

			//b
			//Toute cette partie ne sert qu'à éviter un overflow lors du calcul de la condition d'une boucle
			{
				lentier factQ, factA1, ltemp;

				factA1.size = 3;
				factA1.p = &reste.p[i - 2];									//factA1 = A[i]*r² + A[i-1] * r + A[i - 2]

				facteur.size = 2;
				facteur.p = &B.p[B.size - 2];								//facteur = B[t-1] * r + B[t - 2]

				factQ.size = 1;
				factQ.p = &quotient.p[i - B.size];

				ltemp = factQ * facteur;
				while (ltemp > factA1)
				{
					factQ.p[0]--;
					ltemp -= facteur;
				}

				delete[] ltemp.p;
			}

			facteur.size = i - B.size + 1;
			facteur.p = new unsigned[facteur.size]();
			facteur.p[facteur.size - 1] = quotient.p[i - B.size];
			facteur *= B;

			if (reste >= facteur)															//c
			{
				reste -= facteur;
				delete[] facteur.p;
			}
			else																			//d
			{
				quotient.p[i - B.size]--;
				
				lAdjust(facteur, i - B.size + 1);

				facteur.p[facteur.size - 1] = quotient.p[i - B.size];
				facteur *= B;

				reste -= facteur;
				delete[] facteur.p;
			}
		}
	}

	if (m != 32)					//Inversion de la normalisation
	{
		if(reste.size > 1)
		{
			for (unsigned i = 0; i < reste.size - 1; i++)
			{
				reste.p[i] = (reste.p[i + 1] << m) | (reste.p[i] >> (32 - m));
			}
		}
		reste.p[facteur.size - 1] = reste.p[reste.size - 1] >> (32 - m);

		if (reste.p[reste.size - 1] == 0 && reste.size > 1)
		{
			lAdjust(reste, reste.size - 1);
		}
		
		delete[] B.p;
	}
	
	if (deux == 1)
	{
		lentier both, *pass;
		both.size = 2;
		both.p = new unsigned[both.size];
		pass = new lentier[2];

		pass[0] = quotient;
		pass[1] = reste;
		
		both.p[0] = (unsigned) pass;
		both.p[1] = (unsigned)((unsigned long long)(pass) / 0x100000000);

		return both;
	}
	
	delete[] quotient.p;
	
	return reste;
}

lentier* div_lentier(const lentier a, const lentier b)
{
	lentier both, *pass;
	both = div_eucl(a, b, 1);
	pass = (lentier*)((unsigned long long)both.p[1] * 0x100000000 + both.p[0]);
	return pass;
}

lentier lentier::operator-=(lentier a)
{
	unsigned* temp = this->p;
	*this = sub_lentier(*this, a);
	delete[] temp;

	return *this;
}

lentier operator*(lentier a, lentier b)
{
	return mult_classique(a, b);
}

lentier lentier::operator*=(lentier a)
{
	unsigned* temp = this->p;
	*this = *this * a;
	delete[] temp;

	return *this;
}

bool operator>(const lentier a, const lentier b)
{
	if (cmp_lentier(a, b) == 1)
	{
		return 1;
	}
	return 0;
}

bool operator<(const lentier a, const lentier b)
{
	if (cmp_lentier(a, b) == -1)
	{
		return 1;
	}
	return 0;
}

bool operator>=(const lentier a, const lentier b)
{
	if (cmp_lentier(a, b) != -1)
	{
		return 1;
	}
	return 0;
}