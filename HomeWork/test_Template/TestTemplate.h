#pragma once
template<typename T>
class CTestTemplate
{
private:
   T * mData;
public:
//   CTestTemplate();
   CTestTemplate( T * data );
   //{
   //   mData = new T[strlen( data )+1];
   //   strcpy( mData, data );
   //}
   void setData( const T * data )
   {
      mData = new T[strlen( data )+1];
      strcpy( mData, data );
   }
   char * getData() { return mData; }
};

