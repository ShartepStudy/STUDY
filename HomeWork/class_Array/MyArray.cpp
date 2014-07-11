#include "MyArray.h"

CMyArray::CMyArray()
   : mAllocatedSize( ALLOCATED_STEP )
   , mSize( 0 )
   , mArray( new int[mAllocatedSize] )
{
   for (size_t i = 0; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

CMyArray::CMyArray( int size )
   : mAllocatedSize( size )
   , mSize( 0 )
   , mArray( new int[mAllocatedSize] )
{
   for (size_t i = 0; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

CMyArray::CMyArray( const CMyArray & obj )
   : mAllocatedSize( obj.mAllocatedSize )
   , mSize( obj.mSize )
   , mArray( new int[mAllocatedSize] )
{
   for (size_t i = 0; i < mSize; i++)
      mArray[i] = obj.mArray[i];
   for (size_t i = mSize; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

CMyArray::~CMyArray()
{
   delete[] mArray;
}

void CMyArray::resize( unsigned int size )
{
   if (!size) size = 1;
   
   mAllocatedSize = size;

   int * tmpArray = new int[mAllocatedSize];
   for (size_t i = 0; i < mSize; i++)
      tmpArray[i] = mArray[i];

   for (size_t i = mSize; i < mAllocatedSize; i++)
      tmpArray[i] = 0;

   delete[] mArray;
   mArray = tmpArray;   
}

void CMyArray::pushBack( int data )
{
   if (mSize >= mAllocatedSize)
      resize( mAllocatedSize + ALLOCATED_STEP );

   mArray[mSize++] = data;
}

int CMyArray::popBack()
{
   int tmp = mArray[--mSize];

   if (mSize + ALLOCATED_STEP < mAllocatedSize)
      resize( mAllocatedSize - ALLOCATED_STEP );

   return tmp;
}

void CMyArray::clear()
{
   delete[] mArray;
   mAllocatedSize = ALLOCATED_STEP;
   mSize = 0;
   mArray = new int[mAllocatedSize];
   for (size_t i = 0; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

int CMyArray::getIndexOf( int data )
{
   for (size_t i = 0; i < mSize; i++)
      if (mArray[i]==data) 
         return i;

   return -1;
}

int CMyArray::getLastIndexOf( int data )
{
   for (size_t i = mSize-1; i >= 0; i--)
      if (mArray[i]==data)
         return i;

   return -1;
}

void CMyArray::insert( unsigned int index, int data )
{
   if (index<mSize)
   {
      if (mSize>=mAllocatedSize)
         resize( mAllocatedSize + ALLOCATED_STEP );
      
      for (size_t i = mSize; i > index; i--)
         mArray[i] = mArray[i-1];
      
      mSize++;
   }
   else if (index>=mSize && index<mAllocatedSize)
      mSize = index + 1;
   else if (index>=mAllocatedSize)
   {
      resize( index + ALLOCATED_STEP );
      mSize = index + 1;
   }

   mArray[index] = data;
}

void CMyArray::removeAt( unsigned int index )
{
   if (index<mSize)
   {
      for (size_t i = index; i < mSize; i++)
         mArray[i] = mArray[i+1];

      mSize--;
   }
}

void CMyArray::reverse()
{
   int tmp;
   for (size_t i = 0, j = mSize-1; i < mSize; i++, j--)
   {
      tmp = mArray[i];
      mArray[i] = mArray[j];
      mArray[j] = tmp;
   }
}

void CMyArray::sortUp()
{
   bool isChanged;
   int tmp;
   
   do
   {
      isChanged = false;
      for (size_t i = 0; i < mSize; i++)
         if (mArray[i]>mArray[i+1])
         {
            tmp = mArray[i];
            mArray[i] = mArray[+1];
            mArray[i+1] = tmp;
            isChanged = true;
         }
    }
   while (isChanged);
}

void CMyArray::shuffle()
{
   int mixCount = rand() % mSize;
   int a, b;
   int tmpData;

   for (size_t i = 0; i < mixCount; i++)
   {
      a = rand() % mSize;
      b = rand() % mSize;
      tmpData = mArray[a];
      mArray[a] = mArray[b];
      mArray[b] = tmpData;
   }
}

bool CMyArray::operator==(const CMyArray & rValue)
{
   if (mSize!=rValue.mSize) 
      return false;
   for (size_t i = 0; i < mSize; i++)
      if (mArray[i] != rValue.mArray[i])
         return false;

   return true;
}

void CMyArray::operator()() 
{
   for (size_t i = 0; i < mSize; i++)
      mArray[i] = 0;
}                   

int & CMyArray::operator[]( unsigned int index )
{
   if (index>=mSize && index<mAllocatedSize)
   {
      mSize = index + 1;
   }
   else if (index>mAllocatedSize)
   {
      resize( index + ALLOCATED_STEP );
      mSize = index + 1;
   }
   return mArray[index];
}