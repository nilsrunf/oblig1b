using namespace std;
#include <iostream>
#include <math.h>
// oblig 1 b; LU-composing tridiagonal array

#include <iostream>
#include <armadillo>
#include <math.h>
#include <time.h>
using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
    FILE *f_ut;
    int  i, j, n = 10;
    double h = 1.0/(n-1);;
    clock_t start, finish, t;
    vec f(n), U(n), temp(n), x(n), b(n), temp2(n) ;
    mat A(n,n);

    f_ut = fopen("res1000.txt", "w");
    // Initialize vec u with grid length h in space (0,1)

    for(i = 0; i < n; i++)
           x(i) = i*h;
    for(i = 0; i < n; i++)
        b(i) = 100*exp(-10*x(i))*h*h;

    // Initialize tridiagonal array with 2's and -1's
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i == j)
                A(i, j) = 2;
            else if((j -1 == i) || (i-1 == j) )
                A(i, j) = -1;

    A.print();

    cout << endl  << endl;
    temp(0)= 2;
    temp2(0) = b(0);
    t = clock();

    // Do a forward substitution
    for(i = 0; i < n-1; i++){
        for(j = i; j < i+1; j++){
            A(i+1, j) = 0;
            temp(i+1) = A(i+1, j+1) -(1.0/temp(i));
            temp2(i+1) = b(i+1) -(1.0/temp2(i));
            A(i+1, j+1) = temp(i+1);
            b(i+1) = temp2(i+1);
        }

    }

    A.print();
    // U.print();
    cout << endl << endl<< endl;
    U(n-1) = b(n-1)/A(n-1, n-1);
    // Do a backward substitution
   for(i = n-1; i >0; i--)
   {
        A(i-1, i) = 0;
        U(i-1) = (b(i-1) + U(i))/A(i-1, i-1);
   }
     //   A.print();
      //  U.print();

   t = clock() -t;
   fprintf(stdout, "Execution time algo solwer: %f, N = %d\n",  (double) t/CLOCKS_PER_SEC, n, n);

   for(i = 0; i < n; i++)
       fprintf(f_ut, "%f %f\n", U(i), b(i));

    // Check time for lu-composing tridigonal array.
        start = clock();
        U = solve(A, b);
        finish = clock();
        fprintf(stdout, "Execution time LU: %f, NxN = %dx%d\n",  (start-finish)/CLOCKS_PER_SEC, n, n);

        fclose(f_ut);
          for(i = 0; i < n; i++)
              fprintf(stdout, "%f\n", log10(abs((U(i) - x(i)/U(i)))));
        //oppgave c

        return 0;
  }

