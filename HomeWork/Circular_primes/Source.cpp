#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

bool isPrime( unsigned int a )
{
   unsigned long i1, i2, i3, i4, i5, i6, i7, i8, bound;
   if (a == 0 || a == 1)
      return 0;
   if (a == 2 || a == 3 || a == 5 || a == 7 || a == 11 || a == 13 || a == 17 || a == 19 || a == 23 || a == 29)
      return 1;
   if (a%2 == 0 || a%3 == 0 || a%5 == 0 || a%7 == 0 || a%11 == 0 || a%13 == 0 || a%17 == 0 || a%19 == 0 || a%23 == 0 || a%29 == 0)
      return 0;
   bound = sqrt( (double) a );
   i1 = 31; i2 = 37; i3 = 41; i4 = 43; i5 = 47; i6 = 49; i7 = 53; i8 = 59;
   while (i8 <= bound && a%i1 && a%i2 && a%i3 && a%i4 && a%i5 && a%i6 && a%i7 && a%i8)
   {
      i1 += 30; i2 += 30; i3 += 30; i4 += 30; i5 += 30; i6 += 30; i7 += 30; i8 += 30;
   }
   if (i8 <= bound ||
      i1 <= bound && a % i1 == 0 ||
      i2 <= bound && a % i2 == 0 ||
      i3 <= bound && a % i3 == 0 ||
      i4 <= bound && a % i4 == 0 ||
      i5 <= bound && a % i5 == 0 ||
      i6 <= bound && a % i6 == 0 ||
      i7 <= bound && a % i7 == 0)
      return 0;
   return 1;
}

int digitCount( unsigned int N )
{
   int count = 0;
   while ( N /= 10 )
   {
      count++;
   }
   return ++count;   
}

bool isCircularPrime( unsigned int N )
{
   int dCount = digitCount( N )-1;
   if (!dCount)
   {
      return isPrime( N );
   }
   else
   {
      int base = 1;
      for (int i = 0; i < dCount; i++)
      {
         base *= 10;
      }

      for (int i = 0; i <= dCount; i++)
      {
         if (!isPrime( N )) return false;
         N = (N % base)*10 + N/base;
      }
   }
   return true;
}

int main()
{
   char *input = "1000000";

   unsigned int n = atoi( input );

   if (n<1 || n>1000000) return 0;

   vector<bool> prime( n+1, true );
   prime[0] = prime[1] = false;
   for (int i = 2; i*i<=n; ++i)   // valid for n < 46340^2 = 2147395600
      if (prime[i])
         for (int j = i*i; j<=n; j += i)
            prime[j] = false;

   int arr[1000] = { 0 };
   cout << "enter: ";
   cin >> arr[0];

   unsigned int count = 0;
   unsigned int sz = prime.size();
   for (unsigned int i = 0; i < sz; i++)
   {
      if (prime[i] &&
         isCircularPrime( i ))
      {
         arr[count] = i;
         count++;
      }
   }

   cout << count;
   return count;
}