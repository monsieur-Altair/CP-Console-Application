#include "DataBase.h"
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	
	const string dataBaseFilePath = "D:\\OOP\\CP\\DataBaseFile.txt";
	//hash<string> s;
	//string a;
	//cin >> a;
	//float r = s(a);
	//bool m = (s("14sa") == r);
	//cout << s("14sa")<<endl<<r<<endl<<m;
	
	DataBase db0(dataBaseFilePath);
	db0.AuthorizationMenu();
	//db0.PrintAllTests();
	//db0.PrintAllStudents();
	//db0.PrintAllTeachers();
	db0.Unload(dataBaseFilePath);
	//cout <<"\n\n\n\n" <<sizeof(list<double>)<<"\n\n\n\n";
	//cout << sizeof('\n');
	return 0;
}
