#include <iostream>
#include <string>
#include <stdio.h>

void main( int argc,char * argv[])
{
	using namespace std;
	string s;

	  /*
	  operator=  - ������������ ������ ������ �����, ���������� �������� � ���� �����!!!
	  */

	  s = "hello,";
	  s+=" world!";
	  s+='!';
	  s+=33;
	  cout<<s<<endl;

	 /*
	 c_str() - ����������� ������ � const char* ��� ������������� � ��������, �� ������� �������� �� string. 
	 const value_type *c_str( ) const;
	 */
	
	  printf("%s\n",s.c_str());
	  cout<<"Length of string: "<<strlen(s.c_str())<<endl;

	  /*
	  operator[] - ������ � ���������� �������� � ������ ��� ������ ��� ������.
	  */

	  s[0]='H';
	  cout<<s<<endl;
	  cout<<s[7]<<endl;	

	  /*
	  find - ���������� ������� ��������� ������� ��� ��������� � ������ ������. 
	  substr - ����������� ���������. 
	  rfind - ������ find, �� ������������ ����� � ����� ������ �����. 
	  */

	  int nWordEnd = s.find(',');
	  string sub_string = s.substr(0,nWordEnd);//������� ������ �����
	  cout<<sub_string<<endl;

	  string path_to_exe = argv[0];//������ ���� � exe-�����
	  cout<<path_to_exe<<endl;
	  int n=path_to_exe.rfind('\\');
	  string exe_file=path_to_exe.substr(n+1);//������ ��� � ����������
	  cout<<exe_file<<endl;

	  /*
	  erase - �������� ������ ��� ����� �������� �� �������� ������ � �������� �������. 
	  */

	  s.erase(5,7);//������� � ����� ������� ������� 7 ��������
	  cout<<s<<endl;

	  /*
	  replace - ��������� ������ ��� ����� �������� � �������� �������
	  */
	
	  string result1a, result1b;
	  string s1 ( "AAAAAAAA" );
	  string s2 ( "BBB" );
	  s1.replace (1,4,s2);
      cout << "The result of replacement: " << s1 << endl;

	  /*
	  length(��� size) - ����������� ���������� �������� � ������.
	  */
	  cout<<"Size of string: "<<s1.length()<<endl;

	  /*
	  insert - ������� �������� ��� ������ ����� � ���������� ���� string.
	  */
	  cout<<"Source string: "<<s<<endl;
	  s.insert(5,", world");
	  cout<<"Result string: "<<s<<endl;

	  /*
	  compare - ��������� ������ (����� �������������� ��������� !=, <, >) 
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
