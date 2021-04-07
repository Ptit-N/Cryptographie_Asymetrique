#include "Others.h"

void Affiche_lentier(lentier a)
{
	
}

void lAdjust(lentier& a, unsigned int nsize)
{
	if(a.p)
	{
		realloc(a.p, nsize);

		if(nsize > a.size)
		{
			for(auto i = a.size; i < nsize; i++)
			{
				a.p[i] = 0;
			}
		}
		a.size = nsize;
	}
}

lentier add_lentier(lentier a, lentier b)
{
	lentier Sn;
	char c;
	long long unsigned int t;
	
	if (a.size > b.size)
	{
		lAdjust(b, a.size);
	}
	else if (a.size < b.size)
	{
		lAdjust(a, b.size);
	}

	Sn.size = a.size + 1;
	Sn.p = new unsigned int[Sn.size];
	
	c = 0;
	for (unsigned int i = 0; i < a.size; i++)
	{
		t = a.p[i] + b.p[i] + c;
		Sn.p[i] = static_cast<unsigned>(t % UINT_MAX);

		if (t < UINT_MAX)
		{
			c = 0;
		}
		else
		{
			c = 1;
		}
	}
	Sn.p[Sn.size - 1] = c;

	return Sn;
}

lentier sub_entier(lentier a, lentier b)
{
	
}

char cmp_lentier(lentier a, lentier b)
{
	
}

lentier mult_classique(lentier a, lentier b)
{
	
}

lentier mul_mod(lentier a, lentier b, lentier N)
{
	
}