#include <vector>
#include <sstream>
#include <complex>
#include <cmath>
#include"Interval.h"

using namespace std;

typedef std::complex<long double> Complex;
typedef std::vector<Complex> cplxvector;
typedef std::vector<cplxvector> cplxmatrix;

typedef interval_arithmetic::Interval<long double> inter;
typedef std::complex<inter> Complexp;
typedef std::vector<Complexp> cplxvectorp;
typedef std::vector<cplxvectorp> cplxmatrixp;

void complexmatrix(int n, cplxmatrix& a, cplxvector& x, int& st)
{
    int ih,k,n1;
    long double d;
    Complex aa,b,c;
    bool alb;

    if (n < 1) {
        st = 1;
    } else
    {
        st = 0;
        k = 0;
        do {
            k++;
            d = 0;
            for (int i = k; i <= n; i++)
            {
                b.real(std::abs(a[i - 1][k - 1].real()) + std::abs(a[i - 1][k - 1].imag()));
                if (b.real() > d) {
                    d = b.real();
                    ih = i;
                }
            }
            if (d == 0)
                st = 2;
            else {
                aa = a[ih - 1][k - 1];
                alb = std::abs(aa.real()) < std::abs(aa.imag());
                if (alb)
                {
                    b.real(aa.real());
                    aa.real(aa.imag());
                    aa.imag(b.real());
                }
                b.real(aa.imag() / aa.real());
                aa.imag(1 / (b.real() * aa.imag() + aa.real()));
                aa.real(aa.imag() * b.real());
                if (!alb)
                {
                    b.real(aa.real());
                    aa.real(aa.imag());
                    aa.imag(b.real());
                }
                a[ih - 1][k - 1] = a[k - 1][k - 1];
                n1 = n + 1;
                for (int j = k + 1; j <= n1; j++) {
                    c = a[ih - 1][j - 1];
                    if (d < (std::abs(c.real()) + std::abs(c.imag())) * 1e-16)
                        st = 2;
                    else
                    {
                        a[ih - 1][j - 1] = a[k - 1][j - 1];
                        b.real(c.imag() * aa.imag() + c.real() * aa.real());
                        b.imag(c.imag() * aa.real() - c.real() * aa.imag());
                        a[k - 1][j - 1] = Complex(b.real(), b.imag());
                        for (int i = k + 1; i <= n; i++) {
                            c = a[i - 1][k - 1];
                            a[i - 1][j - 1].real(a[i - 1][j - 1].real() - c.real() * b.real() + c.imag() * b.imag());
                            a[i - 1][j - 1].imag(a[i - 1][j - 1].imag() - c.real() * b.imag() - c.imag() * b.real());
                        }
                    }
                }
            }
        } while ((k != n) && (st != 2));



        if (st == 0) {
            x[n - 1] = a[n - 1][n];
            for (int i = n - 1; i >= 1; i--) {
                aa = a[i-1][n];
                for (int j = i + 1; j <= n; j++) {
                    b = a[j - 1][n];
                    c = a[i - 1][j - 1];
                    aa.real(aa.real() - c.real() * b.real() + c.imag() * b.imag());
                    aa.imag(aa.imag() - c.real() * b.imag() - c.imag() * b.real());
                }
                a[i-1][n] = aa;
                x[i-1] = aa;
            }
        }
    }
}

