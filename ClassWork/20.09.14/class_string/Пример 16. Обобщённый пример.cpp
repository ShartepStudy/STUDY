#include <iostream>
#include <string>
#include <stdio.h>

void main( int argc,char * argv[])
{
	using namespace std;
	string s;

	  /*
	  operator=  - присваивание строке других строк, символьных массивов и даже чисел!!!
	  */

	  s = "hello,";
	  s+=" world!";
	  s+='!';
	  s+=33;
	  cout<<s<<endl;

	 /*
	 c_str() - конвертация строки в const char* для использования в функциях, не умеющих работать со string. 
	 const value_type *c_str( ) const;
	 */
	
	  printf("%s\n",s.c_str());
	  cout<<"Length of string: "<<strlen(s.c_str())<<endl;

	  /*
	  operator[] - доступ к конкретным символам в строке для чтения или записи.
	  */

	  s[0]='H';
	  cout<<s<<endl;
	  cout<<s[7]<<endl;	

	  /*
	  find - нахождение первого вхождения символа или подстроки в данной строке. 
	  substr - возвращение подстроки. 
	  rfind - аналог find, но осуществляет поиск с конца строки назад. 
	  */

	  int nWordEnd = s.find(',');
	  string sub_string = s.substr(0,nWordEnd);//получим первое слово
	  cout<<sub_string<<endl;

	  string path_to_exe = argv[0];//полный путь к exe-файлу
	  cout<<path_to_exe<<endl;
	  int n=path_to_exe.rfind('\\');
	  string exe_file=path_to_exe.substr(n+1);//только имя и расширение
	  cout<<exe_file<<endl;

	  /*
	  erase - удаление одного или более символов из заданной строки в заданной позиции. 
	  */

	  s.erase(5,7);//начиная с пятой позиции удаляем 7 символов
	  cout<<s<<endl;

	  /*
	  replace - замещение одного или более символов в заданной позиции
	  */
	
	  string result1a, result1b;
	  string s1 ( "AAAAAAAA" );
	  string s2 ( "BBB" );
	  s1.replace (1,4,s2);
      cout << "The result of replacement: " << s1 << endl;

	  /*
	  length(или size) - возвращение количества символов в строке.
	  */
	  cout<<"Size of string: "<<s1.length()<<endl;

	  /*
	  insert - вставка символов или других строк в переменную типа string.
	  */
	  cout<<"Source string: "<<s<<endl;
	  s.insert(5,", world");
	  cout<<"Result string: "<<s<<endl;

	  /*
	  compare - сравнение строки (также поддерживаются операторы !=, <, >) 
	  */
	  s1="Ivanov";
	  s2="Sidorov";
	  if(s1>s2)
		  cout<<s1<<" more than "<<s2<<endl;
	  else if(s1<s2)
		  cout<<s1<<" less than "<<s2<<endl;
	  else
		  cout<<s1<<" equal "<<s2<<endl;

}
