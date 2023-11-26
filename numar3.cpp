#include <fstream>
#define NUMAR_MAXIM_DE_CIFRE 2000
using namespace std;
struct NumarMare
{
	int nrCifre,
	    cifre[NUMAR_MAXIM_DE_CIFRE];
};
void citesteDateleDeIntrare(
	NumarMare &,
	NumarMare &);
void determinaNumereleAB(
	NumarMare,
	NumarMare,
	NumarMare &,
	NumarMare &);
void afiseazaNumarMare(
	NumarMare,
	ostream &);
int main()
{
	NumarMare c, p10, a, b;
	citesteDateleDeIntrare(c, p10);
	determinaNumereleAB(c, p10, a, b);
	ofstream scrie("numar3.out");
	scrie << a.nrCifre << endl;
	afiseazaNumarMare(a, scrie);
	scrie << b.nrCifre << endl;
	afiseazaNumarMare(b, scrie);
	scrie.close();
	return 0;
}
int comparaNumereMari(NumarMare a, NumarMare b)
{
	if (a.nrCifre < b.nrCifre)
	{
		return -1;
	}
	if (a.nrCifre > b.nrCifre)
	{
		return 1;
	}
	int i;
	for (i = a.nrCifre - 1;
	     i >= 0 && a.cifre[i] == b.cifre[i]; i--);
	if (i < 0)
	{
		return 0;
	}
	if (a.cifre[i] < b.cifre[i])
	{
		return -1;
	}
	return 1;
}
void adunaNumereMari(
	NumarMare a,
	NumarMare b,
	NumarMare & suma)
{
	// suma = a+b
	suma.nrCifre = a.nrCifre > b.nrCifre
	               ? a.nrCifre
		       : b.nrCifre;
	int i;
	if (a.nrCifre < b.nrCifre)
	{
		for (i = a.nrCifre; i < b.nrCifre; i++)
		{
			a.cifre[i] = 0;
		}
	}
	if (b.nrCifre < a.nrCifre)
	{
		for (i = b.nrCifre; i < a.nrCifre; i++)
		{
			b.cifre[i] = 0;
		}
	}
	int transport = 0;
	for (i = 0; i < suma.nrCifre; i++)
	{
		int valoare = a.cifre[i]
		              + b.cifre[i]
			      + transport;
		suma.cifre[i] = valoare % 10;
		transport = valoare / 10;
	}
	if (transport != 0)
	{
		suma.cifre[suma.nrCifre++] = transport;
	}
}
void scadeNumereMari(
	NumarMare a,
	NumarMare b,
	NumarMare & diferenta)
{
	// diferenta = a-b
	diferenta.nrCifre = a.nrCifre;
	int i;
	for (i = b.nrCifre; i < a.nrCifre; i++)
	{
		b.cifre[i] = 0;
	}
	int transport = 0;
	for (i = 0; i < diferenta.nrCifre; i++)
	{
		int cifra = a.cifre[i]
		            - b.cifre[i]
			    - transport;
		if (cifra < 0)
		{
			cifra += 10;
			transport = 1;
		}
		else
		{
			transport = 0;
		}
		diferenta.cifre[i] = cifra;
	}
	for (i = diferenta.nrCifre-1;
	     i > 0 && diferenta.cifre[i] == 0; i--);
	diferenta.nrCifre = i+1;
}
void imparteNumereMari(
	NumarMare a,
	NumarMare b,
	NumarMare & cat)
{
	// cat = a/b
	NumarMare zero, unu;
	zero.nrCifre = 1, zero.cifre[0] = 0;
	unu.nrCifre = 1, unu.cifre[0] = 1;
	// cat = 0
	scadeNumereMari(zero, zero, cat);
	// while (a >= b)
	while (comparaNumereMari(a, b) >= 0)
	{
		// a = a-b
		scadeNumereMari(a, b, a);
		// cat++
		adunaNumereMari(cat, unu, cat);
	}
}
void celMaiMareDivizorComun(
	NumarMare a,
	NumarMare b,
	NumarMare & cmmdc)
{
	// cmmdc = cmmdc(a, b)
	int compara;
	do
	{
		compara = comparaNumereMari(a, b);
		if (compara > 0)
		{
			// a = a-b
			scadeNumereMari(a, b, a);
		}
		else
		{
			// b = b-a
			scadeNumereMari(b, a, b);
		}
	} while (compara != 0);
	cmmdc.nrCifre = a.nrCifre;
	for (int i = 0; i < a.nrCifre; i++)
	{
		cmmdc.cifre[i] = a.cifre[i];
	}
}
void afiseazaNumarMare(
	NumarMare a,
	ostream & scrie)
{
	for (int i = a.nrCifre-1; i >= 0; i--)
	{
		scrie << a.cifre[i];
	}
	scrie << endl;
}
void determinaNumereleAB(
	NumarMare c,
	NumarMare p10,
	NumarMare & a,
	NumarMare & b)
{
	NumarMare cmmdc;
	// cmmdc = cmmdc(c, p10)
	celMaiMareDivizorComun(c, p10, cmmdc);
	// a = c/cmmdc
	imparteNumereMari(c, cmmdc, a);
	// b = p10/cmmdc
	imparteNumereMari(p10, cmmdc, b);
}
void citesteDateleDeIntrare(NumarMare & c, NumarMare & p10)
{
	ifstream citeste("numar3.in");
	int nrCifreParteIntreaga,
	    nrCifreParteZecimala;
	citeste >> nrCifreParteIntreaga
	        >> nrCifreParteZecimala;
	int cifreParteIntreaga[nrCifreParteIntreaga], i;
	for (i = 0; i < nrCifreParteIntreaga; i++)
	{
		citeste >> cifreParteIntreaga[i];
	}
	int cifreParteZecimala[nrCifreParteZecimala];
	for (i = 0; i < nrCifreParteZecimala; i++)
	{
		citeste >> cifreParteZecimala[i];
	}
	// Notez PI(q) partea intreaga a numarului rational q
	// Notez PZ(q) partea zecimala a numarului rational q
	// c = numarul format prin "lipirea lui PI(q) cu PZ(q)
	// p10 = 10^(nrCifre(PZ(q)))
	for (i = nrCifreParteZecimala-1;
	     cifreParteZecimala[i] == 0 && i >= 0;
	     i--);
	c.nrCifre = 0;
	while (i >= 0)
	{
		c.cifre[c.nrCifre++] = cifreParteZecimala[i];
		i--;
	}
	p10.nrCifre = c.nrCifre + 1;
	p10.cifre[p10.nrCifre-1] = 1;
	for (i = 0; i < p10.nrCifre-1; i++)
	{
		p10.cifre[i] = 0;
	}
	int j;
	for (j = 0;
	     cifreParteIntreaga[j] == 0
	     && j < nrCifreParteIntreaga; j++);
	for (i = nrCifreParteIntreaga - 1; i >= j; i--)
	{
		c.cifre[c.nrCifre++] = cifreParteIntreaga[i];
	}
	citeste.close();
}