void complexmatrixp(int n, cplxmatrixp& a, cplxvectorp& x, int& st)
{
    int ih,k,n1;
    inter d;
    Complexp aa,b,c;
    bool alb;

    if (n < 1) {
        st = 1;
    } else
    {
        st = 0;
        k = 0;
        do {
            k++;
            d = inter (0, 0);
            for (int i = k; i <= n; i++)
            {
                b.real(interval_arithmetic::IAbs(a[i - 1][k - 1].real()) + interval_arithmetic::IAbs(a[i - 1][k - 1].imag()));
                if (b.real().a > d.a && b.real().b > d.b) {
                    d = b.real();
                    ih = i;
                }
            }
            if (d.a == 0  && d.b == 0)
                st = 2;
            else {
                aa = a[ih - 1][k - 1];
                alb = (interval_arithmetic::IAbs(aa.real()).a < interval_arithmetic::IAbs(aa.imag()).a && interval_arithmetic::IAbs(aa.real()).b < interval_arithmetic::IAbs(aa.imag()).b);
                if (alb)
                {
                    b.real(aa.real());
                    aa.real(aa.imag());
                    aa.imag(b.real());
                }
                b.real(aa.imag() / aa.real());
                aa.imag(inter (1, 1) / (b.real() * aa.imag() + aa.real()));
                aa.real(aa.imag() * b.real());
                if (!alb)
                {
                    b.real(aa.real());
                    aa.real(aa.imag());
                    aa.imag(b.real());
                }
                a[ih - 1][k - 1] = a[k - 1][k - 1];
                n1 = n + 1;
                for (int j = k + 1; j <= n1; j++) {
                    c = a[ih - 1][j - 1];
                    if (d.a < (interval_arithmetic::IAbs(c.real()).a + interval_arithmetic::IAbs(c.imag()).a) * 1e-16 && d.b < (interval_arithmetic::IAbs(c.real()).b + interval_arithmetic::IAbs(c.imag()).b) * 1e-16)
                        st = 2;
                    else
                    {
                        a[ih - 1][j - 1] = a[k - 1][j - 1];
                        b.real(c.imag() * aa.imag() + c.real() * aa.real());
                        b.imag(c.imag() * aa.real() - c.real() * aa.imag());
                        a[k - 1][j - 1] = Complexp(b.real(), b.imag());
                        for (int i = k + 1; i <= n; i++) {
                            c = a[i - 1][k - 1];
                            a[i - 1][j - 1].real(a[i - 1][j - 1].real() - c.real() * b.real() + c.imag() * b.imag());
                            a[i - 1][j - 1].imag(a[i - 1][j - 1].imag() - c.real() * b.imag() - c.imag() * b.real());
                        }
                    }
                }
            }
        } while ((k != n) && (st != 2));



        if (st == 0) {
            x[n - 1] = a[n - 1][n];
            for (int i = n - 1; i >= 1; i--) {
                aa = a[i-1][n];
                for (int j = i + 1; j <= n; j++) {
                    b = a[j - 1][n];
                    c = a[i - 1][j - 1];
                    aa.real(aa.real() - c.real() * b.real() + c.imag() * b.imag());
                    aa.imag(aa.imag() - c.real() * b.imag() - c.imag() * b.real());
                }
                a[i-1][n] = aa;
                x[i-1] = aa;
            }
        }
    }
}

/*int main()
{
    int n, st;
    cout << "wprowac ilosc rownan" << endl;
    cin >> n;

    cplxmatrix a(n, cplxvector(n + 1, std::complex<long double>(0, 0)));

    cout << "Wprowadz " << n << " rownania postaci (liczba rzeczywista, liczba urojona):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            long double real, imag;
            cin >> real >> imag;
            a[i][j] = std::complex<long double>(real, imag);
        }
    }

    cplxvector x(n);

    // n - ilosc rownan
    // a - macierz (macierz)
    // x - zwraca wynik (wektor)
    // st - zwraca czy sie da wykonać
    complexmatrix(n, a, x, st);

    if (st == 0)
    {
        cout << "Wyswietlanie tablicy rekordow x:" << endl;
        int i = 1;
        for (const auto& elem : x)
        {
            cout << "x["<<i<<"].re = " << elem.real() << ", x["<<i<<"].im = " << elem.imag() << endl;
            i++;
        }
    }

    cout <<"koncowy status st: " << st << endl;
}*/

/* dane rzeczywiste
0 1 0 0 0 0 1 0
0 0 0 1 0 0 2 0
0 0 0 0 0 1 3 0

2 0 0 1 1 1 -2 11
1 1 2 0 0 1 1 3
0 1 1 1 2 0 -3 5

1 1 1 1 1 1
1 1 1 1 1 1
*/

/* dane przedziałowe
0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0
0 0 0 0 0 0 1 1 0 0 0 0 2 2 0 0
0 0 0 0 0 0 0 0 0 0 1 1 3 3 0 0

2 2 0 0 0 0 1 1 1 1 1 1 -2 -2 11 11
1 1 1 1 2 2 0 0 0 0 1 1 1 1 3 3
0 0 1 1 1 1 1 1 2 2 0 0 -3 -3 5 5

1.99 2.01 -0.01 0.02 -0.02 0.01 0.99 1.02 0.98 1.01 0.99 1.02 -2.01 -1.98 10.98 11.01
0.98 1.01 0.99 1.02 1.99 2.01 -0.02 0.01 -0.01 0.02 0.99 1.01 0.98 1.01 2.98 3.01
-0.01 0.01 0.99 1.01 0.99 1.01 0.99 1.01 1.98 2.01 -0.01 0.01 -3.01 -2.98 4.99 5.01

1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
*/
