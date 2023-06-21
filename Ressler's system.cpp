#include <math.h>
#include <iostream>
#include <locale>
#include <iomanip>
#include <fstream>
#include <string>

#define h 0.05
#define a 0.2
#define b 0.2
#define c 2.6

using namespace std;

int bulst[8][8] = { 0 };

union LDC
{
	double ld;
	char uc[sizeof(ld)];
};

void print_bin(LDC ldc)
{
	unsigned char cc;

	for (int i = sizeof(ldc) - 1; i >= 0; --i)
	{
		cc = ldc.uc[i];
		for (int j = 0; j < 8; ++j)
		{
			if (cc & (128 >> j))
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
	int n;
	double *x, *y, *z;
	int st[201] = { 0 };
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
		z = new double[n];
	}

	~Gener()
	{
		delete[]x;
		delete[]y;
		delete[]z;
	}

	double Fx(double y, double z)
	{
		return -y - z;
	}

	double Fy(double x, double y)
	{
		return x + a * y;
	}

	double Fz(double z, double x)
	{
		return b + z * (x - c);
	}

	void ressler()
	{
		double k[3][4];
		x[0] = 0;
		y[0] = 0;
		z[0] = 0;

		for (int i = 0; i < n; i++)
		{
			
			k[0][0] = h * Fx((y[i]), (z[i]));
			k[1][0] = h * Fy((x[i]), (y[i]));
			k[2][0] = h * Fz((z[i]), (x[i]));
			k[0][1] = h * Fx((y[i] + (h * k[0][0]) / 2.0), (z[i] + (h * k[1][0]) / 2.0));
			k[1][1] = h * Fy((x[i] + (h * k[0][0]) / 2.0), (y[i] + (h * k[1][0]) / 2.0));
			k[2][1] = h * Fz((z[i] + (h * k[1][0]) / 2.0), (x[i] + (h * k[0][0]) / 2.0));
			k[0][2] = h * Fx((y[i] + (h * k[0][1]) / 2.0), (z[i] + (h * k[1][1]) / 2.0));
			k[1][2] = h * Fy((x[i] + (h * k[0][1]) / 2.0), (y[i] + (h * k[1][1]) / 2.0));
			k[2][2] = h * Fz((z[i] + (h * k[1][1]) / 2.0), (x[i] + (h * k[0][0]) / 2.0));
			k[0][3] = h * Fx((y[i] + (h * k[0][2])), (z[i] + h * k[1][2]));
			k[1][3] = h * Fy((x[i] + (h * k[0][2])), (y[i] + h * k[1][2]));
			k[2][3] = h * Fz((z[i] + (h * k[1][2])), (x[i] + h * k[2][2]));
			// X
			x[i + 1] = x[i] + (k[0][0] + 2.0 * k[0][1] + 2.0 * k[0][2] + k[0][3]) / 6.0;
			cout << "x[" << i << "]" << x[i] << endl;
			// Y
			y[i + 1] = y[i] + (k[1][0] + 2.0 * k[1][1] + 2.0 * k[1][2] + k[1][3]) / 6.0;
			cout << "y[" << i << "]" << y[i] << endl;
			// Z
			z[i + 1] = z[i] + (k[2][0] + 2.0 * k[2][1] + 2.0 * k[2][2] + k[2][3]) / 6.0;
			cout << "z[" << i << "]" << z[i] << endl;
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
	}
};

int main()
{
	setlocale(LC_ALL, "RUS");

	Gener B;
	B.ressler();
	B.out();
	B.outmas();

	system("pause");
	return 0;
}
