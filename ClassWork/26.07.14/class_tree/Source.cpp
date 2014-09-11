#include <iostream>
#include <iostream>
#include <time.h>
using namespace std;

struct Elem
{
   int item;

   Elem* left; // левый потомок
   Elem* right; // правый потомок
   Elem* parent; // родитель
};

class Tree
{
   Elem* root; // корень
public:
   Tree( );
   ~Tree( );
   // печать от указанного узла
   void Print( Elem* Node );
   // поиск от указанного узла
   Elem* Search( Elem* Node, int k );
   // min от указанного узла
   Elem* Min( Elem* Node );
   // max от указанного узла
   Elem* Max( Elem* Node );
   // следующий для указанного узла
   Elem* Next( Elem* Node );
   // предыдущий для указанного узла
   Elem* Previous( Elem* Node );
   // вставка узла
   void Insert( int digit );
   // удаление ветки для указанного узла, 
   // 0 - удаление всего дерева
   void Del( Elem* z = 0 );
   // получить корень
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

// Рекурсивный обход дерева
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
   // пока есть узлы и ключи не совпадают
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
   // поиск самого левого узла
   if (Node != 0)
   while (Node->left != 0)
      Node = Node->left;

   return Node;
}

Elem* Tree::Max( Elem* Node )
{
   // поиск самого правого узла
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
      // если есть правый потомок
      if (Node->right != 0)
         return Min( Node->right );

      // родитель узла
      y = Node->parent;
      // если Node не корень и Node справа
      while (y != 0 && Node == y->right)
      {
         // Движемся вверх
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
      // если есть левый потомок
      if (Node->left != 0)
         return Max( Node->left );

      // родитель узла
      y = Node->parent;
      // если Node не корень и Node слева
      while (y != 0 && Node == y->left)
      {
         // Движемся вверх
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

   // потомков нет
   z->left = 0;
   z->right = 0;

   Elem* y = 0;
   Elem* Node = root;

   // поиск места
   while (Node != 0)
   {
      // будущий родитель
      y = Node;
      if (z->item < Node->item)
         Node = Node->left;
      else
         Node = Node->right;
   }
   // заполняем родителя
   z->parent = y;

   if (y == 0) // узлов в дереве ещё не было
      root = z;
   // назначение родительских прав
   else if (z->item < y->item)
      y->left = z;
   else
      y->right = z;
}

void Tree::Del( Elem* z )
{
   // удаление куста
   if (z != 0)
   {
      Elem* Node, *y;

      // не 2 ребенка
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
      // Удаляется корневой узел?
      if (y->parent == 0)
         root = Node;
      else if (y == y->parent->left) // слева от родителя?
         y->parent->left = Node;
      else
         y->parent->right = Node;  // справа от родителя?

      if (y != z)
      {
         // Копирование данных узла
         z->item = y->item;
      }

      delete y;
   }
   else // удаление всего дерева
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