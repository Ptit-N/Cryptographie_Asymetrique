#include "Others.h"

void Affiche_lentier(lentier a)
{
	
}

void lAdjust(lentier& a, unsigned int nsize)
{
	if(a.p)
	{
		a.p = (unsigned int*) realloc(a.p, nsize * sizeof(unsigned int));
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

lentier add_lentier(const lentier a, const lentier b)
{
	lentier Sn;
	unsigned int msize;
	unsigned char c;
	long long unsigned int t;
	
	if (a.size > b.size)
	{
		msize = a.size;
	}
	else
	{
		msize = b.size;
	}

	Sn.size = msize + 1;
	Sn.p = new unsigned int[Sn.size];
	
	c = 0;
	for (unsigned int i = 0; i < a.size; i++)
	{
		t = static_cast<long long unsigned int>(((a.size >= msize) ? a.p[i] : 0)) + ((b.size >= msize) ? b.p[i] : 0) + c;	//teste si a.size et b.size sont suffisamment grands ou s'il faut considérer les valeurs à 0
		Sn.p[i] = static_cast<unsigned int>(t % (static_cast<unsigned long long int>(UINT_MAX) + 1));
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
	if(Sn.p[Sn.size - 1] == 0)
	{
		lAdjust(Sn, Sn.size - 1);
	}
	
	return Sn;
}

lentier sub_entier(lentier a, lentier b)
{
	return a;
}

char cmp_lentier(lentier a, lentier b)
{
	return 1;
}

lentier mult_classique(lentier a, lentier b)
{
	return a;
}

lentier mul_mod(lentier a, lentier b, lentier N)
{
	return a;
}