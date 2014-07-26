#include <iostream>
using namespace std;

struct Elem
{
   int data;
   Elem* next;
   Elem* prev;
};

class List
{
   Elem *Head, *Tail;
   int length;
public:
   List( );
   List( const List& );
   ~List( );
   int GetLength( );
   void AddTail( int n );
   void AddHead( int n );
   void Insert( int pos = 0 );
   void Del( int pos = 0 );
   void DelAll( );
   void Print( );
   void Print( int pos );
   Elem* GetElem( int );

   List& operator = (const List&);
   List operator + (const List&);

   bool operator == (const List&);
   bool operator != (const List&);
   bool operator <= (const List&);
   bool operator >= (const List&);
   bool operator < (const List&);
   bool operator > (const List&);

   List operator - (); // переворачивание
};

List::List( )
{
   Head = Tail = NULL;
   length = 0;
}

void List::AddHead( int n )
{
   Elem * temp = new Elem( );
   temp->prev = 0;
   temp->data = n;
   temp->next = Head;

   // если в списке уже есть элементы
   if (Head != 0) Head->prev = temp;

   // если элементов не было
   if (length == 0) Head = Tail = temp;
   else Head = temp;

   length++;
}

void List::AddTail( int n )
{
   Elem * temp = new Elem( );
   temp->next = 0;
   temp->data = n;
   temp->prev = Tail;

   // если в списке уже есть элементы
   if (Tail != 0) Tail->next = temp;

   // если элементов не было
   if (length == 0) Head = Tail = temp;
   else Tail = temp;

   length++;
}

// конструктор копирования
List::List( const List & L )
{
   Head = Tail = NULL;
   length = 0;

   // голова списка, который копируется
   Elem* temp = L.Head;

   while (temp != 0)
   {
      AddTail( temp->data );
      temp = temp->next;
   }
}

void List::Insert( int pos )
{
   if (pos == 0)
   {
      cout << "Input position: ";
      cin >> pos;
   }

   if (pos < 1 || pos > length + 1)
   {
      cout << "Incorrect position !!!\n";
      return;
   }

   if (pos == length + 1)
   {
      int data;
      cout << "Input new data: ";
      cin >> data;
      AddTail( data );
      return;
   }
   else if (pos == 1)
   {
      int data;
      cout << "Input new data: ";
      cin >> data;
      AddHead( data );
      return;
   }

   int i = 1;
   Elem * Ins = Head;
   while (i < pos)
   {
      Ins = Ins->next;
      i++;
   }

   Elem * PrevIns = Ins->prev;

   Elem * temp = new Elem( );

   cout << "Input new data: ";
   cin >> temp->data;

   // настройка связей
   if (PrevIns != 0 && length != 1)
      PrevIns->next = temp;

   temp->next = Ins;
   temp->prev = PrevIns;
   Ins->prev = temp;

   length++;
}

void List::Del( int pos )
{
   if (pos == 0)
   {
      cout << "Input position: ";
      cin >> pos;
   }
   if (pos < 1 || pos > length)
   {
      cout << "Incorrect position !!!\n";
      return;
   }

   int i = 1;
   Elem * Del = Head;
   while (i < pos)
   {
      Del = Del->next;
      i++;
   }

   Elem * PrevDel = Del->prev;
   Elem * AfterDel = Del->next;

   // если удаляется не голова
   if (PrevDel != 0 && length != 1)
      PrevDel->next = AfterDel;
   // если удаляется не хвост
   if (AfterDel != 0 && length != 1)
      AfterDel->prev = PrevDel;

   // удаление крайних элементов
   if (pos == 1) Head = AfterDel;
   if (pos == length) Tail = PrevDel;

   delete Del;

   length--;
}

void List::DelAll( )
{
   while (length != 0) Del( 1 );
}

List::~List( )
{
   DelAll( );
}

void List::Print( int pos )
{
   if (pos < 1 || pos > length)
   {
      cout << "Incorrect position !!!\n";
      return;
   }

   Elem * temp;

   if (pos <= length / 2)
   {
      temp = Head;
      int i = 1;
      while (i < pos)
      {
         temp = temp->next;
         i++;
      }
   }
   else
   {
      temp = Tail;
      int i = 1;
      while (i <= length - pos)
      {
         temp = temp->prev;
         i++;
      }
   }

   cout << pos << " element: ";
   cout << temp->data << endl;
}

void List::Print( )
{
   if (length != 0)
   {
      Elem * temp = Head;
      cout << "( ";
      while (temp->next != 0)
      {
         cout << temp->data << ", ";
         temp = temp->next;
      }

      cout << temp->data << " )\n";
   }
}

int List::GetLength( )
{
   return length;
}

Elem * List::GetElem( int pos )
{
   Elem *temp = Head;

   if (pos < 1 || pos > length)
   {
      cout << "Incorrect position !!!\n";
      return 0;
   }

   int i = 1;
   while (i < pos && temp != 0)
   {
      temp = temp->next;
      i++;
   }

   if (temp == 0) return 0;
   else return temp;
}

List & List::operator = (const List & L)
{
   // проверка на присвоение элемента самому себе
   if (this == &L) return *this;

   // удаление старого списка
   this->~List( ); // DelAll();

   Elem* temp = L.Head;

   while (temp != 0)
   {
      AddTail( temp->data );
      temp = temp->next;
   }

   return *this;
}

List List::operator + (const List& L)
{
   List Result = *this;

   Elem * temp = L.Head;

   while (temp != 0)
   {
      Result.AddTail( temp->data );
      temp = temp->next;
   }

   return Result;
}

bool List::operator == (const List& L)
{
   // сравнение по количеству
   if (length != L.length)
      return false;

   // сравнение по содержанию
   Elem *t1, *t2;

   t1 = Head;
   t2 = L.Head;

   while (t1 != 0)
   {
      // Сверяем данные, которые
      // находятся на одинаковых позициях
      if (t1->data != t2->data)
         return false;

      t1 = t1->next;
      t2 = t2->next;
   }

   return true;
}

bool List::operator != (const List& L)
{
   return !(*this == L);
}

bool List::operator >= (const List& L)
{
   if (length > L.length) return true;
   if (*this == L) return true;
   return false;
}

bool List::operator <= (const List& L)
{
   if (length < L.length) return true;
   if (*this == L) return true;
   return false;
}

bool List::operator >( const List& L )
{
   if (length > L.length)
      return true;
   return false;
}

bool List::operator < (const List& L)
{
   if (length < L.length)
      return true;
   return false;
}

// переворот
List List::operator - ()
{
   List Result;

   Elem * temp = Head;
   // копирование элементов списка, начиная с головного,
   // в Result путем добавления элементов в голову.
   // таким образом временный список Result будет содержать
   // все элементы в обратном порядке
   while (temp != 0)
   {
      Result.AddHead( temp->data );
      temp = temp->next;
   }

   return Result;
}

void main( )
{
   List L;
   L.AddHead( 1 );

   L.AddTail( 2 );

   L.AddHead( 3 );

   L.AddTail( 4 );

   L.AddHead( 5 );

   L.Print( );

   L.Insert( );

   L.Print( );

   L.Print( 2 );

   L.Print( 8 );

   List T;

   T = L;

   T.Print( );

   List Sum = -L + T;

   Sum.Print( );
}