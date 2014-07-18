#include "TestTemplate.h"

template<typename T>
CTestTemplate<T>::CTestTemplate( T * data )
{
   mData = new T[strlen( data )+1];
   strcpy( mData, data );
}

//template<typename T>
//CTestTemplate<T>::CTestTemplate()
//{}
//
//template<typename T>
//CTestTemplate<T>::CTestTemplate( T * data )
//{
//   mData = new T[strlen( data )+1];
//   strcpy( mData, data );
//}

//CTestTemplate::~CTestTemplate()
//{}
