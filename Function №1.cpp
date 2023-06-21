#include <math.h>
#include <iostream>
#include <locale>
#include <iomanip>
#include <fstream>
#include <string>

#define lya 0.3

int bulst[8][8] = { 0 };

using namespace std;

union LDC
{
	double ld;
	char uc[sizeof(ld)];
};

void print_bin(LDC ldc)
{
	unsigned char c;

	for (int i = sizeof(ldc) - 1; i >= 0; --i)
	{
		c = ldc.uc[i];
		for (int j = 0; j < 8; ++j)
		{
			if (c & (128 >> j))
			{
				cout << "1";
				bulst[i][j] = bulst[i][j] + 1;
			}
			else cout << "0";
		}
		cout << " ";
	}
	cout << endl;
}

class Gener
{
private:
	int n, k = 0;
	double *x, *y;
public:
	int getn()
	{
		cout << "Введите количество переменных: ";
		cin >> n;
		return n;
	}

	Gener() :n(getn())
	{
		x = new double[n];
		y = new double[n];
	}

	~Gener()
	{
		delete[]x;
		delete[]y;
	}

	double func1()
 	{
		x[0] = 0.0049;
		x[0] = ceil((x[0]) * 10000) / 10000;

		while(k < n)
		{
			if (x[k] >= 0 && x[k] < lya)
			{
				y[k] = x[k] / lya;
				y[k] = ceil((y[k]) * 10000) / 10000;
			}
			else
			{
				if (x[k] <= 0.5)
				{
					y[k] = (x[k] - lya) / (0.5 - lya);
					y[k] = ceil((y[k]) * 10000) / 10000;
				}
				else if (x[k] < 1)
				{
					x[k] = 1 - x[k];
					x[k] = ceil((x[k]) * 10000) / 10000;
					return func1();
				}
			}
			x[k + 1] = y[k];
			k++;
		}
	}

	void out()
	{
		LDC ldc;

		for (int i = 0; i < n; i++)
		{
			cout << "x[" << i << "] = " << x[i] << "\t";
			cout << "y[" << i << "] = " << y[i] << endl;
			ldc.ld = x[i];
			cout << "x[" << i << "] = ";
			print_bin(ldc);
			cout << endl;
		}
		for (int i = 7; i >= 0; i--)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << "bulst[" << i << "][" << j << "] = " << bulst[i][j] << endl;
			}
		}
	}
};

int main()
{
	setlocale(LC_ALL, "RUS");

	Gener B;
	B.func1();
	B.out();
	B.outmas();

	system("pause");
	return 0;
}
