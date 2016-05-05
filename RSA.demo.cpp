// My RSA.without OPENSSL!!!
//

#include "stdafx.h"
#include <iostream>
#include<conio.h>
#include <ctime>
#include <cstdlib>



#include <iomanip>

#include <LMat.h>
using namespace std;

 
int sundaram_algo(int n)
{
	int *a = new int[n], i, j, k;
	memset(a, 0, sizeof(int) * n);
	for (i = 1; 3 * i + 1 < n; i++)
	{
		for (j = 1; (k = i + j + 2 * i*j) < n && j <= i; j++)
			a[k] = 1;
	}
	//the nearest to n prime number.
	for (i = n - 1; i >= 1; i--)
		if (a[i] == 0)
		{
			return (2 * i + 1);
			break;
		}
	delete[] a;
}
 
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}
/////////////////////////////////////////////////////////////////////
int main()
{
	cout << " Keys are being generated.It might take some seceonds" << endl << endl;
	 
	srand((unsigned)time(NULL));
	int p = rand() % 100;
	int q = rand() % 100;
	int p_simple = sundaram_algo(p);
	int q_simple = sundaram_algo(q);
	
	
	//N
	unsigned int n = p_simple*q_simple;
	
	//d number generating	
	int d, d_simple = 0;
	while (d_simple != 1)
	{
		d = rand() % 100;
		d_simple = gcd(d, ((p_simple - 1)*(q_simple - 1)));
	}
	// 
	//e number determination
	unsigned int e = 0, e_simple = 0;
	while (e_simple != 1)
	{
		e += 1;
		e_simple = (e*d) % ((p_simple - 1)*(q_simple - 1));
	}
	//generaed Keys.
	cout << '{' << setw(12) << e << ',' << setw(12) << n << '}' << " - Open key" << endl;
	cout << '{' << setw(12) << d << ',' << setw(12) << n << '}' << " - Secret key" << endl << endl;
	
	
	const int max = 25;
	char *Text = new char[25];
	cout << "Please enter the Text. Use <Enter> button when done." << endl;
	cin.get(Text, max);
	// mass for C-message
	unsigned int *CryptoText = new unsigned int[max];
	unsigned int *Tdecrypt = new unsigned int[max];
	//getting data in ASCII
	// Ci = (mj^e)%n.
	int b = 301;
	int C;
	cout << endl << setw(5) << "Text" << setw(6) << "ASCII"
		<< setw(20) << "CryptoText/Block#" << setw(14)
		<< "ASCIIdecrypt" << setw(14) << "Text decrypt" << endl
		<< "------------------------------------------------------------" << endl;

	for (int j = 0; j < max; j++)
	{
		C = 1;
		unsigned int i = 0;
		int ASCIIcode = (static_cast<int>(Text[j])) + b;
		while (i<e)
		{
			C = C*ASCIIcode;
			C = C%n;
			i++;
		}
		CryptoText[j] = C;
		b += 1;
	}
	//decryption
	//and translating it to ASCII.
	b = 301;
	int M;
	for (int j = 0; j < max; j++)
	{
		M = 1;
		unsigned int i = 0;
		while (i < d )
		{
			M = M*CryptoText[j];
			M
				= M % n ;
			i++;
		}
		M = M - b;
		Tdecrypt[j] = M;
		b += 1;
	}
	for (int j = 0; j < max; j++)
	{
		cout << setw(5) << Text[j] << setw(6) << static_cast<int>(Text[j]) << setw(20)
			<< CryptoText[j] << setw(14) << Tdecrypt[j] << setw(14) << static_cast<char>(Tdecrypt[j]) << endl;
	}
	
	delete[] Text;
	
	delete[] CryptoText;
	
	delete[] Tdecrypt;
	
	return 0;
	
	_getch();
}

int _tmain(int argc, _TCHAR* argv[])
{
	_getch();
	return 0;
}

