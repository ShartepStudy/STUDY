#include<iostream>
#include<time.h>
#include<string>
using namespace std;

int getN(string & str)
{
   int i = str.find_first_of(':');
   if (i==string::npos) 
   {
      cout << -1 << endl;
      exit(-1);
   }
   string N(str, 0, i);
   return atoi(N.c_str());
}

int O(string & str)
{
   int N = getN(str);
   str.push_back(',');
   str.insert(str.begin()+str.find_first_of(':')+1, ',');
   
   int i;
   char t[10];
   for( i=1; i<=N ; i++ )
   {
      string digit(",,");
      digit.insert(1, _itoa(i, t, 10));
      if (str.find(digit)==string::npos) 
         break;
   }

   return i>N ? -1 : i;
}

int main() 
{
//   string * iStr = new string("BMC_TEST_INPUT_MAGIC");
//   char * input = "35:1,22,3,33,2,23,28,4,24,5,6,25,8,7,34,26,9,27,10,11,30,12,29,13,31,14,15,32,16,17,18,19,20,21";
//   string * iStr = new string(input);
   
//---------   
   srand((int)time(NULL));

   const int N=10000;
   
   int * arr = new int[N];
   for (int i=0; i<N; i++)
      arr[i] = i+1;
   for (int i=0; i<N; i++)
   {
      int j=rand()%N;
      int buf = arr[i];
      arr[i] = arr[j];
      arr[j] = buf;
   }

   char t[10];
   string *iStr = new string(_itoa(N,t,10));
   iStr->push_back(':');
   for (int i=0; i<N-2; i++)
   {
      *iStr += _itoa(arr[i],t,10);
      iStr->push_back(',');
   }
   *iStr += _itoa(arr[N-1],t,10);
   delete [] arr;
//---------

   cout << "Start work" << endl;
   int result = O(*iStr);
   cout << result << endl;
   return result;
}