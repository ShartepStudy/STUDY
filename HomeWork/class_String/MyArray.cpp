template<typename T> 
CMyArray<T>::CMyArray()
   : mAllocatedSize( ALLOCATED_STEP )
   , mSize( 0 )
   , mArray( new T[mAllocatedSize] )
{
   for (size_t i = 0; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

template<typename T>
CMyArray<T>::CMyArray( unsigned int size )
   : mAllocatedSize( size )
   , mSize( 0 )
   , mArray( new T[mAllocatedSize] )
{
   for (size_t i = 0; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

template<typename T>
CMyArray<T>::CMyArray( const CMyArray & obj )
   : mAllocatedSize( obj.mAllocatedSize )
   , mSize( obj.mSize )
   , mArray( new T[mAllocatedSize] )
{
   for (size_t i = 0; i < mSize; i++)
      mArray[i] = obj.mArray[i];
   for (size_t i = mSize; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

template<typename T>
CMyArray<T>::~CMyArray()
{
   delete[] mArray;
}

template<typename T>
void CMyArray<T>::resize( unsigned int size )
{
   if (!size) size = 1;
   
   mAllocatedSize = size;

   T * tmpArray = new T[mAllocatedSize];
   for (size_t i = 0; i < mSize; i++)
      tmpArray[i] = mArray[i];

   for (size_t i = mSize; i < mAllocatedSize; i++)
      tmpArray[i] = 0;

   delete[] mArray;
   mArray = tmpArray;   
}

template<typename T>
void CMyArray<T>::pushBack( T data )
{
   if (mSize >= mAllocatedSize)
      resize( mAllocatedSize + ALLOCATED_STEP );

   mArray[mSize++] = data;
}

template<typename T>
T CMyArray<T>::popBack()
{
   T tmp = mArray[--mSize];

   if (mSize + ALLOCATED_STEP < mAllocatedSize)
      resize( mAllocatedSize - ALLOCATED_STEP );

   return tmp;
}

template<typename T>
void CMyArray<T>::clear()
{
   delete[] mArray;
   mAllocatedSize = ALLOCATED_STEP;
   mSize = 0;
   mArray = new T[mAllocatedSize];
   for (size_t i = 0; i < mAllocatedSize; i++)
      mArray[i] = 0;
}

template<typename T>
int CMyArray<T>::getIndexOf( T data ) const
{
   for (size_t i = 0; i < mSize; i++)
      if (mArray[i]==data) 
         return i;

   return -1;
}

template<typename T>
int CMyArray<T>::getLastIndexOf( T data ) const
{
   for (size_t i = mSize-1; i >= 0; i--)
      if (mArray[i]==data)
         return i;

   return -1;
}

template<typename T>
unsigned int CMyArray<T>::getSize() const
{
   return mSize;
}

template<typename T>
const T * CMyArray<T>::getPTR() const
{
   return mArray;
}

template<typename T>
void CMyArray<T>::insert( unsigned int index, T data )
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

template<typename T>
void CMyArray<T>::removeAt( unsigned int index )
{
   if (index<mSize)
   {
      for (size_t i = index; i < mSize; i++)
         mArray[i] = mArray[i+1];

      mSize--;
   }
}

template<typename T>
void CMyArray<T>::reverse()
{
   int tmp;
   for (size_t i = 0, j = mSize-1; i < mSize; i++, j--)
   {
      tmp = mArray[i];
      mArray[i] = mArray[j];
      mArray[j] = tmp;
   }
}

template<typename T>
void CMyArray<T>::sortUp()
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

template<typename T>
void CMyArray<T>::shuffle()
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

template<typename T>
CMyArray<T> & CMyArray<T>::operator=(const CMyArray & rValue)
{
   delete[] mArray;
   mAllocatedSize = rValue.mAllocatedSize;
   mSize = rValue.mSize;
   mArray = new T[mAllocatedSize];

   for (size_t i = 0; i < mSize; i++)
      mArray[i] = rValue.mArray[i];
   for (size_t i = mSize; i < mAllocatedSize; i++)
         mArray[i] = 0;

   return *this;
}

template<typename T>
bool CMyArray<T>::operator==(const CMyArray & rValue) const
{
   if (mSize!=rValue.mSize) 
      return false;
   for (size_t i = 0; i < mSize; i++)
      if (mArray[i] != rValue.mArray[i])
         return false;

   return true;
}

template<typename T>
void CMyArray<T>::operator()()
{
   for (size_t i = 0; i < mSize; i++)
      mArray[i] = 0;
}                   

template<typename T>
T & CMyArray<T>::operator[]( unsigned int index ) const
{
   if (index>=mSize)
      return mArray[mSize-1];

   return mArray[index];
}

