// oblig 1 b
using namespace std;
#include <math.h>
#include <stdio.h>
#include <armadillo>
#include <math.h>
#include <fstream>
#include <time.h>
#include <iomanip>
using namespace arma;

fstream logfil;

int main(int argc, char** argv)
  {
    int  i, j, n = 10000;
    double h = 1.0/(n+1), e = 0, max = 0.0;
    clock_t t;
    vec U(n+1), x(n+1), temp(n), b_f(n), U_analytic(n);
    mat A(n,n);
    FILE *utfil;

    utfil = fopen("res10000.txt", "w");
    logfil.open("log.txt");

    // Initier x-verdiene med grid length h fra verdiene (0,1)
    for(i = 0; i < n; i++)
           x(i) = i*h;

    // initier f(x) = b_f(x) med analytisk løsning
    for(i = 0; i < n; i++)
           b_f(i) = 100*exp(-10*x(i))*h*h;

    // Initier tridiagonal matrise med 2's og -1's
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i == j)
                 A(i, j) = 2;
            else if((j -1 == i) || (i-1 == j))
                 A(i, j) = -1;
            else A(i, j)= 0;

    // A.print();

    // Gjør en forward substitution
    t = clock();
    temp(0)= 2;
    for(i = 1; i < n; i++)
    {
          temp(i) = A(i, i) -(1.0/temp(i-1));
          A(i, i) = temp(i);
          b_f(i) = b_f(i) + b_f(i-1)/temp(i-1);
    }

    // Gjør en backward substitution
    U(0) = 0;
    U(n) = 0;
    U(n-1) = b_f(n-1)/A(n-1, n-1);
    for(i = n-1; i > 1; i--)
        U(i-1) = (b_f(i-1) +(U(i)))/A(i-1, i-1);

    t = clock() -t;

    fprintf(stdout, "Execution time solver: %f, N = %d\n",  (float) t/CLOCKS_PER_SEC, n);

    // Skriv verdiene til fil så de kan brukes i matlab-plot
    for(i = 0; i < n; i++)
        fprintf(utfil, "%f\n", U(i));


    //oppgave c

    for(i = 1; i < n; i++){
        U_analytic(i) = 1 - (1 -exp(-10))*x(i) - exp(-10*x(i));
        e = log10(abs(U(i)-U_analytic(i))/U_analytic(i));
                  if(e > max)
                  max = e;
    }

    logfil << setiosflags(ios::showpoint | ios:: uppercase);
    logfil << setw(10) << setprecision(8) << "N= " << n << "h = " << h << "Error " << max << endl;

    cout << "N= " << n << "h = " << h << "Error " << max << endl;

    fclose(utfil);
    logfil.close();

    // Check time for lu-composing tridigonal array.
        t = clock();
        U = solve(A, U_analytic);
        t = clock() -t;
        fprintf(stdout, "Execution time: %f, N = %d\n",  (float) t/CLOCKS_PER_SEC, n);
         return 0;
  }
