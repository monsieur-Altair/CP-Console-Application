#include "DataBase.h"
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	
	const string dataBaseFilePath = "D:\\OOP\\CP\\DataBaseFile.txt";
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

//2069 строк 07.05