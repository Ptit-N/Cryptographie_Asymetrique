#include "../lentier.h"


void Affiche_lentier(const lentier a)
{
	for (auto i = a.size; i >= 1; i--)
	{
		std::cout << a.p[i - 1] << ' ';
	}
	std::cout << std::endl;
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

lentier operator+(const lentier a, const lentier b)
{
	return add_lentier(a, b);
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

lentier operator-(const lentier a, const lentier b)
{
	return sub_lentier(a, b);
}

lentier lentier::operator-=(lentier a)
{
	unsigned* temp = this->p;
	*this = *this - a;
	delete[] temp;

	return *this;
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

bool operator!=(const lentier a, const lentier b)
{
	if (cmp_lentier(a, b) == 0)
	{
		return 0;
	}
	return 1;
}

bool operator>=(const lentier a, const lentier b)
{
	if (cmp_lentier(a, b) != -1)
	{
		return 1;
	}
	return 0;
}

bool operator<=(const lentier a, const lentier b)
{
	if (cmp_lentier(a, b) != 1)
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
			c = static_cast<unsigned>(temp / (static_cast<long long unsigned>(UINT_MAX) + 1));
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

lentier lentier::operator*=(lentier a)
{
	unsigned* temp = this->p;
	*this = *this * a;
	delete[] temp;

	return *this;
}

lentier mul_mod(const lentier a, const lentier b, const lentier N)
{
	lentier aa, bb;
	aa.size = a.size;
	aa.p = new unsigned[aa.size]();
	bb.size = b.size;
	bb.p = new unsigned[bb.size]();

	for (unsigned i = 0; i < aa.size; i++)
	{
		aa.p[i] = a.p[i];
	}
	for (unsigned i = 0; i < bb.size; i++)
	{
		bb.p[i] = b.p[i];
	}

	if (aa > N)
	{
		aa %= N;
	}
	if (bb > N)
	{
		bb %= N;
	}

	lentier P = aa * bb;
	P %= N;

	delete[] aa.p;
	delete[] bb.p;

	return P;
}

lentier exp_mod(const lentier a, const lentier x, const lentier N)
{
	lentier P;
	unsigned* temp;
	P.size = a.size;
	P.p = new unsigned[P.size]();
	for (unsigned i = 0; i < P.size; i++)
	{
		P.p[i] = a.p[i];
	}

	for (char i = (char)log2(x.p[x.size - 1]) - 1; i > -1; i--)
	{
		temp = P.p;
		P = mul_mod(P, P, N);
		delete[] temp;
		if (x.p[x.size - 1] & (0x00000001 << i))
		{
			temp = P.p;
			P = mul_mod(P, a, N);
			delete[] temp;
		}
	}
	for (unsigned i = x.size - 1; i > 0; i--)
	{
		for (char j = 31; j > -1; j--)
		{
			temp = P.p;
			P = mul_mod(P, P, N);
			delete[] temp;
			if (x.p[i - 1] & (0x00000001 << j))
			{
				temp = P.p;
				P = mul_mod(P, a, N);
				delete[] temp;
			}
		}
	}

	return P;
}

lentier dec2lentier(const char* nombre_dec)
{
	struct lchar
	{
		char* p;
		long long size;
	};

	lchar nb;
	nb.size = 0;
	while (nombre_dec[nb.size] != '\0')
	{
		nb.size++;
	}
	nb.p = new char[nb.size]();

	for (auto i = 0; i < nb.size; i++)
	{
		nb.p[i] = nombre_dec[i] - 48;
	}

	lentier Sn;
	Sn.size = (unsigned)((((long double)nb.size * log(10)) / log(0x100000000)) + 1);
	Sn.p = new unsigned[Sn.size]();

	for (unsigned i = 0; i < Sn.size - 1; i++)
	{
		for (char j = 0; j < 32; j++)
		{
			if (nb.p[nb.size - 1] & 1)
			{
				Sn.p[i] += 1 << j;
				nb.p[nb.size - 1] = nb.p[nb.size - 1] - 1;
			}
			for (long long k = nb.size - 1; k >= 0; k--)
			{
				if (nb.p[k] & 1)
				{
					nb.p[k + 1] += 5;
					nb.p[k] -= 1;
				}
				nb.p[k] /= 2;
			}
		}
	}
	for(char j = 0; j < (char) nb.size; j++)
	{
		if (nb.p[nb.size - 1] & 1)
		{
			Sn.p[Sn.size - 1] += 1 << j;
			nb.p[nb.size - 1] = nb.p[nb.size - 1] - 1;
		}
		for (long long k = nb.size - 1; k >= 0; k--)
		{
			if (nb.p[k] & 1)
			{
				nb.p[k + 1] += 5;
				nb.p[k] -= 1;
			}
			nb.p[k] /= 2;
		}
	}

	delete[] nb.p;
	
	return Sn;
}

char* lentier2dec(const lentier a)
{
	const long long size = (long long)((a.size * (long double)log(0x100000000)) / (long double)log(10)) + 2;
	char* chr = new char[size]();

	lentier quotient, reste, diviseur, * pointeur;
	quotient.size = a.size;
	quotient.p = new unsigned[quotient.size];
	for (unsigned i = 0; i < quotient.size; i++)
	{
		quotient.p[i] = a.p[i];
	}

	reste.p = nullptr;

	diviseur.size = 1;
	diviseur.p = new unsigned[diviseur.size]();
	diviseur.p[0] = 1000000000;

	long long it = size - 1;

	while(!(quotient.p[0] == 0 && quotient.size == 1))
	{
		pointeur = div_lentier(quotient, diviseur);
		delete[] quotient.p;
		delete[] reste.p;
		quotient = pointeur[0];
		reste = pointeur[1];
		delete[] pointeur;
		for (long long j = it; (j > it - 9) && j >= 1; j--)
		{
			if (j > 0)
			{
				chr[j - 1] = (reste.p[0] % 10) + 48;
				reste.p[0] /= 10;
			}
		}
		it -= 9;
	}

	it = 0;

	for (long long i = 0; (i < size) && (chr[i] == '0'); i++) it++;

	char* temp = chr;
	it = size - it;
	chr = new char[it];
	chr[it - 1] = '\0';
	for (auto i = 2; i <= it; i++)
	{
		chr[it - i] = temp[size - i];
	}
	delete[] temp;

	delete[] quotient.p;
	delete[] reste.p;
	delete[] diviseur.p;

	return chr;
}