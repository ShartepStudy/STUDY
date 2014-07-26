#include <iostream>
#include <iostream>
#include <time.h>
using namespace std;

struct Elem
{
   int item;

   Elem* left; // ����� �������
   Elem* right; // ������ �������
   Elem* parent; // ��������
};

class Tree
{
   Elem* root; // ������
public:
   Tree( );
   ~Tree( );
   // ������ �� ���������� ����
   void Print( Elem* Node );
   // ����� �� ���������� ����
   Elem* Search( Elem* Node, int k );
   // min �� ���������� ����
   Elem* Min( Elem* Node );
   // max �� ���������� ����
   Elem* Max( Elem* Node );
   // ��������� ��� ���������� ����
   Elem* Next( Elem* Node );
   // ���������� ��� ���������� ����
   Elem* Previous( Elem* Node );
   // ������� ����
   void Insert( int digit );
   // �������� ����� ��� ���������� ����, 
   // 0 - �������� ����� ������
   void Del( Elem* z = 0 );
   // �������� ������
   Elem* GetRoot( );
};

Tree::Tree( )
{
   root = 0;
}

Tree::~Tree( )
{
   Del( );
}

// ����������� ����� ������
void Tree::Print( Elem* Node )
{
   if (Node != 0)
   {
      Print( Node->left );
      cout << Node->item <<"  ";
      Print( Node->right );
   }
}

Elem* Tree::Search( Elem* Node, int k )
{
   // ���� ���� ���� � ����� �� ���������
   while (Node != 0 && k != Node->item)
   {
      if (k < Node->item)
         Node = Node->left;
      else
         Node = Node->right;
   }
   return Node;
}

Elem* Tree::Min( Elem* Node )
{
   // ����� ������ ������ ����
   if (Node != 0)
   while (Node->left != 0)
      Node = Node->left;

   return Node;
}

Elem* Tree::Max( Elem* Node )
{
   // ����� ������ ������� ����
   if (Node != 0)
   while (Node->right != 0)
      Node = Node->right;

   return Node;
}

Elem* Tree::Next( Elem* Node )
{
   Elem* y = 0;
   if (Node != 0)
   {
      // ���� ���� ������ �������
      if (Node->right != 0)
         return Min( Node->right );

      // �������� ����
      y = Node->parent;
      // ���� Node �� ������ � Node ������
      while (y != 0 && Node == y->right)
      {
         // �������� �����
         Node = y;
         y = y->parent;
      }
   }
   return y;
}

Elem* Tree::Previous( Elem* Node )
{
   Elem* y = 0;
   if (Node != 0)
   {
      // ���� ���� ����� �������
      if (Node->left != 0)
         return Max( Node->left );

      // �������� ����
      y = Node->parent;
      // ���� Node �� ������ � Node �����
      while (y != 0 && Node == y->left)
      {
         // �������� �����
         Node = y;
         y = y->parent;
      }
   }
   return y;
}

Elem* Tree::GetRoot( )
{
   return root;
}

void Tree::Insert( int digit )
{
   Elem* z = new Elem;

   z->item = digit;

   // �������� ���
   z->left = 0;
   z->right = 0;

   Elem* y = 0;
   Elem* Node = root;

   // ����� �����
   while (Node != 0)
   {
      // ������� ��������
      y = Node;
      if (z->item < Node->item)
         Node = Node->left;
      else
         Node = Node->right;
   }
   // ��������� ��������
   z->parent = y;

   if (y == 0) // ����� � ������ ��� �� ����
      root = z;
   // ���������� ������������ ����
   else if (z->item < y->item)
      y->left = z;
   else
      y->right = z;
}

void Tree::Del( Elem* z )
{
   // �������� �����
   if (z != 0)
   {
      Elem* Node, *y;

      // �� 2 �������
      if (z->left == 0 || z->right == 0)
         y = z;
      else
         y = Next( z );

      if (y->left != 0)
         Node = y->left;
      else
         Node = y->right;

      if (Node != 0)
         Node->parent = y->parent;
      // ��������� �������� ����?
      if (y->parent == 0)
         root = Node;
      else if (y == y->parent->left) // ����� �� ��������?
         y->parent->left = Node;
      else
         y->parent->right = Node;  // ������ �� ��������?

      if (y != z)
      {
         // ����������� ������ ����
         z->item = y->item;
      }

      delete y;
   }
   else // �������� ����� ������
   while (root != 0)
      Del( root );
}

void main( )
{
   setlocale( 0, "" );
   srand( time( 0 ) );

   Tree t;
   for (int i = 0; i<250; i++)
      t.Insert( rand( )%900+100 );

   t.Print( t.GetRoot( ) );
}