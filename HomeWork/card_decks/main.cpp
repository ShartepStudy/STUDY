#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string>
#include<vector>
using namespace std;

int getN(char c)
{
   switch (c)
   {
   case '2': return 0;
   case '3': return 1;
   case '4': return 2;
   case '5': return 3;
   case '6': return 4;
   case '7': return 5;
   case '8': return 6;
   case '9': return 7;
   case 'T': return 8;
   case 'J': return 9;
   case 'Q': return 10;
   case 'K': return 11;
   case 'A': return 12;
   default:
      printf( "-1" );
      exit( -1 );
      break;
   }
}

int O(string & str)
{
   str.push_back( ',' );
   vector<unsigned int> vS( 13, 0 );
   vector<unsigned int> vC( 13, 0 );
   vector<unsigned int> vH( 13, 0 );
   vector<unsigned int> vD( 13, 0 );

   vector<unsigned int> * deck[4] = {&vS, &vC, &vH, &vD};

   int b = 0;
   int e = str.find_first_of( ',' );
   string card = str.substr( b, e-b );

   do
   {
      switch (card[1])
      {
      case 'S':
         vS[getN( card[0] )]++;
         break;
      case 'C':
         vC[getN( card[0] )]++;
         break;
      case 'H':
         vH[getN( card[0] )]++;
         break;
      case 'D':
         vD[getN( card[0] )]++;
         break;
      default:
         printf( "-1" );
         exit( -1 );
         break;
      }
      b = e+1;
      e = str.find_first_of( ',', b );
      card = str.substr( b, e-b );
   }
   while (e != -1);

   bool flag = true;
   int k = -1;
   do
   {
      k++;
      for (int j = 0; j < 4; j++)
         for (int i = 0; i < 13; i++)
            if ( (*deck[j])[i]>0 ) 
               (*deck[j])[i]--;
            else flag = false;
   }
   while (flag);

   return k;
}

int main() 
{
//   string & iStr = new string("BMC_TEST_INPUT_MAGIC");
   char * input = "JD,5D,6D,2S,3S,7S,9S,AS,5C,2S,JS,TC,JC,2H,9C,QH,2D,7H,2H,QS,KD,3D,4C,QS,8S,8H,5H,7D,9D,QH,5C,TD,KS,AH,3C,AS,4C,6C,TH,KC,AH,AC,2C,JC,4S,QD,4C,9S,KD,8C,TC,TS,AC,TC,JH,9D,3D,TH,7H,7D,KH,QC,2D,KH,AH,JH,TC,JS,6H,3C,TS,TH,TC,TC,4D,KC,QD,9D,3D,4C,TD,7H,5S,8S,8C,6S,TD,KC,5S,7S,6S,4H,4H,3D,QC,6S,AC,AD,3H,TC,5H,6C,2H,6S,6S,6H,4C,7H,8D,4D,TH,JC,AH,2H,7C,AD,2H,6D,KD,6C,7D,5D,QS,QD,TS,5S,2H,5H,3H,3S,3D,2H,3H,JD,3C,7C,4S,AC,KS,9C,8D,2C,KH,2D,6C,TC,JS,AD,KC,5C,9H,AC,9H,QS,8H,2H,7D,TS";
   string * iStr = new string(input);
   
////---------   
//   srand((int)time(NULL));
//
//   const int N=1000000;
//   string * iStr = new string;
//   char r, s;
//
//   for (int i=0; i<N; i++)
//   {
//      switch (rand()%4)
//      {
//      case 0: s = 'S'; break;
//      case 1: s = 'C'; break;
//      case 2: s = 'H'; break;
//      case 3: s = 'D'; break;
//      }
//      
//      switch (rand()%13)
//      {
//      case 0: r = '2'; break;
//      case 1: r = '3'; break;
//      case 2: r = '4'; break;
//      case 3: r = '5'; break;
//      case 4: r = '6'; break;
//      case 5: r = '7'; break;
//      case 6: r = '8'; break;
//      case 7: r = '9'; break;
//      case 8: r = 'T'; break;
//      case 9: r = 'J'; break;
//      case 10: r = 'Q'; break;
//      case 11: r = 'K'; break;
//      case 12: r = 'A'; break;
//      }
//
//      iStr->push_back( r );
//      iStr->push_back( s );
//      iStr->push_back( ',' );
//   }
//   
//   iStr->pop_back();
//   cout << "Start work" << endl;
////---------

   int result = O( *iStr );
   delete iStr;
   printf("%d\n", result);
   return result;
}





/*
In a casino all the playing cards got mixed up, and a lot of them got lost.You have to collect as many full decks as possible.A deck contains 52 cards, one for each rank and suit.

You get N mixed up French playing cards as your input.

You have to output the number of full decks.

The cards are of the following ranks :
2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A

The four suits are :
Spade( ♠ ), Club( ♣ ), Heart( ♥ ), and Diamond( ♦ )

The cards are given using their rank followed by their suit :

2 of Spades : 2S
Ace of Clubs : AC
10 of Hearts : TH

The "BMC_TEST_INPUT_MAGIC" (with quotes) in the code will be replaced with the actual value of the input.The input is in the format : "2S,AC,TH".
*/