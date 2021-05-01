#include "Others.h"

#include <charconv>

void Affiche_lentier(const lentier a)
{
	for (auto i = a.size; i >= 1; i--)
	{
		std::cout << a.p[i - 1] << ' ';
	}
}

void lAdjust(lentier& a, const unsigned int nsize)
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
	Sn.p = new unsigned int[Sn.size]();
	
	c = 0;
	for (unsigned int i = 0; i < msize; i++)
	{
		t = static_cast<long long unsigned int>(((i < a.size) ? a.p[i] : 0)) + ((i < b.size) ? b.p[i] : 0) + c;	//teste si a.size et b.size sont suffisamment grands ou s'il faut considérer les valeurs à 0
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

lentier sub_lentier(const lentier a, const lentier b)
{
	lentier Sn;
	
	if(cmp_lentier(a, b) == -1)
	{
		Sn = { nullptr, NULL };
		return Sn;
	}

	unsigned int msize;
	char c;
	long long int t;
	
	msize = a.size;

	Sn.size = msize;
	Sn.p = new unsigned int[Sn.size]();

	c = 0;
	for (unsigned int i = 0; i < msize; i++)
	{
		t = static_cast<long long int>(a.p[i]) - ((i < b.size) ? b.p[i] : 0) + c;	//teste si a.size et b.size sont suffisamment grands ou s'il faut considérer les valeurs à 0
		Sn.p[i] = static_cast<unsigned int>(t % (static_cast<unsigned long long int>(UINT_MAX) + 1));
		if (t >= 0)
		{
			c = 0;
		}
		else
		{
			c = -1;
		}
	}
	unsigned m = 0;
	auto i = Sn.size - 1;
	while(Sn.p[i] == 0)
	{
		m++;
		i--;
	}
	if (m > 0)
	{
		if(m == Sn.size)
		{
			m = Sn.size - 1;
		}
		lAdjust(Sn, Sn.size - m);
	}

	return Sn;
}

char cmp_lentier(const lentier a, const lentier b)
{
	if(a.size > b.size)
	{
		return 1;
	}
	else if(a.size < b.size)
	{
		return -1;
	}
	else
	{
		for(auto i = static_cast<long long signed>(a.size) - 1; i >= 0; i--)
		{
			if (a.p[i] > b.p[i])
			{
				return 1;
			}
			else if (a.p[i] < b.p[i])
			{
				return -1;
			}
		}
	}
	return 0;
}

bool operator>(const lentier a, const lentier b)
{
	if(cmp_lentier(a, b) == 1)
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

bool operator==(const lentier a, const lentier b)
{
	if (cmp_lentier(a, b) == 0)
	{
		return 1;
	}
	return 0;
}

bool operator>=(const lentier a, const lentier b)
{
	char i = cmp_lentier(a, b);
	if (i == 1 || i == 0)
	{
		return 1;
	}
	return 0;
}

bool operator<=(const lentier a, const lentier b)
{
	char i = cmp_lentier(a, b);
	if (i == -1 || i == 0)
	{
		return 1;
	}
	return 0;
}

lentier mult_classique(const lentier a, const lentier b)
{
	lentier Sn;
	Sn.size = a.size + b.size;
	Sn.p = new unsigned int[Sn.size]();

	for(unsigned i = 0; i < a.size; i++)
	{
		unsigned int c = 0;
		for(unsigned j = 0; j < b.size; j++)
		{
			long long unsigned temp = Sn.p[i + j] + static_cast<long long unsigned>(a.p[i]) * b.p[j] + c;
			Sn.p[i + j] = temp % (static_cast<long long unsigned>(UINT_MAX) + 1);
			c = temp / (static_cast<long long unsigned>(UINT_MAX) + 1);
		}
		Sn.p[i + b.size] = c;
	}
	
	unsigned m = 0;
	auto i = Sn.size - 1;
	while (Sn.p[i] == 0)
	{
		m++;
		i--;
	}
	if (m > 0)
	{
		if (m == Sn.size)
		{
			m = Sn.size - 1;
		}
		lAdjust(Sn, Sn.size - m);
	}
	
	return Sn;
}

lentier operator*(lentier a, lentier b)
{
	return mult_classique(a, b);
}

lentier mul_mod(const lentier a, const lentier b, const lentier N)
{
	return a;
}


/*
lentier dec2lentier(char* nombre_dec)
{
	auto i = 0;
	while (nombre_dec[i] != '\0')
	{
		nombre_dec[i] -= '0';
		i++;
	}

	std::string s = std::to_string(0x100000000);
	char const* base = s.c_str();

	char* q = new char[strlen(nombre_dec) - strlen(base) + 1]();

	char* r[strlen(base)];

	while(sizeof(q))
	for(auto c: q)
	{
		c = 0;
	}
}
*/