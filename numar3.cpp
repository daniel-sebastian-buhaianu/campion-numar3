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
	NumarMare &,
	NumarMare &);
void afiseazaNumarMare(
	NumarMare,
	ostream &);
int main()
{
	NumarMare a, b;
	citesteDateleDeIntrare(a, b);
	determinaNumereleAB(a, b);
	ofstream scrie("numar3.out");
	scrie << a.nrCifre << endl;
	afiseazaNumarMare(a, scrie);
	scrie << b.nrCifre << endl;
	afiseazaNumarMare(b, scrie);
	scrie.close();
	return 0;
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
void imparteNumarMareLaNumarMic(
	NumarMare a,
	int numarMic,
	NumarMare & cat)
{
	// cat = a/numarMic
	if ((a.nrCifre == 1 && a.cifre[0] == 0)
		|| numarMic == 0)
	{
		cat.cifre[0] = 0;
		cat.nrCifre = 1;
		return;
	}
	int rest = 0;
	for (int i = a.nrCifre-1; i >= 0; i--)
	{
		int valoare = rest*10 + a.cifre[i];
		cat.cifre[i] = valoare/numarMic;
		rest = valoare%numarMic;
	}
	for (cat.nrCifre = a.nrCifre;
	     cat.nrCifre > 1 && cat.cifre[cat.nrCifre-1] == 0;
	     cat.nrCifre--);
}
bool esteDiferitDeZero(NumarMare a)
{
	return !(a.nrCifre == 1 && a.cifre[0] == 0); 
}
bool ultimaCifraDivizibilaCu(int x, NumarMare a)
{
	return a.cifre[0] % x == 0;
}
void determinaNumereleAB(
	NumarMare & a,
	NumarMare & b)
{
	while (esteDiferitDeZero(a)
	       && esteDiferitDeZero(b)
	       && ultimaCifraDivizibilaCu(2, a)
	       && ultimaCifraDivizibilaCu(2, b))
	{
		imparteNumarMareLaNumarMic(a, 2, a);
		imparteNumarMareLaNumarMic(b, 2, b);
	}
	while (esteDiferitDeZero(a)
	       && esteDiferitDeZero(b)
	       && ultimaCifraDivizibilaCu(5, a)
	       && ultimaCifraDivizibilaCu(5, b))
	{
		imparteNumarMareLaNumarMic(a, 5, a);
		imparteNumarMareLaNumarMic(b, 5, b);
	}
}
void citesteDateleDeIntrare(NumarMare & a, NumarMare & b)
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
	// a = numarul format prin "lipirea lui PI(q) cu PZ(q)
	// b = 10^(nrCifre(PZ(q)))
	for (i = nrCifreParteZecimala-1;
	     cifreParteZecimala[i] == 0 && i >= 0;
	     i--);
	a.nrCifre = 0;
	while (i >= 0)
	{
		a.cifre[a.nrCifre++] = cifreParteZecimala[i];
		i--;
	}
	b.nrCifre = a.nrCifre + 1;
	b.cifre[b.nrCifre-1] = 1;
	for (i = 0; i < b.nrCifre-1; i++)
	{
		b.cifre[i] = 0;
	}
	int j;
	for (j = 0;
	     cifreParteIntreaga[j] == 0
	     && j < nrCifreParteIntreaga; j++);
	for (i = nrCifreParteIntreaga - 1; i >= j; i--)
	{
		a.cifre[a.nrCifre++] = cifreParteIntreaga[i];
	}
	citeste.close();
}
